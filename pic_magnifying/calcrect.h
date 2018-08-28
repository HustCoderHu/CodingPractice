#ifndef CALCRECT_H
#define CALCRECT_H

struct Rect {
  int left;
  int top;
  int right;
  int bottom;

  void setRect(int l, int r, int t, int b) {
    left = l;
    right = r;
    top = t;
    bottom = b;
  }

  int width() {return right-left;}
  int height() {return bottom-top;}

  void offset(int dx, int dy) {
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
  }

  const int boundry = 100;
  void repair() {
    if (left < 0) {
      right -= left;
      left = 0;
    }
    if (top < 0) {
      bottom -= top;
      top = 0;
    }
    if (right > boundry) {
      left -= (right-boundry);
      right = boundry;
    }
    if (bottom > boundry) {
      top -= (bottom-boundry);
      bottom = boundry;
    }
  }
};

struct Point {
  int x;
  int y;
  Point(int a, int b) {
    x = a;
    y = b;
  }
};

class CalcRect
{
public:
  CalcRect();

  //窗格大小
  int width;
  int height;
  // 放大区域 百分数
  Rect rc_;

  // 鼠标滑动驱动方块区域移动
  void move(const Point& fromPt, const Point& toPt);
  void zoom(const Point& center);

  void showRect();
};

#endif // CALCRECT_H
