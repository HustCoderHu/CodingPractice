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
  CnfEdit(uint32_t nClause, uint32_t _nVar);

  void reset();
  void delClause(unsigned int pos);
  void delClauseVar(unsigned int var, unsigned int pos);

  BitMap *deletedClause;
  uint32_t nVar;
  BitMap **varVec;
};

#endif // CNFEDIT_H
