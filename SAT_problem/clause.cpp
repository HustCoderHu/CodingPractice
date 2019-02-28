#include "clause.h"



bool Clause::isUnitClause()
{
  if (nVar != 1)
    return false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i])
      return true;
  }
  return false;
}

bool Clause::getUnit(uint32_t *var)
{
  if (nVar != 1)
    return false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i]) {
      *var = i;
      return true;
    }
  }
  return false;
}
