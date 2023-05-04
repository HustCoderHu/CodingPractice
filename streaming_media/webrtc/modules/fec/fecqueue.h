#ifndef FECQUEUE_H
#define FECQUEUE_H

#include <set>
#include <map>
#include <stdint.h>

#include "protocol.h"

using std::set;
using std::map;
//using std::vector;

class FecBlock
{
public:
  void OnSrcPkt(const MediaPkt &pkt);

  void GenFec(vector<MediaPkt*> &fecPkts);

  uint32_t CountRecvedSrcPktNum();

  uint8_t cfg_m_src_pkt_num_;//分组源包数量 M，由服务器配置
  uint8_t cfg_n_rdd_blk_num_;//分组补偿包数量 N，根据丢包率进行计算

  uint32_t blockSize;
  uint32_t groupId;
  set<uint32_t> seqs_;//记录源码的位置
};

class FecDecoder
{
public:
  void OnSrcPkt(const MediaPkt &pkt);
  void OnFecPkt(const PMediaRSFECData &pkt, vector<MediaPkt> &recoveredSrcPkts);

  bool ReadyRecover() { return src_pkt_num_+fecpkts_.size() >= blk_.cfg_m_src_pkt_num_; }
  void Decode(vector<MediaPkt> &recoveredSrcPkts,
              const vector<std::string> &fecPkts);

  bool IsSrcPktsCompleted() { return src_pkt_num_ >= blk_.cfg_m_src_pkt_num_; }
  void IsPktProtected(uint32_t seq) { return blk_.seqs_.find(seq) != blk_.seqs_.end(); }

  FecBlock blk_;

  //  map<uint32_t, PMediaRSFECData> fecpkts;
  vector<PMediaRSFECData> fecpkts_ ;

  bool recovered;
  uint8_t src_pkt_num_; // 收到的源包数量
  uint8_t fec_pkt_num_;

  uint8_t *rec_blks;
  uint8_t rec_blks_cnt;
  uint32_t blk_size;
};

class FecQueue
{
public:
  FecQueue();
  ~FecQueue();

  void OnSrcPkt(const MediaPkt& pkt);

  map<uint32_t, FecDecoder> decoders_;
//  map<uint32_t, FecBlock> decoders_;

//  FecEncoder encoder_;
};

#endif // FECQUEUE_H
