#include "solver.h"
#include <time.h>

Solver *createSolver()
{
  Solver *sl = (Solver*)malloc(sizeof(*sl));
  sl->s = 0;
  sl->resoBmap = NULL;
  sl->t = 0;
}

void destroySolver(Solver *sl)
{
  if (sl != NULL) {
    if (sl->resoBmap != NULL)
      free(sl->resoBmap);
    free(sl);
  }
}

/**
 * @brief simplize
 *   针对变量 var 化简 CNF
 * @param c
 * @param var
 * @param edit
 * @return bool, false if 存在单子句 -var
 */
bool simplize(Solver *sl, Cnf *cnf, int var, CnfEdit *edit)
{
  for (int pos = cnf->nClause - 1; pos >= 0; --pos) {
    if (existClause(cnf, pos) == false) // 子句已被简化为空
      continue;

    Clause *cl = cnf->clVec[pos];
    if (contains(cl, var)) { // 子句包含变量 L ，标记满足
      markClauseExist(cnf, pos, false);
      delClause(edit, pos);
      continue;
    }
    if (contains(cl, -var)) { // 包含 -L
      if (isUnitClause(cl)) // 单子句 -L 不能满足
        return false;
      markVarExist(cl, -var, false);
      delClauseVar(edit, -var, pos);
    }
  }
  return true;
}

void showResult(Solver *sl, Cnf *cnf)
{
  printf("s %d\n", sl->s);
  // v
  printf("v");
  for (uint32_t i = 1; i <= cnf->nVar; ++i) {
    if (getReso(sl, i))
      printf(" %d", i);
    else
      printf(" -%d", i);
  }
  printf("\n");
  printf("t %lu\n", sl->t);
}

void result2file(Solver *sl, Cnf *cnf, const char *fpath)
{
  FILE *fp = fopen(fpath, "w+");
  // s
  fprintf(fp, "s %d\n", sl->s);
  // v
  fprintf(fp, "v");
  for (uint32_t i = 1; i <= cnf->nVar; ++i) {
    if (getReso(sl, i))
      fprintf(fp, " %d", i);
    else
      fprintf(fp, " -%d", i);
  }
  fprintf(fp, "\n");
  fprintf(fp, "t %lu", sl->t);
  // t

  fclose(fp);
}

int solve(Solver *sl, Cnf *cnf)
{
  Bitmap *resoBmap = createBitmap(cnf->nVar);
  resetBitmap(resoBmap);
  sl->resoBmap = resoBmap;

  clock_t start, finish;
  start = clock();
  sl->resoBmap = _solve(sl, cnf, 0);
  finish = clock();
  sl->t = (double)(finish - start) * 1000 / CLOCKS_PER_SEC;
  return sl->s;
}

int _solve(Solver *sl, Cnf *cnf, int var)
{
  int ret = 0;
  CnfEdit *edit = createCnfEdit(cnf->nClause, cnf->nVar);
  if (var != 0) {
    simplize(sl, cnf, var, edit);
    setReso(sl, var);
    //    resoBmap->set(abs(var)-1, var>0);
    //    cnf->show();
    //    cnf->bmap->show();
    //    cout << endl;
    if (isEmpty(cnf)) {// 全部被简化
      ret = 1;
      //      cout << __LINE__ << endl;
      //      cnf->show(); cout << endl;
      goto end;
    }
  }
  while (getSimple(cnf, &var)) {
    //    cout << "======================" << endl;
    //    cnf->show(); cout << endl;
    //    cout << "getSimple ::::::: " << var << endl << endl;
    if (simplize(sl, cnf, var, edit)) {
      setReso(sl, var);
      //      resoBmap->set(abs(var)-1, var>0);
      if (isEmpty(cnf)) {// 全部被简化
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

  var = selectVar(sl, cnf);
  //  cout << "select: " << var << endl;
  //  simplize(cnf, var, edit_branch);
  ret = _solve(sl, cnf, var);
  if (1 == ret || -1 == ret) {
    ret = 1;
    //    cout << __LINE__ << endl;
    //    cnf->show(); cout << endl;
    goto end;
  }
  // 还原 CNF，验证另外一条分支
  ret = _solve(sl, cnf, -var);
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
  restore(cnf, edit);
  destroyCnfEdit(edit);
  return ret;
}

int selectVar(Solver *sl, Cnf *cnf)
{
  // TODO
  Clause *cl = getShortestClause(cnf);
  //  char strbuf[20];
  //  cl->toString(strbuf);
  //  printf("%s \n", strbuf);
  return getVar(cl, 0);
}

bool verifyCnf(Solver *sl, Cnf *cnf)
{
  char strbuf[80];
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    Clause *cl = cnf->clVec[i];
    toString(cl, strbuf);
    if (!verifyClause(cl, sl->resoBmap)) {
      //      cl->toString(strbuf);
      printf("clause idx: %d\n", i);
      printf("%s\n", strbuf);
    }
  }
  printf("Solver verify finish\n");
  return true;
}

void setReso(Solver *sl, int var)
{
  set(sl->resoBmap, abs(var)-1, var > 0);
}

bool getReso(Solver *sl, uint32_t var)
{
  return sl->resoBmap->get(var-1);
}
