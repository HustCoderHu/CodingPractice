#ifndef CNFEDIT_H
#define CNFEDIT_H
#include "bitmap.h"


/**
 * @brief The CnfEdit class
 * 记录化简过程中的修改，用来还原 CNF
 */
class CnfEdit
{
public:
  CnfEdit(uint32_t _nClause, uint32_t _nVar);
  ~CnfEdit();

  void reset();
  void delClause(uint32_t pos);
  void delClauseVar(int var, uint32_t pos);

  BitMap *deletedClause;
  uint32_t nClause;
  uint32_t nVarPlusNOT;
  // varVec[trans] 记录变量 trans 从哪些子句里被移除
  BitMap **varVec;
};

#endif // CNFEDIT_H
