#include "cnfedit.h"
#include "clause.h"
#include "bitmap.h"
#include <string.h>

CnfEdit* createCnfEdit(uint32_t _nClause, uint32_t _nVar)
{
  CnfEdit *edit = (CnfEdit*)malloc(sizeof(*edit));
  edit->nClause = _nClause;
  edit->nVarPlusNOT = _nVar * 2;

  edit->deletedClause = createBitmap(edit->nClause);
  edit->varVec = (Bitmap**)malloc(sizeof(Bitmap*) * edit->nVarPlusNOT);
  for (uint32_t i = 0; i < edit->nVarPlusNOT; ++i)
    edit->varVec[i] = NULL;

  return edit;
}

void resetCnfEdit(CnfEdit *edit)
{
  resetBitmap(edit->deletedClause);
  for (uint32_t v = 0; v < edit->nVarPlusNOT; ++v) {
    if (edit->varVec[v])
      resetBitmap(edit->varVec[v]);
  }
}

void delClause(CnfEdit* edit, uint32_t pos)
{
  mayResize(edit->deletedClause, pos+1);
  set(edit->deletedClause, pos, true);
}

void delClauseVar(CnfEdit* edit, int var, uint32_t pos)
{
  uint32_t transformed = toBufferFormat(var);
  if (NULL == edit->varVec[transformed]) {
    edit->varVec[transformed] = createBitmap(pos+1);
  } else {
    mayResize(edit->varVec[transformed], pos);
  }
  set(edit->varVec[transformed], pos, true);
}
