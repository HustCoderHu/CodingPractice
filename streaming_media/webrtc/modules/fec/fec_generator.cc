#include "modules/fec/fec_generator.h"

namespace webrtc {

void FecEncoder::SetFecRate(double r)
{

}

void RsfecGenerator::UpdateLossRate(uint16_t new_rate)
{
  loss_rate = new_rate;
}

/**
 * @brief 调整 I 帧 p帧的冗余系数
 * @param v
 */
void RsfecGenerator::UpdateCoefficient(double v)
{
  protect_gain_iframe *= v;
  double *pframe_gain = protect_gain_pframe[0];
  for (uint16_t i = 0; i < 3; ++i, ++pframe_gain) {
    double target = (*pframe_gain) * v;
    if (target < 1.00001)
      *pframe_gain = 1.0;
    else
      *pframe_gain = target;
  }
}

} // namespace webrtc
