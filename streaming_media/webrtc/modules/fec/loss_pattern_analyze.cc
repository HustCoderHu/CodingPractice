#include "modules/fec/loss_pattern_analyze.h"

/**
 * @brief 步长 1 的分组丢包率
 * @param loss_rates
 * @param loss_seqs
 * @param block_size
 * @note
 *  i.e. block_size = 8
 *   1,2,3,   9,10,   16,18,20,21
 *   block0  block1    block2
 *    3/8     2/8       4/8
 */
static void _CalBlockLossRate(std::vector<uint8_t> &loss_count,
                              const std::vector<uint64_t> &loss_seqs,
                              uint32_t block_size)
{
  uint32_t loss_in_block = 0;
  uint32_t block_idx = 0;
  auto it = loss_seqs.begin();
  for (; it != loss_seqs.end(); ++it) {
    if ( *it < (block_idx+1)*block_size ) {
      //属于分组 block_idx
      ++loss_in_block;
    } else {
      // 属于下一个分组
      ++block_idx;
      loss_count.push_back(loss_in_block);
      loss_in_block = 1; // 重新计数
    }
  }
  // @todo xiaohu 处理一下最后一个不完整的 block
}

void LossPatternAnalyzer::CalBlockLossRate(
    const std::vector<uint64_t> &loss_seqs)
{
  std::vector<uint64_t> mod_step_0;
  uint64_t start = loss_seqs.front();
  // step 1
  _CalBlockLossRate(loss_count_step_1_, mod_step_0, block_size_);

  std::vector<uint64_t> mod_step_1;
  auto it = loss_seqs.begin();
  mod_step_0.push_back(0);
  // 按 step 分组分别计算
  for (; it != loss_seqs.end(); it++) {
    uint64_t seq_diff = *it - start;
    uint64_t i = seq_diff >> 1; // % 2
    if (seq_diff & 0x1)
      mod_step_1.push_back(i);
    else
      mod_step_0.push_back(i);
  }
  _CalBlockLossRate(loss_count_step_1_, mod_step_0, block_size_);
  _CalBlockLossRate(loss_count_step_2_, mod_step_1, block_size_);

  // step 2
  // 2i, 2i+1

  // 3i, 3i+1, 3i+2
  std::vector<uint64_t> mod_step_2;
  for (; it != loss_seqs.end(); it++) {
    uint64_t seq_diff = *it - start;
    uint64_t i = seq_diff / 3; // % 2
    uint64_t step_idx = seq_diff - i * 3;
    switch (step_idx) {
      case 0:
        mod_step_0.push_back(step_idx);
        break;
      case 1:
        mod_step_1.push_back(step_idx);
        break;
      case 2:
        mod_step_2.push_back(step_idx);
        break;
    }
  }
  _CalBlockLossRate(loss_count_step_1_, mod_step_0, block_size_);
  _CalBlockLossRate(loss_count_step_2_, mod_step_1, block_size_);
  _CalBlockLossRate(loss_count_step_3_, mod_step_2, block_size_);
}

void LossPatternAnalyzer::SelectBestStepAndRate()
{
  uint8_t start_pos = 85; // 85/100
  uint8_t step_1_percentage_loss =
      loss_count_step_1_[loss_count_step_1_.size() * start_pos / 100];

  uint8_t step_2_percentage_loss =
      loss_count_step_2_[loss_count_step_2_.size() * start_pos / 100];

  uint8_t step_3_percentage_loss =
      loss_count_step_3_[loss_count_step_3_.size() * start_pos / 100];

  uint8_t step_n = 1;
  uint8_t step_n_min_loss = step_1_percentage_loss;

  if (step_2_percentage_loss < step_n_min_loss) {
    step_n = 2;
    step_n_min_loss = step_2_percentage_loss;
  }

  if (step_3_percentage_loss < step_n_min_loss) {
    step_n = 3;
    step_n_min_loss = step_3_percentage_loss;
  }

  float fec_rate_start = step_n_min_loss * 1.0 / block_size_;
  return ;
}

void LossPatternAnalyzer_test()
{
  std::vector<uint8_t> &loss_count;
  for (uint32_t i = 0; i < 5; ++i) {
    uint8_t cnt = 2+i;
    for (uint32_t j = 0; j < 5; ++j)
      loss_count.push_back(cnt);
  }

  loss_count.push_back(15);
  loss_count.push_back(20);
  loss_count.push_back(25);

  uint16_t sum = 0;
  for (uint8_t n : loss_count)
    sum += n;

  uint16_t mean = sum / loss_count;
}

/**
 * @brief 20 组 丢包分析, 决策 fec 取多少
 * 能满足恢复数量 >= sum_estimated_recovered
 */
void blockFecAnalyze(uint16_t step) {
  uint16_t block_cnt = 20;
  uint16_t pkt_range_per_block = 15;
  uint16_t loss_cnt[block_cnt]; // 每范围 15 个包，记录丢失数量
  // sort  从小到大

  uint16_t recovered_cnt[16]; // 1...15 冗余情况下恢复包数量

  uint16_t sum_estimated_recovered;
  // 计算需要恢复的比例 p=(total_loss_pkt - sum_estimated_recovered)/total_loss_pkt,
  // 满足 p * loss_rate * rtt < max_pending

  uint16_t design_recovered = 1;
  uint16_t j = 0;
  uint16_t tmp_sum = 0;
  uint16_t *loss_cnt_i = loss_cnt;
  for (; design_recovered <= 15; ++design_recovered) {
    // 每上移一层就累加一部分恢复数量
    for (; j < 20; ++j) {
      if (*loss_cnt_i >= design_recovered) {
        // 后面的丢失太多，只能恢复冗余的量
        tmp_sum += 20 - j;
        break;
      }
      ++loss_cnt_i;
    }
    recovered_cnt[design_recovered] = tmp_sum;
    if (tmp_sum >= sum_estimated_recovered) {
      // 找到恢复量能满足 sum_estimated_recovered 的位置
      break;
    }
  }
}
