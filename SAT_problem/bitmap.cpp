#include "bitmap.h"
#include <stdio.h>
#include <string.h>

BitMap::BitMap(int _len)
  : len(_len)
{
  ints = (_len + 31) / 32;
  intmap_ = new int[ints];
  memset(intmap_, 0, sizeof(intmap_[0]) * ints);
}

bool BitMap::set(unsigned int pos, bool flag)
{
  if (pos >= len) {
    printf("err: pos >= len, %d > %d\n", pos, len);
    return false;
  }

  unsigned int ruler;
  unsigned int int_pos = pos >> 5; // pos / 32
  unsigned int bit_pos = pos & ((1 << 6) - 1); // = pos & b'0001 1111

  ruler = 1 << bit_pos;
  if (flag)
    intmap_[int_pos] |= ruler;
  else {
    ruler ~= ruler;
    intmap_[int_pos] &= ruler;
  }
}

void BitMap::reset()
{
  memset(intmap_, 0, sizeof(intmap_[0]) * ints);
  return;
  for (int i = 0; i < ints; ++i)
    intmap_[i] = 0;
}

//int BitMap::get()
//{
//  for (unsigned int i = 0; i < ints; ++i) {
//    if (intmap_[i] != 0) {
//      unsigned ruler = 0x1;
//      unsigned int j = 0;

//      while ((intmap_[i] & ruler) == 0) {
//        ++j;
//        ruler <<= 1;
//      }
//      return (i << 5) + j;
//    }
//  }
//  return -1;
//}

bool BitMap::get(unsigned int pos)
{
  if (pos >= len) {
    printf("err: pos >= len, %d > %d\n", pos, len);
    return false;
  }

  unsigned int int_pos = pos >> 5; // pos / 32
  unsigned int bit_pos = pos & ((1 << 5) - 1); // = pos & b'0001 1111

  unsigned int ruler = 1 << bit_pos;
  if ((intmap_[int_pos] & ruler) != 0)
    return true;
  return false;
}

bool BitMap::isAllFalse()
{
  for (int i = 0; i < len; ++i) {
    if (intmap_[i] != 0)
      return false;
  }
  return true;
}

void BitMap::resize(int _len)
{
  if (_len <= len)
    return;
  int _ints = (_len + 31) / 32;
  unsigned int *intmap__ = new int[_ints];
  memset(intmap__, intmap_, sizeof(intmap_[0]) * ints);
  delete[] intmap_;
  len = _len;
  ints = _ints;
  intmap_ = intmap__;
}
