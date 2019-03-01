#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"

#include "cnfedit.h"

class Solver
{
public:
  Solver();
  ~Solver() {}

  bool simplize(Cnf *c, int var, CnfEdit *edit);

  void result2file(Cnf *c, const char *fpath);
  bool solve(Cnf *c);
  int _solve(Cnf *c);
  int selectVar(Cnf *c);

  unsigned int *varCnt;

  int s;
  BitMap *v; // 解 变元值
  unsigned long t;
};

#endif // SOLVER_H
