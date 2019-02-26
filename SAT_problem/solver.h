#ifndef SOLVER_H
#define SOLVER_H
#include "cnf.h"
#include "clause.h"

class Solver
{
public:
  Solver();

  static solve(Cnf *c);
};

#endif // SOLVER_H
