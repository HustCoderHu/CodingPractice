#include "modules/fec/rsfecsender.h"

namespace webrtc {

bool RsFecSender::checkFecRateUp(TimeDelta bound_ms)
{
  return fec_rate_.cur_ > fec_rate_.last_ * 1.25
      && fec_rate_.updateTime < fec_rate_.lastTime+bound_ms;
}

bool RsFecSender::checkLossUp(TimeDelta bound_ms)
{
  return loss_rate_.cur_ > loss_rate_.last_ * 1.25
      && loss_rate_.updateTime < loss_rate_.lastTime + bound_ms;
}

/**
 * @brief
 * @param new_rate
 * @note 不同排队情况下， fec 码率增长速度不同
 */
void RsFecSender::updateLossRate(uint16_t new_rate)
{
  Timestamp now = clock_->CurrentTime();
  loss_rate_.update(new_rate, now);
  if (new_rate < fec_rate_.cur_)
    fec_rate_.update(new_rate, now);

  switch (rate_ctrl_state_) {
    case BandwidthUsage::kBwOverusing:
      // overusing 时 fec 不能增加太多 smooth 增加
      if (new_rate > fec_rate_.cur_)
        fec_rate_.update(fec_rate_.cur_ + (new_rate - fec_rate_.cur_)/4,
                         now);
      else // 快速下降
        fec_rate_.update(new_rate, now);
      break;
    case BandwidthUsage::kBwNormal:
      if (new_rate > fec_rate_.cur_)
        fec_rate_.update(fec_rate_.cur_ + (new_rate - fec_rate_.cur_)/2,
                         now);
      else // 快速下降
        fec_rate_.update(new_rate, now);
      break;
    case BandwidthUsage::kBwUnderusing:
      if (new_rate > fec_rate_.cur_)
        fec_rate_.update(fec_rate_.cur_ + (new_rate - fec_rate_.cur_)/3,
                         now);
      else // 快速下降
        fec_rate_.update(new_rate, now);
      break;
  }
}

void RsFecSender::OnBwNormal(BandwidthUsage prev_state)
{
  Timestamp now = clock_->CurrentTime();
  bool recoverd_from_overuse = prev_state == BandwidthUsage::kBwOverusing;

  uint32_t decrease, target;
  switch (rate_ctrl_state_.cur_) {
    case RateControlState::kRcIncrease:
      uint16_t last_chg = fec_rate_.cur_ - fec_rate_.last_;
      if (acknowledge_rate_.cur_ - acknowledge_rate_.last_ < last_chg*0.2) {
        // 但是接收码率增加很少, 说明增加的基本都丢包了，继续增加也无意义
        rate_ctrl_state_.update(RateControlState::kRcDecrease, now);
        // 需要回退 fec_rate 退一半
        fec_rate_.update((fec_rate_.cur_-fec_rate_.last_)>>1, now);
        break;
      } // 接收端还能继续增加接受的情况下，检查是否需要继续降 delay,
      // fall through to below kRcHold
    case RateControlState::kRcHold: {
      if (recver_report_delay_.cur_ > max_pending_) {
        // delay not low enough, 分组分析决策下一个冗余码率
        DataRate block_analyze_next = block_analyze_res[cur_idx+1];
        DataRate new_fec_rate = fec_rate_.cur_;
        if (fec_rate_.cur_ + total_rate_.cur_ * 0.08 < block_analyze_next)
          new_fec_rate += total_rate_.cur_ * 0.08;
        else
          new_fec_rate = block_analyze_res[++cur_idx];
        fec_rate_.update(new_fec_rate, now);
        rate_ctrl_state_ = RateControlState::kRcIncrease;
      }
    } break;
    case RateControlState::kRcDecrease: {
      rate_ctrl_state_ = RateControlState::kRcHold;
    }
      break;
    default:
      break;
  }

  switch (rate_ctrl_state_) {
    case RateControlState::kRcHold:
      rsfec_generator_.UpdateCoefficient(kOptimizeBwDown);

      decrease = fec_rate_.cur_ * kOptimizeBwDown; // 100;
      target = fec_rate_.cur_ - decrease;
      if (target > fec_rate_bound_left_.cur_) {
        // 下探, 降低带宽成本
        fec_rate_.update(target, now);
        rate_ctrl_state_ = RateControlState::kRcDecrease;
      } else {
        // 到达下界
        fec_rate_.update(fec_rate_bound_left_.cur_, now);
        // 状态维持 Hold
      }
      break;

    case RateControlState::kRcDecrease:
      if (checkFecRateUp(k_interval_between_dec_while_loss_inc) ) {
        // fec 冗余率上升时 暂时不要下探
        rate_ctrl_state_ = RateControlState::kRcHold;
        break;
      }
      rsfec_generator_.UpdateCoefficient(kOptimizeBwDown);

      decrease = fec_rate_.cur_ * kOptimizeBwDown; // 100;
      target = fec_rate_.cur_ - decrease;
      if (target > fec_rate_bound_left_.cur_) {
        // 下探, 降低带宽成本
        fec_rate_.update(target, now);
      } else {
        // 到达下界
        fec_rate_.update(fec_rate_bound_left_.cur_, now);
        rate_ctrl_state_ = RateControlState::kRcHold;
        // warning
      }
      break;
    default:
      break;
  }
  hypothesis_ = BandwidthUsage::kBwNormal;
}

void RsFecSender::OnBwOverusing(BandwidthUsage prev_state)
{
  Timestamp now = clock_->CurrentTime();

  switch (rate_ctrl_state_.cur_) {
    case RateControlState::kRcHold: {
      // 网络被其他流挤占
      rate_ctrl_state_.update(RateControlState::kRcDecrease, now);
    } break;

    case RateControlState::kRcIncrease: {
      rate_ctrl_state_.update(RateControlState::kRcDecrease, now);
    }
  }

  switch (rate_ctrl_state_) {
    case RateControlState::kRcHold:
    if (checkFecRateUp(rtt_ + (rtt_>>2)) ) {
      // fec 冗余率上升 还没有体现在网络里
      rate_ctrl_state_ = RateControlState::kRcHold;
      break;
    }
    rsfec_generator_.UpdateCoefficient(kOptimizeBwDown);
    rate_ctrl_state_ = RateControlState::kRcDecrease;
      break;
    case RateControlState::kRcDecrease:
      // if now - last_change < rtt_ + (rtt>>2)
      // 时间不够
      rsfec_generator_.UpdateCoefficient(kOptimizeBwDown);
      break;
  }
  hypothesis_ = BandwidthUsage::kBwOverusing;
}

void RsFecSender::OnBwUnderusing(BandwidthUsage prev_state)
{
  Timestamp now = clock_->CurrentTime();
  if (recver_report_delay_.cur_ > max_pending_) {
    // delay not low enough, 分组分析决策下一个冗余码率
    DataRate block_analyze_next = block_analyze_res[cur_idx+1];
    DataRate new_fec_rate = fec_rate_.cur_;
    if (fec_rate_.cur_ + total_rate_.cur_ * 0.08 < block_analyze_next)
      new_fec_rate += total_rate_.cur_ * 0.08;
    else
      new_fec_rate = block_analyze_res[++cur_idx];
    fec_rate_.update(new_fec_rate, now);
    rate_ctrl_state_ = RateControlState::kRcIncrease;
  }

  switch (rate_ctrl_state_.cur_) {
    case RateControlState::kRcHold: {
      rate_ctrl_state_.update(RateControlState::kRcDecrease, now);
    } break;

    case RateControlState::kRcIncrease: {
      rate_ctrl_state_.update(RateControlState::kRcDecrease, now);
    }
  }

  switch (rate_ctrl_state_) {
    case RateControlState::kRcHold:
      break;
    case RateControlState::kRcDecrease:
      break;
  }
    hypothesis_ = BandwidthUsage::kBwOverusing;
}



} // namespace webrtc
