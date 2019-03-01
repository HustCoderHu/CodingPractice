#include <iostream>
#include "cnf.h"

using std::cout;
using std::endl;

int main()
{
  const char *fpath = "D:/docs/github_repo/CodingPractice/sat-20.cnf";
  Cnf cnf;
  cnf.parseFile(fpath);
  cnf.show();
  return 0;
}
