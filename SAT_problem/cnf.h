#ifndef CNF_H
#define CNF_H
#include "clause.h"

#include "bitmap.h"
#include "versionedit.h"
//#include "versionset.h"

class Cnf
{
public:
  Cnf();

  static void parseFromFile(const char* fpath);

  int getSimple()
  {
    int simple;
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
    return bmap.isAllFalse();
  }

  bool existClause(unsigned int pos);
  void rmClause(unsigned int pos);
  void snapshot();

  int nVar;
  int nClause;

  int nCur;
  Clause **clVec;

  BitMap bmap; // 第i个子句是否还在 (没有被简化成 空)
  void apply(VersionEdit *edit);
  void restore(VersionEdit *edit);

//  Version *ver;
};

#endif // CNF_H
