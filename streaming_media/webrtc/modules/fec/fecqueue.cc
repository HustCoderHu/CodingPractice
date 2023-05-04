#include "fecqueue.h"
#include "cauchy_256.h"

#include <vector>
using std::vector;

void FecBlock::GenFec(vector<MediaPkt *> &fecPkts)
{

}

uint32_t FecBlock::CountRecvedSrcPktNum()
{
  if (src_pkt_num_!=0)
    return src_pkt_num_;

  for (uint32_t seq : seqs_) {
    if (1) // seq has recved
      ++src_pkt_num_;
  }
}

void FecEncoder::Encode(vector<string> &fecPkts, const vector<MediaPkt> &pkts)
{
  int m = pkts.size();
  int n = 0; // @todo  according to loss rate
  const unsigned char* data_ptrs[256];

  uint32_t row = 0;
  for (MediaPkt &pkt : pkts) {
    if (blk_size > pkt.data.size()) {
      pkt.data.append(blk_size - pkt.data.size(), 0x0);
    }
    data_ptrs[row++] = pkt.data;
  }

  if (n > rec_blks_cnt) {
    if (rec_blks!=NULL)
      delete[] rec_blks;
    rec_blks = new uint8_t[n * blk_size];
  }

  if (cauchy_256_encode(m, n, data_ptrs, rec_blks, blk_size)) {
    // error
    return;
  }

  fecPkts.reserve(n);
  for (int ii = 0; ii < n; ++ii) {
    uint8_t *blk = rec_blks + ii*blk_size;
    fecPkts.push_back(std::move(std::string(blk, blk_size)));
  }
}

void FecQueue::OnSrcPkt(const MediaPkt &pkt)
{
  if (decoders_.empty())
    return ;

  auto it = decoders_.lower_bound(pkt.seq);
  if (it == decoders_.end()) {
    // 还没有 fec 包，不知道起始 seq
    return;
  }
  --it;

  FecDecoder &decoder = it->second;
  if (decoder.IsPktProtected(pkt.seq) == false)
    return;

//  if (pkt.seq > fecblk.seqs_.rbegin()) {
//    FUNLOG(Debug, "seq greater than last %u-%u-%u", pkt.seq,
//           it->first, fecblk.cfg_m_src_pkt_num_);
//    return;
//  }

  decoder.OnSrcPkt(pkt);
}

void FecDecoder::OnSrcPkt(const MediaPkt &pkt)
{
  if (recovered)
    return;

  if (IsSrcPktsCompleted()) {
    //源包收齐
    return;
  }
}

void FecDecoder::OnFecPkt(const PMediaRSFECData &pkt,
                          vector<MediaPkt> &recoveredSrcPkts)
{
  if (IsSrcPktsCompleted()) {
    //源包收齐
//    return ;
    // 不直接返回, 统计 fec 到达率使用
  }

  if (fecpkts_.empty())
    fecpkts_.reserve(pkt.rddBlkCnt);

  fecpkts_.push_back(pkt);
  if ( ReadyRecover() == false) {
    // 不够恢复
    return;
  }

  vector<string> fecPkts;
  Decode(recoveredSrcPkts, fecPkts);
  return;
//  if (fecpkts.size() == rddBlkCnt) {
//    // fec 包齐
  //  }
}

bool FecDecoder::ReadyRecover()
{

}

void FecDecoder::Decode(vector<MediaPkt> &recoveredSrcPkts,
                        const vector<std::string> &fecPkts)
{
  Block blocks[256];

  if (cauchy_256_decode(blk_.cfg_m_src_pkt_num_, blk_.cfg_n_rdd_blk_num_,
                        blocks, blk_.blockSize)) {
    // error
    return;
  }

  uint32_t recovered_src_pkt_num = blk_.cfg_m_src_pkt_num_ - src_pkt_num_;
  recoveredSrcPkts.reserve(recovered_src_pkt_num);
  Block *blk = blocks + src_pkt_num_;
  for (uint32_t cnt = 0; cnt < recovered_src_pkt_num; ++cnt, ++blk) {
    unsigned char *d = blk->data;
    uint32_t len = *((uint32_t*)d); // 前 4 个字节 len 小端
    MediaPkt pkt;
    pkt.Parse(d, len);
    recoveredSrcPkts.push_back(std::move(pkt));
  }
}
