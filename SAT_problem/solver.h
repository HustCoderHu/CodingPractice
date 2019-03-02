#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"

#include "cnfedit.h"

class Reso
{
public:
  Reso(uint32_t nVar);

  void addVar(int var, bool flag);
  bool getReso(uint32_t var);
  // 回退 n 个变元的解
  void rollback(uint32_t n);

  BitMap *v; // 解 变元值
  uint32_t len;
  int *varBuffer;
  uint32_t nCur; // 已保存变元解 个数
};

class Solver
{
public:
  Solver();
  ~Solver() {}

  bool simplize(Cnf *cnf, int var, CnfEdit *edit);

  void showResult();
  void result2file(const char *fpath);
  bool solve(Cnf *cnf);
  int _solve(Cnf *cnf, int var);
  int selectVar(Cnf *cnf);

  bool verify(Cnf *cnf);

  unsigned int *varCnt;

  int s;
  BitMap *resoBmap; // 解 变元值
  unsigned long t;
};

#endif // SOLVER_H
