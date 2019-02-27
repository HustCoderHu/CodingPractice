#include "solver.h"

Solver::Solver()
{

}

bool Solver::simplize(Cnf *c,unsigned int var, VersionEdit *edit)
{
  unsigned int logicNot = LogicNOT(var);
  for (unsigned int pos = c->nClause; pos >= 0; --pos) {
    if (c->existClause(pos) == false) // 子句已被简化为空
      continue;

    Clause *cl = c->clVec[pos];
    if (cl->contains(var)) { // 子句包含变量 L ，标记满足
      c->rmClause(pos);
      edit->del(pos);
      continue;
    }
    if (cl->contains(logicNot)) { // 包含 -L
      if (cl->isUnitClause()) // 单子句 -L 不能满足
        return false;
//      cl->rmVar(logicNot);
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
  for (unsigned int i = 0; i < v.len; ++i) {
    if (v.get(i))
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
  v.reset();
  s = _solve(c);
}

bool Solver::_solve(Cnf *c)
{
  int var = c->getSimple();
  while (var != -1) {
    if (simplize(c, var)) {
      if (c->isEmpty()) // 全部被简化
        return true;
    } else { // 单子句 -L 不能满足
      return false;
    }
    var = c->getSimple();
  }
  var = selectVar(c);
  simplize(c, var);
  if (_solve(c)) {
    v.set(var, true);
    return true;
  }
  // restore // 还原 CNF
  simplize(c, LogicNOT(var));
  if (_solve(c)) {
    v.set(LogicNOT(var), true);
    return true;
  }
  // restore
  return false;
}

int Solver::selectVar(Cnf *c)
{

}
