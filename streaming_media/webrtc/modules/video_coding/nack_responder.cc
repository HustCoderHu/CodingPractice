#include "modules/video_coding/nack_responder.h"

namespace webrtc {

void NackResponder::OnNack(const NackPkt &pkt)
{
  //  std::vector<uint64_t> seqs_for_fec;
  uint8_t loss; // 1/256
//  (batch_size+1) * loss* x/256 <= 1
  // x: 1.1 for 1st
  //    1.2 for 2nd+
  uint16_t first_batch_size = 256 / loss / 1.1 - 1;
  uint16_t twice_batch_size = 256 / loss / 1.2 - 1;
//  if (batch_size * loss == 256)
//    --batch_size;
  // 第一次重传补偿 loss_rate 相近的冗余
  // 后续补偿更多
  std::vector<uint64_t> seqs_first_resend_for_fec;
  std::vector<uint64_t> seqs_twice_resend_for_fec;

  for (uint64_t seq : pkt) {
    auto it = seq_resend_cnt_.find(seq);
    if (it == seq_resend_cnt_.end()) {
      // 还没重传过
      if (seqs_not_resended_.AddSeq(seq) < first_batch_size)
        continue;
      seqs_not_resended_.GenSeqsForFec(seqs_first_resend_for_fec);
      seq_resend_cnt_.insert({seq, 1});
      // GenFec seqs_for_fec
      std::vector<FecForResendPkt> fec_pkts;

      continue;
    }

    ++it->second;

    if (seqs_resended_once_more_.AddSeq(seq) < twice_batch_size)
      continue;
    seqs_resended_once_more_.GenSeqsForFec(seqs_twice_resend_for_fec);
    // GenFec seqs_for_fec
    std::vector<FecForResendPkt> fec_pkts;
    // send fec_pkts
  }

  // 重传包交织发送
}

} // namespace webrtc
