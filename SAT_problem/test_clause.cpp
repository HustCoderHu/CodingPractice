#include <iostream>
#include "cnf.h"

using std::cout;
using std::endl;

/*
int main()
{
  char display[80];
  Clause *cl;

  char buf1[] = "1 11  111   -2 -22  -222   0";
  cl = Cnf::parseLine(buf1);
  cl->toString(display);
  cout << display << endl;
  cout << endl;

  cout << cl->contains(1) << endl;
  cout << cl->contains(11) << endl;
  cout << cl->contains(111) << endl;
  cout << endl;

  cout << cl->contains(-2) << endl;
  cout << cl->contains(-22) << endl;
  cout << cl->contains(-222) << endl;
  cout << endl;

  cout << cl->contains(-1) << endl;
  cout << cl->contains(-11) << endl;
  cout << cl->contains(-111) << endl;
  cout << endl;

  cout << cl->contains(2) << endl;
  cout << cl->contains(22) << endl;
  cout << cl->contains(222) << endl;

  cl->rmVar(1);
  cl->rmVar(-1);
  cl->rmVar(-2);
  cl->toString(display);
  cout << display << endl;
  cl->addVar(1);
  cl->addVar(-1);
  cl->addVar(-2); // 范围原因 被加到子句里
  cl->toString(display);
  cout << display << endl;

  delete cl;
  Clause::releaseBuf();

  return 0;
}

*/
