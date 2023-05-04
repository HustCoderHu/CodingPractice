#include <stdint.h>
#include <vector>

#include "modules/congestion_controller/goog_cc/link_capacity_estimator.h"
#include "api/network_state_predictor.h"

using std::vector;

namespace webrtc {

enum class RateControlStat {
  Hold,
  Incr,
  Dec
};

void OnFeedback()
{
  DataRate src_rate;
  DataRate fec_rate;

  DataRate total_rate;

  TimeDelta max_pending;
  TimeDelta cur_delay;

  vector<uint32_t> block_analyze_res;
  uint32_t cur_idx;

  RateControlStat stat_;
  DataRate acknowledge_rate;

  DataRate fec_rate;
  DataRate last_fec_rate;

  uint8_t  loss_rate_plus256;
  uint8_t  last_loss_rate_plus256;

  DataRate new_acknowledge_rate;

  BandwidthUsage cur_state;

  switch (stat_) {
    case RateControlStat::Hold: {
      DataRate last_chg = fec_rate - last_fec_rate; // 上次调整的码率
      if (cur_state == BandwidthUsage::kBwOverusing) {
        // 排队了，只能减少
        last_fec_rate = fec_rate;
        fec_rate -= last_chg;
        stat_ = RateControlStat::Dec;
        break;
      }
      if (cur_delay > max_pending) {
        // fec_rate need increase to lower delay
        // 分组分析决策下一个冗余码率
        stat_ = RateControlStat::Incr;
      }
    }
      break;
    case RateControlStat::Incr: {
      DataRate last_chg = fec_rate - last_fec_rate; // 上次调整的码率
      if (cur_state == BandwidthUsage::kBwOverusing) {
        // 排队了，只能减少
        last_fec_rate = fec_rate;
        fec_rate -= last_chg;
        stat_ = RateControlStat::Dec;
        break;
      }
      // 没排队
      if (new_acknowledge_rate - acknowledge_rate < last_chg * 0.2) {
        // 但是接收码率增加很少, 说明增加的基本都丢包了，继续增加也无意义
        stat_ = RateControlStat::Hold;
        // 码率回滚
        last_fec_rate = fec_rate;
        fec_rate -= last_chg;
        break;
      }

      if (cur_delay > max_pending) {
        // delay not low enough, 分组分析决策下一个冗余码率
        last_fec_rate = fec_rate;
        DataRate block_analyze_next = block_analyze_res[cur_idx+1];
        if (fec_rate + total_rate * 0.08 < block_analyze_next)
          fec_rate += total_rate * 0.08;
        else
          fec_rate = block_analyze_res[++cur_idx];
      }
    }
      break;
    case RateControlStat::Dec:
      if (cur_state == BandwidthUsage::kBwOverusing) {
        // 拥塞了还未解除，需要继续降
        fec_rate -= total_rate*0.1;
        stat_ = RateControlStat::Dec;
        break;
      }
      if (cur_delay < max_pending * 0.85) {
        // 延迟已经满足，向下降低 fec_rate
        //
      }
      DataRate last_chg = last_fec_rate - fec_rate; // 上次减少的码率
      if (acknowledge_rate - new_acknowledge_rate >= last_chg * 0.2) {
        // 降低 有效
      }
      break;
    default:
      break;
  }
}

/**
 * @brief
 * SRNE: src_rate not enough
 * INCR: increase fec rate
 * DEC:  decrease fec rate
 *
 * ATTEM: attemp more rate
 * ATFB:  attemp failed, fall back to decrese
 * @note 接收端发现
 */

void judgeState()
{
  DataRate acknowledge_rate;
  DataRate src_rate;
  DataRate fec_rate;

  DataRate total_rate;

  BandwidthUsage cur_state;

  TimeDelta max_pending;
  TimeDelta cur_delay;

  vector<uint32_t> block_analyze_res;
  uint32_t cur_idx;

  switch (cur_state) {
    case BandwidthUsage::kBwOverusing:
      // 开始排队了, 提高冗余也没有用
      if (acknowledge_rate < src_rate) {
        // 不足以传输源流, 需要增加发送
      } else {
        fec_rate -= total_rate*0.1;
      }
      break;

    case BandwidthUsage::kBwNormal:
      if (acknowledge_rate < src_rate) {
        // 不足以传输源流, 需要增加发送
      }
    case BandwidthUsage::kBwUnderusing:
      // 可以增加
      break;
    default:
      break;
  }


  if (acknowledge_rate < src_rate) {
    // 不足以传输源流, 需要增加发送
    switch (cur_state) {
      case BandwidthUsage::kBwOverusing:
        // 开始排队了 不能增加冗余
        break;

      case BandwidthUsage::kBwNormal:
      case BandwidthUsage::kBwUnderusing:
        // 可以增加
        break;
      default:
        break;
    }
  } else if (acknowledge_rate > src_rate * 1.15) {
    if (cur_delay < max_pending * 0.85) {
      // 延迟已经满足，向下降低 fec_rate
      //
    }
  }
}

} // namespace webrtc
