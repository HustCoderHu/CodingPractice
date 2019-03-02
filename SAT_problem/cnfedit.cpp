#include "cnfedit.h"
#include "clause.h"
#include <string.h>

CnfEdit::CnfEdit(uint32_t _nClause, uint32_t _nVar)
{
  nClause = _nClause;
  nVarPlusNOT = _nVar * 2;

  deletedClause = new BitMap(nClause);
  varVec = new BitMap*[nVarPlusNOT];
  for (uint32_t i = 0; i < nVarPlusNOT; ++i)
    varVec[i] = nullptr;
}

void CnfEdit::reset()
{
  deletedClause->reset();
  for (uint32_t v = 0; v < nVarPlusNOT; ++v) {
    if (varVec[v])
      varVec[v]->reset();
  }
}

void CnfEdit::delClause(uint32_t pos)
{
  deletedClause->mayResize(pos+1);
  deletedClause->set(pos, true);
}

void CnfEdit::delClauseVar(int var, uint32_t pos)
{
  uint32_t transformed = Clause::toBufferFormat(var);
  if (nullptr == varVec[transformed]) {
    varVec[transformed] = new BitMap(pos+1);
  } else {
    varVec[transformed]->mayResize(pos+1);
  }
  varVec[transformed]->set(pos, true);
}
