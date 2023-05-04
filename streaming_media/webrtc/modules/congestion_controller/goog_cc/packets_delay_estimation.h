#pragma once
#include <stdint.h>
#include <api/units/timestamp.h>
#include <api/units/time_delta.h>

#include "modules/video_coding/nack_responder.h"
#include "modules/video_coding/nack_requester.h"

namespace webrtc {

/**
 * @brief The PacketsDelayEstimation class
 * @note 根据重传情况估计包平均延迟
 * sum(packet.resend_cnt * rtt )
 * 范围选择
 */
class PacketsDelayEstimation
{
\ public:
  PacketsDelayEstimation();
  ~PacketsDelayEstimation();

  void UpdateRtt(TimeDelta rtt) {rtt_ = rtt;}

  TimeDelta MeanDelay(Timestamp now, const NackResponder& responder);
  TimeDelta MeanDelay(Timestamp now, const NackRequester& requester);

  // 发送端从上游收到源包的时间
  Timestamp getRecvTsFromUpStreamForSeqPkt(uint64_t seq);


  TimeDelta rtt_;
};

TimeDelta PacketsDelayEstimation::MeanDelay(Timestamp now,
                                           const NackResponder &responder)
{
  TimeDelta period = TimeDelta::Millis(300);
  uint64_t latest_seq;

  auto rit = responder.seq_resend_cnt_.rbegin();
  for (; rit != responder.seq_resend_cnt_.rend(); ++rit) {
    uint64_t seq = rit->first;
    Timestamp recvTs = getRecvTsFromUpStreamForSeqPkt(seq);

    if (now - recvTs > period)
      continue;

    // 只统计最近时段的

  }

}

/**
 * @brief 接收端计算重传引入的平均延迟
 * @param now
 * @param requester
 * @note 累加 nack_list 里所有没有收到的包的等待时间
 * @return
 */
TimeDelta PacketsDelayEstimation::MeanDelay(Timestamp now, const NackRequester &requester)
{
  TimeDelta period = TimeDelta::Millis(1000);
  uint64_t latest_seq;

  uint64_t earliest_seq = 0; //

  uint16_t pkts_cnt = 0;
  TimeDelta sum_delay = TimeDelta::Zero();
  auto rit = requester.nack_list_.rbegin();

  for (; rit != requester.nack_list_.rend(); ++rit) {
    NackRequester::NackInfo& nackinfo = rit->second;

    // 等待时间
    TimeDelta delay = now - nackinfo.created_at_time;
    if (delay > period)
      continue;

    // 只统计最近时段的
    sum_delay += delay;
    pkts_cnt++;
    earliest_seq = rit->first;
  }

  if (latest_seq - earliest_seq < 30) {
    // seq 总数太少
    return 0;
  }

  TimeDelta mean_delay = sum_delay / (latest_seq-earliest_seq);
  return mean_delay;
}

}  // namespace webrtc
