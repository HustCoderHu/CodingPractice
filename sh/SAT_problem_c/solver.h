#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"
#include "bitmap.h"

#include "cnfedit.h"

typedef struct
{
  int s;
  Bitmap *resoBmap; // 解 变元值
  unsigned long t; // 用时
} Solver;

Solver* createSolver();
void destroySolver(Solver *sl);

bool simplize(Solver *sl, Cnf *cnf, int var, CnfEdit *edit);

int solve(Solver *sl, Cnf *cnf);
int _solve(Solver *sl, Cnf *cnf, int var);
int selectVar(Solver *sl, Cnf *cnf);

// 标记解
void setReso(Solver *sl, int var);
bool getReso(Solver *sl, uint32_t var);
void showResult(Solver *sl, Cnf *cnf);
void result2file(Solver *sl, Cnf *cnf, const char *fpath);

bool verifyCnf(Solver *sl, Cnf *cnf);

#endif // SOLVER_H
