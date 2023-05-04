#include "modules/video_coding/nack_requester.h"
#include "rtc_base/numerics/sequence_number_util.h"

namespace webrtc {

namespace {
constexpr int kMaxPacketAge = 10000;
constexpr int kMaxNackPackets = 1000;
constexpr TimeDelta kDefaultRtt = TimeDelta::Millis(100);
constexpr int kMaxNackRetries = 10;
constexpr int kMaxReorderedPackets = 128;
constexpr int kNumReorderingBuckets = 10;
constexpr TimeDelta kDefaultSendNackDelay = TimeDelta::Zero();

TimeDelta GetSendNackDelay(const FieldTrialsView& field_trials) {
  int64_t delay_ms = strtol(
      field_trials.Lookup("WebRTC-SendNackDelayMs").c_str(), nullptr, 10);
  if (delay_ms > 0 && delay_ms <= 20) {
    RTC_LOG(LS_INFO) << "SendNackDelay is set to " << delay_ms;
    return TimeDelta::Millis(delay_ms);
  }
  return kDefaultSendNackDelay;
}
}  // namespace

void NackRequester::ProcessNacks()
{
  std::vector<uint16_t> nack_batch = GetNackBatch(kTimeOnly);



  if (!nack_batch.empty()) {
    // This batch of NACKs is triggered externally; there is no external
    // initiator who can batch them with other feedback messages.
    nack_sender_->SendNack(nack_batch, /*buffering_allowed=*/false);
  }
}

int NackRequester::OnRecvPacket(uint64_t seq, bool is_keyframe,
                                bool is_resend, bool is_recovered)
{

}

std::vector<uint16_t> NackRequester::GetNackBatch(NackRequester::NackFilterOptions options)
{
  // Called on worker_thread_.

  bool consider_seq_num = options != kTimeOnly;
  bool consider_timestamp = options != kSeqNumOnly;
  Timestamp now = clock_->CurrentTime();
  std::vector<uint16_t> nack_batch;
  auto it = nack_list_.begin();
  while (it != nack_list_.end()) {
    NackInfo &ninfo = it->second;
    bool delay_timed_out = now - ninfo.created_at_time >= send_nack_delay_;
    bool nack_on_rtt_passed = now - ninfo.sent_at_time >= rtt_;
    bool nack_on_seq_num_passed =
        ninfo.sent_at_time.IsInfinite() &&
        AheadOrAt(latest_seq, ninfo.send_at_seq_num);
    if (delay_timed_out && ((consider_seq_num && nack_on_seq_num_passed) ||
                            (consider_timestamp && nack_on_rtt_passed))) {
      nack_batch.emplace_back(ninfo.seq_num);
      ++ninfo.retries;
      ninfo.sent_at_time = now;
      if (ninfo.retries >= kMaxNackRetries) {
        RTC_LOG(LS_WARNING) << "Sequence number " << ninfo.seq_num
                            << " removed from NACK list due to max retries.";
        it = nack_list_.erase(it);
      } else {
        ++it;
      }
      continue;
    }
    ++it;
  }
  return nack_batch;
}

void NackRequester::GenFecForResend(std::vector<uint16_t> resend_seqs)
{
  std::vector<uint16_t> seqs_for_fec;
  for (uint16_t seq : resend_seqs) {
    auto it = seq_resend_cnt_.find(seq);
    if (it == seq_resend_cnt_.end()) {
      // 还没重传过
    }
  }
}

} //webrtc
