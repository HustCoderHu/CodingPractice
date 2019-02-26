#ifndef CNF_H
#define CNF_H
#include "clause.h"

class Cnf
{
public:
  Cnf();

  int getSimple()
  {
    int simple;
    for (int i = 0; i < nVar; ++i) {
      if (clVec[i] != nullptr) {
        if (clVec[i]->isUnitClause(&simple))
          return simple;
      }
    }
    return -1;
  }
  void simplize(int var)
  {

  }

  int nVar;
  int nClause;

  int nCur;
  Clause **clVec;
};

#endif // CNF_H
