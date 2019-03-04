#include "solver.h"
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

Solver::Solver()
{
  s = 0;
  resoBmap = nullptr;
  t = 0;
}

Solver::~Solver()
{
  if (resoBmap != nullptr)
    delete resoBmap;
}

/**
 * @brief Solver::simplize
 *   针对变量 var 化简 CNF
 * @param c
 * @param var
 * @param edit
 * @return bool, false if 存在单子句 -var
 */
bool Solver::simplize(Cnf *cnf, int var, CnfEdit *edit)
{
  for (int pos = cnf->nClause - 1; pos >= 0; --pos) {
    if (cnf->existClause(pos) == false) // 子句已被简化为空
      continue;

    Clause *cl = cnf->clVec[pos];
    if (cl->contains(var)) { // 子句包含变量 L ，标记满足
      cnf->markClauseExist(pos, false);
      edit->delClause(pos);
      continue;
    }
    if (cl->contains(-var)) { // 包含 -L
      if (cl->isUnitClause()) // 单子句 -L 不能满足
        return false;
      cl->rmVar(-var);
      edit->delClauseVar(-var, pos);
    }
  }
  return true;
}

void Solver::showResult(Cnf *cnf)
{
  printf("s %d\n", s);
  // v
  printf("v");
  for (uint32_t i = 1; i <= cnf->nVar; ++i) {
    if (getReso(i))
      printf(" %d", i);
    else
      printf(" -%d", i);
  }
  printf("\n");
  printf("t %lu\n", t);
}

void Solver::result2file(Cnf *cnf, const char *fpath)
{
  FILE *fp = fopen(fpath, "w+");
  // s
  fprintf(fp, "s %d\n", s);
  // v
  fprintf(fp, "v");
  for (uint32_t i = 1; i <= cnf->nVar; ++i) {
    if (getReso(i))
      fprintf(fp, " %d", i);
    else
      fprintf(fp, " -%d", i);
  }
  fprintf(fp, "\n");
  fprintf(fp, "t %lu", t);
  // t

  fclose(fp);
}

int Solver::solve(Cnf *cnf)
{
  resoBmap = new BitMap(cnf->nVar);
  resoBmap->reset();
  clock_t start, finish;
  start = clock();
  s = _solve(cnf, 0);
  finish = clock();
  t = (double)(finish - start) * 1000 / CLOCKS_PER_SEC;
  return s;
}

int Solver::_solve(Cnf *cnf, int var)
{
  int ret = 0;
  CnfEdit *edit = new CnfEdit(cnf->nClause, cnf->nVar);
  if (var != 0) {
    simplize(cnf, var, edit);
    setReso(var);
//    resoBmap->set(abs(var)-1, var>0);
//    cnf->show();
//    cnf->bmap->show();
//    cout << endl;
    if (cnf->isEmpty()) {// 全部被简化
      ret = 1;
//      cout << __LINE__ << endl;
//      cnf->show(); cout << endl;
      goto end;
    }
  }
  while (cnf->getSimple(&var)) {
//    cout << "======================" << endl;
//    cnf->show(); cout << endl;
//    cout << "getSimple ::::::: " << var << endl << endl;
    if (simplize(cnf, var, edit)) {
      setReso(var);
//      resoBmap->set(abs(var)-1, var>0);
      if (cnf->isEmpty()) {// 全部被简化
        ret = 1;
//        cout << __LINE__ << endl;
//        cnf->show(); cout << endl;
        goto end;
      }
    } else { // 单子句 -L 不能满足
      ret = 0;
      goto end;
    }
  }
//  cnf->show();

  var = selectVar(cnf);
//  cout << "select: " << var << endl;
  //  simplize(cnf, var, edit_branch);
  ret = _solve(cnf, var);
  if (1 == ret || -1 == ret) {
    ret = 1;
//    cout << __LINE__ << endl;
//    cnf->show(); cout << endl;
    goto end;
  }
  // 还原 CNF，验证另外一条分支
  ret = _solve(cnf, -var);
  if (1 == ret || -1 == ret) {
    ret = 1;
    goto end;
//    cout << __LINE__ << endl;
//    cnf->show(); cout << endl;
  }
//  else
//    cnf->show(); cout << endl;
  // 无解
//  cout << var << -var << endl;
end:
  cnf->restore(edit);
  delete edit;
  return ret;
}

int Solver::selectVar(Cnf *cnf)
{
  // TODO
  Clause *cl = cnf->getShortestClause();
//  char strbuf[20];
//  cl->toString(strbuf);
//  printf("%s \n", strbuf);
  return cl->getVar(0);
}

bool Solver::verify(Cnf *cnf)
{
  char strbuf[80];
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    Clause *cl = cnf->clVec[i];
    cl->toString(strbuf);
    if (!cl->verify(resoBmap)) {
//      cl->toString(strbuf);
      printf("clause idx: %d\n", i);
      printf("%s\n", strbuf);
    }
  }
  cout << "Solver verify finish" << endl;
  return true;
}
