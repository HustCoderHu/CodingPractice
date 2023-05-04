#ifndef LOSS_PATTERN_ANALYZE_H
#define LOSS_PATTERN_ANALYZE_H

#include <vector>
#include <stdint.h>

class LossPatternAnalyzer
{
public:
  LossPatternAnalyzer(uint32_t block_size):block_size_(block_size)
  {

  }
  /**
   * @brief 计算分组丢包率
   * @param loss_rates
   * @param loss_seqs
   * @param block_size
   * @param interleaving_step  交织模式步长
   */
  void CalBlockLossRate(const std::vector<uint64_t>& loss_seqs);
  void SelectBestStepAndRate();

  uint32_t block_size_;
  std::vector<uint8_t> loss_count_step_1_;
  std::vector<uint8_t> loss_count_step_2_;
  std::vector<uint8_t> loss_count_step_3_;
};



void SelectBestStepAndRate();

#endif // LOSS_PATTERN_ANALYZE_H
