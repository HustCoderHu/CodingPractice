#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"

#include "versionedit.h"

class Solver
{
public:
  Solver();

  bool simplize(Cnf *c, int var, VersionEdit *edit);

  static void result2file(Cnf *c, const char *fpath);
  static bool solve(Cnf *c);
  static bool _solve(Cnf *c);
  static int selectVar(Cnf *c);

  unsigned int *varCnt;

  bool s;
  BitMap v; // 解 变元值
  unsigned long t;
};

#endif // SOLVER_H
