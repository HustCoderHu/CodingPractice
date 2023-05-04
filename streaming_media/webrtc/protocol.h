#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <string>
#include <vector>

using std::string;
using std::vector;

struct PMediaRSFECData : public Marshallable
{
    enum { uri = (81018 << 8 | SESSION_SVID) };

    StreamGroupID streamGroupId;
    UID uid;
    uint32_t fec_pkt_seq; // fec 包 单增序号
    uint32_t stampc;//FEC包发送时间，带宽评估等用到
    uint32_t firstSeq;//该分组M个源包中第一个源包序号，与N结合，就可以判断出哪些源包属于此分组
    uint16_t groupId;	  // 该分组的序号，最大256，标识每个分组
    uint8_t actualSeqFlag; // 0: vecSeqGap 携带丢失的Seq与FirstSeq差值
                               // 1: vecSeqGap 携带跟上一个seq的差值;
                           // 2: 连续编码模式，vecSeqGap无关
    uint8_t srcBlkCnt;//分组源包数量 M，由服务器配置
    uint8_t rddBlkCnt;//分组补偿包数量 N，根据丢包率进行计算
    uint8_t curBlkId;//当前补偿包序号，取值范围M，M+1......M+N-1
    uint8_t seqStep;	  // 分组内相邻的两个数据包SEQ的差，预留交织
    vector<uint8_t> vecSeqGap;
    string fecData;//整个PStreamData3的包内容进行FEC
};

struct RSFecPkt
{
  uint8_t M;  // 源包数量
  uint8_t N;  // 冗余包
  uint8_t rdd_offset; // 每个冗余包在分组里的偏移
  uint8_t block_id;   // 分组号
  uint8_t interleaving_step;
  uint64_t first_src_seq;
  vector<uint8_t> except_seq_offset;
  // 跳过部分服务端也没有收到的 seq = firstSrcSeq + except_seqs[i]
  string data;
  FecPkt() {}
};

struct XorFecPkt
{
  uint64_t base_seq;
  vector<uint8_t> seq_offset;
  string data;
  FecPkt() {}
};

struct MediaPkt
{
  uint64_t seq;
  string data;
  MediaPkt() {}

  void Parse(const char* d, uint32_t len);
};

struct ResendPkt
{
  uint64_t seq;
  vector<uint8_t> fec_src_seqs;

  union {
    struct {
      uint8_t flag;

    };
    struct {
      int fec_pkt_flag:1;
      int fec_pkt_flag:1;
    };
  };

  string data;
  ResendPkt() {}
};

struct FecForResendPkt
{
  uint64_t seq;
  string data;
  std::set<uint64_t> protect_seqs;
  FecForResendPkt() {}
};

struct NackPkt
{
  std::vector<uint64_t> seqs;
  NackPkt() {}
};

#endif // PROTOCOL_H
