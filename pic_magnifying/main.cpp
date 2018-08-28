#include <iostream>

#include "calcrect.h"

using namespace std;

int main()
{
  CalcRect rect;
  rect.width = 160;
  rect.height = 90;

  rect.rc_.setRect(0, 100, 0, 100);
  rect.rc_.setRect(20, 80, 20, 80);
//  rect.showRect();

  Point fromPt(100, 100);
  Point toPt(50, 50);
  rect.move(fromPt, toPt);
  rect.showRect();
  cout << "Hello World!" << endl;
  return 0;
}
