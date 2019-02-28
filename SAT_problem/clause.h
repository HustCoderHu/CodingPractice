#ifndef CLAUSE_H
#define CLAUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

class Clause
{
public:
  Clause(int _minV, int _maxV)
    : len(n)
    , nVar(0)
  {
    minV = _minV;
    len = _maxV - _minV + 1;
    elem = new bool[len]; //malloc(sizeof(int) * n);

    for (uint32_t i = 0; i < len; ++i)
      elem[i] != false;
  }

  ~Clause()
  {
    free(elem);
  }

  bool isUnitClause();
  bool getUnit(uint32_t *var);
  bool isUnitClauseFallback()
  {
    bool found = false;
    for(uint32_t i = 0; i < len; ++i) {
      if (elem[i] != 0)
        if (!found)
          found = true;
      //        else
    }
    return false;
  }
  bool contains(int var)
  {
    return (var < minV || var >= minV + len) ?
          false : elem[var-minV];

    if (var < minV || var >= minV + len)
      return false;
    return elem[var-minV];
  }

  void rmVar(int var)
  {
    if (var < minV || var >= minV + len)
      return;
    if (true == elem[var-minV])
      --nVar;
    elem[var-minV] = false;
  }

  void addVar(int var)
  {
    if (var < minV || var >= minV + len)
      return;
    if (elem[var-minV] == false)
      ++nVar;
    elem[var-minV] = true;
  }
  bool suspectVar(int var)
  {
    if (var < len)
      elem[var] = false;
    return true;
  }

  int minV;
  uint32_t len;
  bool *elem;
  uint32_t nVar;
};

int LogicNOT(uint32_t var);

#endif // CLAUSE_H
