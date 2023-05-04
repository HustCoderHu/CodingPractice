#include <stdint.h>
#include <vector>
#include <map>

#include "modules/fec/interleaving_util.h"

using std::vector;
using std::map;

/**
 * @brief 把数列拆分成连续的小段， 相邻差值 <= 2视为连续
 * @param seqblks: key: 记录连续丢包 分块的第一个seq
 * @param loss_list
 */
static void split2blocks(map<uint64_t, SeqBlk> &seqblks,
                  vector<uint64_t> loss_list)
{
  auto it_loss = loss_list.begin();
  uint64_t last_seq = *it_loss;
  ++it_loss;

  uint32_t pos = 1;
  auto _pair_it_bool = seqblks.emplace(last_seq, pos);
  SeqBlk *last_blk = &(_pair_it_bool.first->second);
  for (; it_loss != loss_list.end(); ++it_loss, ++pos) {
    uint64_t seq = *it_loss;
//    ++count_step[seq - last_seq];
    if (seq - 3 >= last_seq) {
      // 不连续，生成新块
      auto _pair_it_bool = seqblks.emplace(seq, seq, pos);
      last_blk = &(_pair_it_bool.first->second);
    } else {
      last_blk->push_back(seq, pos);
//      SeqBlk &_blk = seqblks.rbegin()->second;
//      _blk.seqs.push_back(seq);
//      _blk.end_pos = seq;
    }
    last_seq = seq;
  }
}

uint32_t CalInterleavingStep(vector<uint64_t> rec_list,
                             vector<uint64_t> loss_list,
                             uint8_t cur_step,
                             uint32_t pkts_per_sec,
                             uint32_t check_ms,
                             uint64_t latest_seq)
{
  if (loss_list.empty())
    return 1;

  uint64_t start_seq = latest_seq - check_ms * pkts_per_sec / 1000;

  auto it_loss = std::lower_bound(loss_list.begin(),
                                  loss_list.end(), start_seq);

  vector<uint64_t> recent_loss;

  uint64_t last_seq = 0;
  uint32_t count_step[4] = {0, 0, 0, 0}; // step 1, 2, >=3

  if (it_loss == loss_list.end())
    return 1;
  last_seq = *it_loss;
  ++it_loss;
  uint32_t count_loss = 0;

  auto rit_rec = rec_list.rbegin();
  uint32_t count_rec = 0;
  for ( ; rit_rec != rec_list.rend(); ++rit_rec) {
    if (*rit_rec < start_seq)
      break;
    ++count_rec;
  }

  uint32_t fec_interleaving_trigger_lvl = 80;
  if (count_rec > count_loss * fec_interleaving_trigger_lvl/100) {
    // fec enough
    return cur_step;
  }

  // 开始对丢包分布分析
  // 30Mbps  3750 pkts/sec
  // 最近 200ms 包数 750
  // 50% 丢包 375
  map<uint64_t, SeqBlk> seqblks;
  split2blocks(seqblks, loss_list);

  uint32_t blk_step1_num = 0;
  uint32_t blk_step2_num = 0;
  for (auto &p : seqblks) {
    SeqBlk &blk = p.second;
    if (blk.seqs.size() <= 3)
      continue;
    uint32_t mean_dis = blk.MeanDistance();
    if (mean_dis < 150)
      ++blk_step1_num;
    else
      ++blk_step2_num;
  }

  uint32_t step_2_trigger_lvl = 125; // / 1000
//  uint32_t step_3_trigger_lvl = 250; // / 1000
  uint32_t total_blks = seqblks.size();
  uint32_t trigger_2 = total_blks * step_2_trigger_lvl / 1000;
//  uint32_t trigger_3 = total_blks * step_3_trigger_lvl / 1000;

  uint32_t next_step = 1;
  if (blk_step1_num+blk_step2_num >= trigger_2) {
    next_step = 2;
    if (blk_step2_num >= blk_step1_num * 7/5) // 40%
      next_step = 3;
  }
  return next_step;


}
