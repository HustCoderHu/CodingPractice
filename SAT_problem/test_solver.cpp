#include <iostream>
#include "cnf.h"
#include "solver.h"

using std::cout;
using std::endl;

Cnf* buildCnf();
bool test_simplize_restore();
void test_solve();

int main()
{
  test_solve();
}

Cnf* buildCnf()
{
  char fileContent[5][30] = {
    "6 0 \n",
    "-1 2 0 \n",
    "-3 4 0 \n",
    "-5 -6 0 \n",
    "6 -5 -2 0\n"
  };

  Cnf *cnf = new Cnf();
  cnf->nVar = 6;
  cnf->nClause = 5;
  Clause** clVec = new Clause*[cnf->nVar];
  BitMap *bmap = new BitMap(cnf->nClause);
  cnf->clVec = clVec;
  cnf->bmap = bmap;

  uint32_t nCur = 0;
  for (nCur = 0; nCur < cnf->nClause; ++nCur) {
    clVec[nCur] = Cnf::parseLine(fileContent[nCur]);
    cnf->markClauseExist(nCur, true);
  }
  cnf->nCur = nCur;

  return cnf;
}

bool test_simplize_restore()
{
  Cnf *cnf = buildCnf();

  cnf->show();

  Solver sl;
  CnfEdit *edit = new CnfEdit(cnf->nClause, cnf->nVar);
  int var;
  while (cnf->getSimple(&var)) {
    if (sl.simplize(cnf, var, edit)) {
      if (cnf->isEmpty()) // 全部被简化
        return true;
    } else { // 单子句 -L 不能满足
      return false;
    }
  }
  cnf->show();
  cout << endl;
  cnf->restore(edit);
  cnf->show();
  cout << endl;

  delete edit;
  delete cnf;
  //  sl.solve(cnf);
  //  sl.showResult();

  return true;
}

void test_solve()
{
//  for (int i = 0; i < 10; ++i)
//    cout << rand() << endl;
//  return;

//  Cnf *cnf = buildCnf();
  Cnf *cnf = new Cnf();
  const char *fpath = "D:/docs/github_repo/sat-20.cnf";
//  const char *fpath = "D:/docs/github_repo/tst_v10_c100.cnf";
//  const char *fpath = "D:/docs/github_repo/unsat-5cnf-30.cnf";

  cnf->parseFile(fpath);
  Solver sl;
  sl.solve(cnf);
  sl.showResult();

  char buf[] = "-1 2 3 4 -5 -6 -7 8 9 10 11 -12 -13 14 15 -16 17 18 19 20 0";
  int var;
  char* token = strtok(buf, " ");
  while ( token != NULL ) {
    var = atoi(token);
    token = strtok(NULL, " ");
    sl.resoBmap->set(abs(var)-1, var > 0);
  }

//  Clause *cl;
//  char buf1[] = "3 -5 18  0";
//  cl = Cnf::parseLine(buf1);
//  cout << cl->verify(sl.resoBmap) << endl;
//  cout << endl;
  sl.verify(cnf);
}

/*
*/
