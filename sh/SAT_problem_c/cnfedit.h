#ifndef CNFEDIT_H
#define CNFEDIT_H
#include "bitmap.h"


/**
 * @brief The CnfEdit class
 * 记录化简过程中的修改，用来还原 CNF
 */
struct CnfEdit
{
  BitMap *deletedClause;
  uint32_t nClause;
  uint32_t nVarPlusNOT;
  // varVec[trans] 记录变量 trans 从哪些子句里被移除
  BitMap **varVec;
};

CnfEdit* createCnfEdit(uint32_t _nClause, uint32_t _nVar);
void reset(CnfEdit* edit);
void delClause(CnfEdit* edit, uint32_t pos);
void delClauseVar(CnfEdit* edit, int var, uint32_t pos);

#endif // CNFEDIT_H
