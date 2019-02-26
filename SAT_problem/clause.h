#ifndef CLAUSE_H
#define CLAUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Clause
{
public:
  Clause(int n, int *_elem)
    : len(n)
    , nVar(0)
  {
    elem = malloc(sizeof(int) * n);
    memcpy(elem, _elem, sizeof(int) * n);

    for (int i = 0; i < n; ++i)
      if (_elem[i] != 0)
        ++nVar;
  }

  ~Clause()
  {
    free(elem);
  }

  bool isUnitClause(int *var) { return nVar == 1; }
  bool isUnitClauseFallback()
  {
    bool found = false;
    for(int i = 0; i < len; ++i) {
      if (elem[i] != 0)
        if (!found)
          found = true;
//        else
    }
  }
  bool contains(int var)
  {
    return elem[var] == 1;
  }

  void rmVar(int var)
  {

  }
  void addVar(int var)
  {

  }
  bool suspectVar(int var)
  {

  }

  int len;
  int *elem;
  int nVar;
};

#endif // CLAUSE_H
