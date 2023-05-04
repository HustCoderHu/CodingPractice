#ifndef INTERLEAVING_UTIL_H
#define INTERLEAVING_UTIL_H

#include <stdint.h>
#include <vector>

#include "api/units/timestamp.h"

struct SeqBlk
{
  SeqBlk(uint64_t seq, uint32_t pos) :start_pos(pos), end_pos(pos) {
    seqs.push_back(seq);
  }
  std::vector<uint64_t> seqs;
  uint32_t start_pos;
  uint32_t end_pos;

  void push_back(uint64_t seq, uint32_t pos) {
    seqs.push_back(seq);
    end_pos = pos;
  }

  /**
   * @brief MeanDistance
   * @return v%
   */
  uint32_t MeanDistance() {
    if (seqs.size() == 1)
      return 0;
    return (end_pos-start_pos) * 100 / (seqs.size()-1);
    // todo vec[pos]
  }
};

struct FecStat
{
  FecStat() {}

  uint8_t interleaving_step;
  uint16_t recovery_rate; // plus 1000
  Timestamp at_time;
};

/**
 * @brief CalInterleavingStep
 * @param rec_list
 * @param loss_list
 * @param cur_step
 * @param pkts_per_sec
 * @param check_ms
 * @param latest_seq
 * @return
 */
uint32_t CalInterleavingStep(vector<uint64_t> rec_list,
                             vector<uint64_t> loss_list,
                             uint8_t cur_step,
                             uint32_t pkts_per_sec,
                             uint32_t check_ms,
                             uint64_t latest_seq);

#endif // INTERLEAVING_UTIL_H
