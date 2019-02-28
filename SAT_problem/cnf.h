#ifndef CNF_H
#define CNF_H
#include "clause.h"

#include "bitmap.h"
#include "cnfedit.h"
//#include "versionset.h"

class Cnf
{
public:
  Cnf();

  void parseFile(const char* fpath);
  static Clause* parseLine(char buf[]);
  static uint32_t countNvar(char buf[]);

  int getSimple()
  {
    uint32_t simple;
    for (int i = 0; i < nVar; ++i) {
      if (clVec[i] != nullptr) {
        if (clVec[i]->getUnit(&simple))
          return simple;
      }
    }
    return -1;
  }

  bool isEmpty()
  {
    return bmap->isAllFalse();
  }

  bool existClause(unsigned int pos);
  void rmClause(unsigned int pos);
  //  void apply(CnfEdit *edit);
  void restore(CnfEdit *edit);

  static const unsigned int LINE_MAX_LEN = 80;

  int nVar;
  int nClause;

  int nCur;
  Clause **clVec;

  BitMap *bmap; // 第i个子句是否还在 (没有被简化成 空)

  //  Version *ver;
};

#endif // CNF_H
