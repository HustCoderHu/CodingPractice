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
    elem = new int[n]; //malloc(sizeof(int) * n);
    memcpy(elem, _elem, sizeof(int) * n);

    for (int i = 0; i < n; ++i)
      if (_elem[i] != 0)
        ++nVar;
  }

  ~Clause()
  {
    free(elem);
  }

  bool isUnitClause();
  bool getUnit(int *var);
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
    return var < len ? elem[var] == 1 : false;

    if (var < len)
      return elem[var] == 1;
    else
      return false;
  }

  void rmVar(int var)
  {
    if (var < len)
      elem[var] = 0;
  }
  void addVar(int var)
  {
    if (var < len)
      elem[var] = 1;
  }
  bool suspectVar(int var)
  {
    if (var < len)
      elem[var] = 0;
  }

  int len;
  int *elem;
  int nVar;
};

int LogicNOT(int var);

#endif // CLAUSE_H
