#ifndef CNFEDIT_H
#define CNFEDIT_H
#include "bitmap.h"

class CnfEdit
{
public:
  CnfEdit(unsigned int nClause, unsigned int _nVar);

  void delClause(unsigned int pos);
  void delClauseVar(unsigned int pos, unsigned int var);

  BitMap deletedClause;
  unsigned int nVar;
  BitMap *varVec[];
};

#endif // CNFEDIT_H
