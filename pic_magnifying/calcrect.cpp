#include <iostream>
#include "calcrect.h"

using std::cout;
using std::endl;

CalcRect::CalcRect()
{

}

void CalcRect::move(const Point &fromPt, const Point &toPt)
{
  int deltaH = fromPt.x - toPt.x;
  int deltaV = fromPt.y - toPt.y;

  int deltaPercentH = rc_.width() * deltaH / width;
  int deltaPercentV = rc_.height() * deltaV / height;

  rc_.offset(deltaPercentH, deltaPercentV);
  rc_.repair();
}

void CalcRect::showRect()
{
  cout << rc_.left << " " << rc_.right << endl;
  cout << rc_.top << " " << rc_.bottom << endl;
}
// https://blog.csdn.net/luo_aiyang/article/details/80539736
