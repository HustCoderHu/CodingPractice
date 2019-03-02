#ifndef BITMAP_H
#define BITMAP_H
#include <stdint.h>

class BitMap
{
public:
  BitMap(uint32_t _len);
  ~BitMap()
  {
    delete[] intmap_;
  }

  bool set(uint32_t pos, bool flag);
  void reset();

//  int get();
  bool get(uint32_t pos);

  bool isAllFalse();
  void mayResize(uint32_t _len)
  {
    if (_len > len)
      resize(_len);
  }
  void resize(uint32_t _len);

  void OR(BitMap *other);

  void show();

  uint32_t len;
  uint32_t ints;
  uint32_t *intmap_;

//  unsigned int count; // 有效的位数
};

#endif // BITMAP_H
