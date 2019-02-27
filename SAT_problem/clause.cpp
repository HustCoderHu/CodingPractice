#include "clause.h"

// 比如 A=2n, 则-A=2n+1
inline int LogicNOT(int var)
{
  return var ^ 0x1;
}

Clause::Clause()
{

}

bool Clause::isUnitClause()
{
  if (nVar != 1)
    return false;
  for (int i = 0; i < len; ++i) {
    if (elem[i])
      return true;
  }
  return false;
}

bool Clause::getUnit(int *var)
{
  if (nVar != 1)
    return false;
  for (int i = 0; i < len; ++i) {
    if (elem[i]) {
      *var = i;
      return true;
    }
  }
  return false;
}
