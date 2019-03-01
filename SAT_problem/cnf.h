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
  ~Cnf();

  void parseFile(const char* fpath);
  static Clause* parseLine(char buf[]);
  static uint32_t countNvar(char buf[]);

  int getSimple();

  bool isEmpty() { return bmap->isAllFalse(); }

  void show();

  bool existClause(uint32_t pos);
  void addClause(uint32_t pos);
  void markClauseRemoved(uint32_t pos);
  //  void apply(CnfEdit *edit);
  void restore(CnfEdit *edit);

  static const uint32_t LINE_MAX_LEN = 80;

  int nVar;
  int nClause;

  int nCur;
  Clause **clVec;

  BitMap *bmap; // 第i个子句是否还在 (没有被简化成 空)
  //  Version *ver;
};

#endif // CNF_H
