#ifndef BITMAP_H
#define BITMAP_H

class BitMap
{
public:
  BitMap(int _len);
  ~BitMap()
  {
    delete[] intmap_;
  }

  bool set(unsigned int pos, bool flag);
  void reset();

//  int get();
  bool get(unsigned int pos);

  bool isAllFalse();
  void resize(int _len);

  unsigned int len;
  unsigned int ints;
  unsigned int *intmap_;

  unsigned int count; // 有效的位数
};

#endif // BITMAP_H
