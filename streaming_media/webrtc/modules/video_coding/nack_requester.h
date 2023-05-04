#pragma once

#include <stdint.h>
#include <vector>
#include <set>
#include <map>
#include "system_wrappers/include/clock.h"
#include "api/units/timestamp.h"
#include "modules/include/module_common_types.h"

namespace webrtc {

class NackRequester
{
public:
  NackRequester();
  ~NackRequester();

  void ProcessNacks();// override;
  int OnRecvPacket(uint64_t seq, bool is_keyframe, bool is_resend,
                   bool is_recovered);

  enum NackFilterOptions { kSeqNumOnly, kTimeOnly, kSeqNumAndTime };
  struct NackInfo {
    NackInfo();
    NackInfo(uint64_t seq_num,
             uint64_t send_at_seq_num,
             Timestamp created_at_time);

    uint64_t seq_num;
    uint64_t send_at_seq_num;
    Timestamp created_at_time;
    Timestamp sent_at_time;
    int retries;
  };

  void AddPacketsToNack(uint16_t seq_num_start, uint16_t seq_num_end);
  // Removes packets from the nack list until the next keyframe. Returns true
  // if packets were removed.
  bool RemovePacketsUntilKeyFrame();
  std::vector<uint16_t> GetNackBatch(NackFilterOptions options);

  void GenFecForResend(std::vector<uint16_t> resend_seqs);

  Clock* const clock_;

  std::map<uint64_t, NackInfo> nack_list_;

  std::set<uint64_t, NackInfo> recovered_list_;

  uint64_t latest_seq;

  NackSender* const nack_sender_;


};

} //webrtc
