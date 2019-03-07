#ifndef BITMAP_H
#define BITMAP_H
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  uint32_t len;
  uint32_t ints;
  uint32_t *intmap_;
//  unsigned int count; // 有效的位数
} Bitmap;

Bitmap* createBitmap(uint32_t _len);
bool set(Bitmap *bmap, uint32_t pos, bool flag);
void resetBitmap(Bitmap *bmap);

bool get(Bitmap *bmap, uint32_t pos);

bool isAllFalse(Bitmap *bmap);
void mayResize(Bitmap *bmap, uint32_t _len);
void resize(Bitmap *bmap, uint32_t _len);

void OR(Bitmap *bmap, Bitmap *other);

void show(Bitmap *bmap);

#endif // BITMAP_H
