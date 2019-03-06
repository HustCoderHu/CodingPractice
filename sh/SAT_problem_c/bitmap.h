#ifndef BITMAP_H
#define BITMAP_H
#include <stdint.h>

struct BitMap
{
  uint32_t len;
  uint32_t ints;
  uint32_t *intmap_;

//  unsigned int count; // 有效的位数
};

BitMap* createBitmap(uint32_t _len);
bool set(BitMap *bmap, uint32_t pos, bool flag);
void reset(BitMap *bmap);

bool get(BitMap *bmap, uint32_t pos);

bool isAllFalse(BitMap *bmap);
void mayResize(BitMap *bmap, uint32_t _len);
void resize(BitMap *bmap, uint32_t _len);

void OR(BitMap *bmap, BitMap *other);

void show(BitMap *bmap);

#endif // BITMAP_H
