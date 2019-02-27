#include "cnfedit.h"

CnfEdit::CnfEdit(unsigned int nClause, unsigned int _nVar)
  : deletedClause(nClause)
  , nVar(_nVar)
{
  varVec = new BitMap*[nVar];
  for (int i = 0; i < nVar; ++i)
    varVec[i] = nullptr;
}

void CnfEdit::delClause(unsigned int pos)
{
  deletedClause.set(pos, true);
}

void CnfEdit::delClauseVar(unsigned int pos, unsigned int var)
{
  if (varVec[var] == nullptr) {
    varVec[var] = new BitMap(pos+1);
  }
  if (pos >= varVec[var]->len)
    varVec[var]->resize(pos+1);
  varVec[var]->set(pos, true);
}
