#include "solver.h"
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

Solver::Solver()
{
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

void Solver::showResult()
{
  printf("s %d\n", s);
  // v
  printf("v");
  for (uint32_t i = 0; i < resoBmap->len; ++i) {
    if (resoBmap->get(i))
      printf(" %d", i+1);
    else
      printf(" -%d", i+1);
  }
  printf("\n");
  printf("t %lu\n", t);
}

void Solver::result2file(const char *fpath)
{
  FILE *fp = fopen(fpath, "w+");
  // s
  fprintf(fp, "s %d\n", s);
  // v
  fprintf(fp, "v");
  for (uint32_t i = 0; i < resoBmap->len; ++i) {
    if (resoBmap->get(i))
      fprintf(fp, " %d", i+1);
    else
      fprintf(fp, " -%d", i+1);
  }
  fprintf(fp, "\n");
  fprintf(fp, "t %lu", t);
  // t

  fclose(fp);
}

bool Solver::solve(Cnf *cnf)
{
  resoBmap = new BitMap(cnf->nVar);
  resoBmap->reset();

  clock_t start, finish;
  start = clock();
  s = _solve(cnf, 0);
  finish = clock();
  t = (double)(finish - start) * 1000 / CLOCKS_PER_SEC;
  // TODO return
}

int Solver::_solve(Cnf *cnf, int var)
{
  int ret = 0;
  CnfEdit *edit = new CnfEdit(cnf->nClause, cnf->nVar);
  if (var != 0) {
    simplize(cnf, var, edit);
    resoBmap->set(abs(var)-1, var>0);
//    cnf->show();
//    cnf->bmap->show();
//    cout << endl;
    if (cnf->isEmpty()) {// 全部被简化
      ret = 1;
      goto end;
    }
  }
  while (cnf->getSimple(&var)) {
    if (simplize(cnf, var, edit)) {
      resoBmap->set(abs(var)-1, var>0);
      if (cnf->isEmpty()) {// 全部被简化
        ret = 1;
        goto end;
      }
    } else { // 单子句 -L 不能满足
      ret = 0;
      goto end;
    }
  }
//  cnf->show();

  var = selectVar(cnf);
  cout << "select: " << var << endl;
  //  simplize(cnf, var, edit_branch);
  ret = _solve(cnf, var);
  if (1 == ret || -1 == ret) {
    ret = 1;
    goto end;
  }
  // 还原 CNF，验证另外一条分支
  ret = _solve(cnf, var);
  if (1 == ret || -1 == ret) {
    ret = 1;
  }
  // 无解
end:
  cnf->restore(edit);
  delete edit;
  return ret;
}

int Solver::selectVar(Cnf *cnf)
{
  // TODO
//  Clause *cl = cnf->getShortestClause();
  Clause *cl = cnf->getRandomClause();
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
      printf("idx: %d\n", i);
      printf("%s\n", strbuf);
    }
  }
  return true;
}

Reso::Reso(uint32_t nVar)
{
  v = new BitMap(nVar);
  len = nVar;
//  varBuffer = new int[nVar];
  nCur = 0;
}

void Reso::addVar(int var, bool flag)
{
  if (var > 0) {
//    varBuffer[nCur++] = var;
    v->set(var-1, flag);
  } else {
//    varBuffer[nCur++] = -var;
    v->set(-var-1, !flag);
  }
}

bool Reso::getReso(uint32_t var)
{
  return v->get(var-1);
}

void Reso::rollback(uint32_t n)
{

}


