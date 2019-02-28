#include "solver.h"

// 比如 A=2n, 则-A=2n+1
#define LogicNOT(var) (var ^ 0x1)

Solver::Solver()
{

}

/**
 * @brief Solver::simplize
 *   针对变量 var 化简 CNF
 * @param c
 * @param var
 * @param edit
 * @return
 */
bool Solver::simplize(Cnf *c, unsigned int var, CnfEdit *edit)
{
  unsigned int logicNot = LogicNOT(var);
  for (int pos = c->nClause; pos >= 0; --pos) {
    if (c->existClause(pos) == false) // 子句已被简化为空
      continue;

    Clause *cl = c->clVec[pos];
    if (cl->contains(var)) { // 子句包含变量 L ，标记满足
      c->rmClause(pos);
      edit->delClause(pos);
      continue;
    }
    if (cl->contains(logicNot)) { // 包含 -L
      if (cl->isUnitClause()) // 单子句 -L 不能满足
        return false;
      cl->rmVar(logicNot);
      edit->delClauseVar(logicNot, pos);
    }
  }
  return true;
}

void Solver::result2file(Cnf *c, const char *fpath)
{
  FILE *fp = fopen(fpath, "w+");
  // s
  fprintf(fp, "s %d\n", s);
  // v
  fprintf(fp, "v");
  for (unsigned int i = 0; i < v->len; ++i) {
    if (v->get(i))
      fprintf(fp, " %d", i);
    else
      fprintf(fp, " -%d", i);
  }
  fprintf(fp, "t %l", t);
  // t

  fclose(fp);
}

bool Solver::solve(Cnf *c)
{
  v->reset();
  s = _solve(c);
}

int Solver::_solve(Cnf *c)
{
  CnfEdit *edit = new CnfEdit(c->nClause, c->nVar);

  int var = c->getSimple();
  while (var != -1) {
    if (simplize(c, var, edit)) {
      if (c->isEmpty()) // 全部被简化
        return true;
    } else { // 单子句 -L 不能满足
      return false;
    }
    var = c->getSimple();
  }

  CnfEdit *edit_branch = new CnfEdit(c->nClause, c->nVar);
  var = selectVar(c);
  simplize(c, var, edit_branch);
  if (_solve(c) == 0) {
    v->set(var, true);
    delete edit;
    return 1;
  }
  // 还原 CNF，验证另外一条分支
  c->restore(edit_branch);

  simplize(c, LogicNOT(var), edit_branch);
  if (_solve(c) == 0) {
    v->set(LogicNOT(var), true);
    delete edit;
    return 1;
  }
  // 无解
  c->restore(edit);
  delete edit;
  return 0;
}

int Solver::selectVar(Cnf *c)
{

}
