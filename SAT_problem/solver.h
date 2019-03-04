#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"

#include "cnfedit.h"

class Solver
{
public:
  Solver();
  ~Solver();

  bool simplize(Cnf *cnf, int var, CnfEdit *edit);

  int solve(Cnf *cnf);
  int _solve(Cnf *cnf, int var);
  int selectVar(Cnf *cnf);

  // 标记解
  void setReso(int var) { resoBmap->set(abs(var)-1, var > 0); }
  bool getReso(uint32_t var) { return resoBmap->get(var-1); }
  void showResult(Cnf *cnf);
  void result2file(Cnf *cnf, const char *fpath);

  bool verify(Cnf *cnf);

  int s;
  BitMap *resoBmap; // 解 变元值
  unsigned long t; // 用时
};

#endif // SOLVER_H
