#pragma once
#include <stdint.h>
#include <bitset>
#include <vector>
#include <map>
#include <string.h>

using std::vector;
using std::map;

namespace webrtc {

uint8_t CountNotZero(uint64_t v)
{
  uint8_t n = 0;
  while (v != 0) {
    ++n;
    v = v & (v-1);
  }
  return n;
}

struct FecPktRecvStat{
  uint16_t group_id;
  uint64_t recved_bitmap;

  uint8_t n_recved;
  uint8_t n_rdd_blk; // fec 总包数 N

  void Mashall(char *d)
  {
    memcpy(d, group_id, 2);
    memcpy(d+2, recved_bitmap, 4);
    n_recved = CountNotZero(recved_bitmap);
  }
//  std::bitset<64> recved;
};

class ResendGenerator
{
public:
  void OnFecPktRecvStat(const FecPktRecvStat& s);

  void GetUnrecvedFecPktsBlkId(vector<uint8_t> ids);

  map<uint16_t, FecPktRecvStat> fec_pkts_recv_stats_;
};

} // namespace webrtc
