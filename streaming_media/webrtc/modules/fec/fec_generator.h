#ifndef RSFEC_GENERATOR_H
#define RSFEC_GENERATOR_H

#include <memory>
#include "protocol.h"
#include "modules/fec/fecqueue.h"
#include "api/units/timestamp.h"

namespace webrtc {

template <typename T>
struct ValueRecord
{
  ValueRecord() {}
  void update(T v, Timestamp at_time) {
    last_ = cur_;
    cur_ = v;
    lastTime = updateTime;
    updateTime = at_time;
  }

  T last_;
  T cur_;
  Timestamp updateTime;
  Timestamp lastTime;
};

class FecEncoder
{
public:
  void SetFecRate(double r);
  void OnSrcPkt(const MediaPkt &pkt);
  void Encode(vector<std::string> &fecPkts, const vector<MediaPkt> &pkts);

  FecBlock blk_;

  uint8_t *rec_blks;
  uint8_t rec_blks_cnt;
  uint32_t blk_size;
};

class FecGenerator
{
public:
  virtual ~FecGenerator();
  virtual void AddPacketAndGenerateFec(const MediaPkt& pkt) = 0;
  virtual std::vector<std::unique_ptr<MediaPkt> > GetFecPackets() = 0;
  virtual void UpdateCoefficient(double v);
};

class RsfecGenerator : public FecGenerator
{
public:
  // Adds a media packet to the internal buffer. When enough media packets
  // have been added, the FEC packets are generated and stored internally.
  // These FEC packets are then obtained by calling GetFecPackets().
  void AddPacketAndGenerateFec(const MediaPkt& pkt) override;
  std::vector<std::unique_ptr<MediaPkt> > GetFecPackets() override;
  /**
   * @brief 获取 fec 分组号
   * @param 源包 seq
   * @return
   */
  uint16_t GetGroupId(uint64_t src_pkt_seq);

  void UpdateLossRate(uint16_t new_rate);

  void UpdateCoefficient(double v) override;

  map<uint64_t, FecEncoder> iframe_encoders_;
  map<uint64_t, FecEncoder> pframe_encoders_;

  uint16_t loss_rate;
//  uint8_t protect_gain; // 百分数

  double protect_gain_iframe = 1.25;
  double protect_gain_pframe[3] = {
    1.16, 1.12, 1.08
  };

  // 不同帧使用不同系数
  static const double kProtectGainIframe = 1.25;
  static const double kProtectGainPframe[3] = {
    1.16, 1.12, 1.08
  };
//  double kProtectGainPframe[3] = {
//    7/18, 6/18, 5/18
//  };
};

} // namespace webrtc

#endif // RSFEC_GENERATOR_H
