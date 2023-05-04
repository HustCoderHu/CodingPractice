#ifndef RSFECSENDER_H
#define RSFECSENDER_H

#include "protocol.h"
#include "modules/fec/video_fec_generator.h"
#include "modules/fec/fecqueue.h"
#include "modules/fec/fec_generator.h"
#include "modules/congestion_controller/goog_cc/trendline_estimator.h"

namespace webrtc {

enum class RateControlState { kRcHold, kRcIncrease, kRcDecrease };

class RsFecSender : public FecGenerator,
    public TrendlineEstimator::INetworkStateChange
{
public:
  bool checkFecRateUp(TimeDelta bound_ms);
  bool checkLossUp(TimeDelta bound_ms);

  void updateLossRate(uint16_t new_rate);

  void OnBwNormal(BandwidthUsage prev_state) override;
  void OnBwOverusing(BandwidthUsage prev_state) override;
  void OnBwUnderusing(BandwidthUsage prev_state) override;

  uint16_t rtt_;
//  FecQueue iframeQ;
//  FecQueue pframeQ;
  RsfecGenerator rsfec_generator_;

  ValueRecord<DataRate> total_rate_;
  ValueRecord<uint16_t> loss_rate_;
  ValueRecord<DataRate> fec_rate_; // fec 冗余度要网络排队情况
  ValueRecord<uint16_t> prev_fec_rate_; // fec 冗余度要网络排队情况

  ValueRecord<DataRate> acknowledge_rate_;
  // 和 丢包率调整

  struct ValueRange
  {
    ValueRange() {}
    ValueRecord left;
    ValueRecord right;
  };
  ValueRange fec_rate_bound_;
  ValueRecord<uint8_t> fec_rate_bound_left_;  // 1.1
  ValueRecord<uint8_t> fec_rate_bound_right_; // 1.25

  static const double kOptimizeBwDown; //0.92 defaul 970 / 1000;
  static const TimeDelta k_loss_rate_up_interval_bound; // 200 ms
  static const TimeDelta k_interval_between_dec_while_loss_inc; // 200 ms

  int interleaving_step_;

  Clock *clock_; // GetRealTimeClock()
  BandwidthUsage hypothesis_;
  ValueRecord<RateControlState> rate_ctrl_state_;

  // seq 左右边界 标记 延迟
  // 发送端确定区间的 fec_rate, 然后调整
  // seq 区间是用来同步发送和接送段的  fec_rate 和 延迟的对应关系
  ValueRecord<TimeDelta> recver_report_delay_;

  TimeDelta max_pending_;
};

#endif // RSFECSENDER_H
