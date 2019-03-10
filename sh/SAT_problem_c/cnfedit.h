#ifndef CNFEDIT_H
#define CNFEDIT_H
#include "bitmap.h"

/**
 * @brief The CnfEdit class
 * 记录化简过程中的修改，用来还原 CNF
 */
typedef struct
{
  Bitmap *deletedClause;
  uint32_t nClause;
  // 正负变量总个数
  uint32_t nVarPlusNOT;
  // varVec[trans] 记录变量 trans 从哪些子句里被移除
  Bitmap **varVec;
} CnfEdit;

CnfEdit* createCnfEdit(uint32_t _nClause, uint32_t _nVar);
void destroyCnfEdit(CnfEdit *edit);

void resetCnfEdit(CnfEdit *edit);
void delClause(CnfEdit* edit, uint32_t pos);
void delClauseVar(CnfEdit* edit, int var, uint32_t pos);

#endif // CNFEDIT_H
