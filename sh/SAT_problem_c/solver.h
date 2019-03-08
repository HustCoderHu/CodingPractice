#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"
#include "bitmap.h"

#include "cnfedit.h"

typedef enum
{
  ENUM_SHORTEST_CLAUSE,
  ENUM_FIRST_CLAUSE,

  NUM_STRATEGE
} VAR_SELECT_STRATEGE;

typedef struct
{
  int (*selectVar)(Cnf *cnf);
  int s;
  Bitmap *resoBmap; // 解 变元值
  unsigned long t; // 用时
} Solver;

Solver* createSolver(VAR_SELECT_STRATEGE s);
void destroySolver(Solver *sl);

bool simplize(Cnf *cnf, int var, CnfEdit *edit);

int solve(Solver *sl, Cnf *cnf);
int _solve(Solver *sl, Cnf *cnf, int var);
// 选最短的子句
int selectVar_shortestClause(Cnf *cnf);
// 选第一个子句
int selectVar_firstClause(Cnf *cnf);

// 标记解
void setReso(Solver *sl, int var);
bool getReso(Solver *sl, uint32_t var);
void showResult(Solver *sl, Cnf *cnf);
void result2file(Solver *sl, Cnf *cnf, const char *fpath);

bool verifyCnf(Solver *sl, Cnf *cnf);

#endif // SOLVER_H
