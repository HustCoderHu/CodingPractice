#pragma once

#include <stdint.h>
#include <map>

#include "protocol.h"

namespace webrtc {

template <typename T, size_t kSize>
class RingBuf
{
  size_t Capacity() { return kSize; }
  size_t Size();

  size_t CurrentIndex();

  // Returns the element at index |n| (% |kSize|).
  //
  // n = 0 returns the oldest value and
  // n = bufferSize() - 1 returns the most recent value.
  const T& ReadBuffer(size_t n) const {
    const size_t buffer_index = BufferIndex(n);
    CHECK(IsFilledIndexByBufferIndex(buffer_index));
    return buffer_[buffer_index];
  }

  void SaveToBuffer(const T& value) {
//    push_index_ %= kSize;
    buffer_[push_index_ % kSize] = value;
    ++push_index_;
  }

private:
  inline size_t BufferIndex(size_t n) const {
    return (push_index_ + n) % kSize;
  }

  // This specialization of |IsFilledIndex| is a micro-optimization that enables
  // us to do e.g. `CHECK(IsFilledIndex(n))` without calling |BufferIndex|
  // twice. Since |BufferIndex| involves a % operation, it's not quite free at a
  // micro-scale.
  inline bool IsFilledIndexByBufferIndex(size_t buffer_index) const {
    return buffer_index < push_index_;
  }

  T buffer_[kSize];
  size_t push_index_;
};

class NackResponder
{
public:
  NackResponder();
  ~NackResponder();

  void OnNack(const NackPkt& pkt);

  // seq has been resend n times;
  Clock* const clock_;

  struct CachedSeqs
  {
    RingBuf<uint64_t, 64> cached_seqs_for_fec_;
    size_t read_index_;
    uint16_t cached_cnt_;
    cached_seqs() {}
    uint16_t AddSeq(uint64_t seq) {
      cached_seqs_for_fec_.SaveToBuffer(seq);
      ++cached_cnt_;
      return cached_cnt_;
    }
    void GenSeqsForFec(std::vector<uint64_t> seqs) {
      while(cached_cnt_ != 0) {
        uint64_t seq = cached_seqs_for_fec_.ReadBuffer(read_index_);
        seqs.push_back(seq);
        --cached_cnt_;
        ++read_index_;
      }
    }
  };

  CachedSeqs seqs_not_resended_;
  CachedSeqs seqs_resended_once_more_;

  std::map<uint64_t, uint8_t> seq_resend_cnt_;
};


} // namespace webrtc
