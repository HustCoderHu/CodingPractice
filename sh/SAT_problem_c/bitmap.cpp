#include "bitmap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

BitMap *createBitmap(uint32_t _len)
{
  BitMap *bmap = (BitMap*)malloc(sizeof(*bmap));
  bmap->len = _len;
  bmap->ints = (_len + 31) / 32;
  bmap->intmap_ = new uint32_t[bmap->ints];
  memset(bmap->intmap_, 0, sizeof(bmap->intmap_[0]) * bmap->ints);
  return bmap;
}

bool set(BitMap *bmap, uint32_t pos, bool flag)
{
  if (pos >= bmap->len) {
    printf("%s err: pos >= len, %d > %d\n", __FUNCTION__, pos, bmap->len);
    return false;
  }

  uint32_t ruler;
  uint32_t int_pos = pos >> 5; // pos / 32
  uint32_t bit_pos = pos & ((1 << 6) - 1); // = pos & b'0001 1111

  ruler = 1 << bit_pos;
  if (flag)
    bmap->intmap_[int_pos] |= ruler;
  else {
    ruler = ~ruler;
    bmap->intmap_[int_pos] &= ruler;
  }
  return true;
}

void reset(BitMap *bmap)
{
  memset(bmap->intmap_, 0, sizeof(bmap->intmap_[0]) * bmap->ints);
  return;
}

bool get(BitMap *bmap, uint32_t pos)
{
  if (pos >= bmap->len) {
    printf("%s err: pos >= len, %d > %d\n", __FUNCTION__, pos, bmap->len);
    return false;
  }

  uint32_t int_pos = pos >> 5; // pos / 32
  uint32_t bit_pos = pos & ((1 << 5) - 1); // = pos & b'0001 1111

  uint32_t ruler = 1 << bit_pos;
  if ((bmap->intmap_[int_pos] & ruler) != 0)
    return true;
  return false;
}

bool isAllFalse(BitMap *bmap)
{
  for (uint32_t i = 0; i < bmap->ints; ++i) {
    if (bmap->intmap_[i] != 0)
      return false;
  }
  return true;
}

void mayResize(BitMap *bmap, uint32_t _len)
{
  if (_len > bmap->len)
    resize(bmap, _len);
}

void resize(BitMap *bmap, uint32_t _len)
{
  uint32_t _ints = (_len + 31) / 32;
  if (_ints <= bmap->ints)
    return;

  uint32_t *intmap__ = new uint32_t[_ints];
  memcpy(intmap__, bmap->intmap_, sizeof(bmap->intmap_[0]) * bmap->ints);
  delete[] bmap->intmap_;
  bmap->len = _len;
  bmap->ints = _ints;
  bmap->intmap_ = intmap__;
}

void OR(BitMap *bmap, BitMap *other)
{
  for (uint32_t i = 0; i < bmap->ints && i < other->ints; ++i) {
    bmap->intmap_[i] |= other->intmap_[i];
  }
}

void show(BitMap *bmap)
{
  for (int i = bmap->ints-1; i >= 0; --i) {
    printf("%x ", bmap->intmap_[i]);
  }
}




