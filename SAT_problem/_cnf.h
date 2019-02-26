#ifndef CNF_H
#define CNF_H

#include "_clause.h"

struct Cnf {
  int nVar;
  int nClause;

  int nCur;
  Clause **clVec;
};

static Cnf* createCnf(int _nClause)
{
  Cnf *c = malloc(sizeof(Cnf));
  c->nClause = _nClause;
  c->clVec = malloc(sizeof(Clause*) * _nClause);
}

static void addClause(Cnf *c, Clause *cl)
{
//  ++c->nClause;
  c->clVec[c->nCur++] = cl;
}

static void removeClause()
{

}

#endif // CNF_H
