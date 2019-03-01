#include <iostream>
#include "cnf.h"

using std::cout;
using std::endl;

int main()
{
  char display[80];
  Clause *cl;

//  char buf0[] = "1 11  111   0";
//  Clause *cl = Cnf::parseLine(buf0);
//  cl->toString(display);
//  cout << display << endl;
//  delete cl;

  char buf1[] = "1 11  111   -2 -22  -222   0";
  cl = Cnf::parseLine(buf1);
  cl->toString(display);
  cout << display << endl;
  delete cl;

  return 0;
}
