#ifndef CLAUSE_H
#define CLAUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Clause {
  int len;
  int elem[];
};

static Clause* createClause(int n, int *elem)
{
  Clause *cl = malloc(sizeof(cl->len) + n * sizeof(int));
  cl->len = n;
  memcpy(cl->elem, elem, sizeof(int) * n);
  return cl;
}

static void destroyClause(Clause *cl)
{
  free(cl->elem);
  free(cl);
}

static bool isUnitClause(Clause *cl)
{

}

#endif // CLAUSE_H
