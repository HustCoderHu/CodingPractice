#include "cnfedit.h"
#include <string.h>

CnfEdit::CnfEdit(uint32_t nClause, uint32_t _nVar)
{
  deletedClause = nullptr;
  nVar = _nVar;
  varVec = nullptr;
}

void CnfEdit::reset()
{
  if (deletedClause)
    deletedClause->reset();
  if (nullptr == varVec)
    return;
  for (uint32_t v = 0; v < nVar; ++v) {
    if (varVec[v])
      varVec[v]->reset();
  }
}

void CnfEdit::delClause(unsigned int pos)
{
  if (nullptr == deletedClause)
    deletedClause = new BitMap(pos);
  deletedClause->set(pos, true);
}

void CnfEdit::delClauseVar(unsigned int var, unsigned int pos)
{
  if (nullptr == varVec) {
    varVec = new BitMap*[nVar];
    memset(varVec, 0, sizeof(BitMap*) * var);
//    for (int i = 0; i < nVar; ++i)
//      varVec[i] = nullptr;
  }

  if (nullptr == varVec[var]) {
    varVec[var] = new BitMap(pos+1);
  }
  if (pos >= varVec[var]->len)
    varVec[var]->resize(pos+1);
  varVec[var]->set(pos, true);
}
