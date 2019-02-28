#include "bitmap.h"
#include <stdio.h>
#include <string.h>

BitMap::BitMap(uint32_t _len)
{
  len = _len;
  ints = (_len + 31) / 32;
  intmap_ = new uint32_t[ints];
  memset(intmap_, 0, sizeof(intmap_[0]) * ints);
}

bool BitMap::set(uint32_t pos, bool flag)
{
  if (pos >= len) {
    printf("err: pos >= len, %d > %d\n", pos, len);
    return false;
  }

  uint32_t ruler;
  uint32_t int_pos = pos >> 5; // pos / 32
  uint32_t bit_pos = pos & ((1 << 6) - 1); // = pos & b'0001 1111

  ruler = 1 << bit_pos;
  if (flag)
    intmap_[int_pos] |= ruler;
  else {
    ruler = ~ruler;
    intmap_[int_pos] &= ruler;
  }
}

void BitMap::reset()
{
  memset(intmap_, 0, sizeof(intmap_[0]) * ints);
  return;
  for (uint32_t i = 0; i < ints; ++i)
    intmap_[i] = 0;
}

//int BitMap::get()
//{
//  for (uint32_t i = 0; i < ints; ++i) {
//    if (intmap_[i] != 0) {
//      unsigned ruler = 0x1;
//      uint32_t j = 0;

//      while ((intmap_[i] & ruler) == 0) {
//        ++j;
//        ruler <<= 1;
//      }
//      return (i << 5) + j;
//    }
//  }
//  return -1;
//}

bool BitMap::get(uint32_t pos)
{
  if (pos >= len) {
    printf("err: pos >= len, %d > %d\n", pos, len);
    return false;
  }

  uint32_t int_pos = pos >> 5; // pos / 32
  uint32_t bit_pos = pos & ((1 << 5) - 1); // = pos & b'0001 1111

  uint32_t ruler = 1 << bit_pos;
  if ((intmap_[int_pos] & ruler) != 0)
    return true;
  return false;
}

bool BitMap::isAllFalse()
{
  for (uint32_t i = 0; i < len; ++i) {
    if (intmap_[i] != 0)
      return false;
  }
  return true;
}

void BitMap::resize(uint32_t _len)
{
  if (_len <= len)
    return;
  uint32_t _ints = (_len + 31) / 32;
  uint32_t *intmap__ = new uint32_t[_ints];
  memcpy(intmap__, intmap_, sizeof(intmap_[0]) * ints);
  delete[] intmap_;
  len = _len;
  ints = _ints;
  intmap_ = intmap__;
}

void BitMap::OR(BitMap *other)
{
  for (uint32_t i = 0; i < ints && i < other->ints; ++i) {
    intmap_[i] ^= other->intmap_[i];
  }
}
