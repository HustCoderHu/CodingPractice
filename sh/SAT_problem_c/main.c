#include <stdio.h>
#include "solver.h"

void test_solver();
unsigned long solve2file(VAR_SELECT_STRATEGE s,
                         const char *cnfile, const char* res2file);
void testShowCnf();

int main(int argc, char *argv[])
{
//  testShowCnf();
  test_solver();
  return 0;
}

unsigned long solve2file(VAR_SELECT_STRATEGE s,
                         const char *cnfile, const char* res2file)
{
  Cnf *cnf = createCnf();
  parseFile(cnf, cnfile);
  Solver *sl = createSolver(s);
  solve(sl, cnf);
  showResult(sl, cnf);

  verifyCnf(sl, cnf);
  result2file(sl, cnf, res2file);
  unsigned long t = sl->t;

  destroySolver(sl);
  destroyCnf(cnf);
  return t;
}

void testShowCnf()
{
  const char *cnfile = NULL;
  cnfile = "D:/docs/github_repo/sat-20.cnf";
//  cnfile = "D:/docs/github_repo/ais10.cnf";
//  cnfile = "D:/docs/github_repo/sud00009.cnf";
  Cnf *cnf = createCnf();
  parseFile(cnf, cnfile);
  showCnf(cnf);
}

void test_solver()
{
  //  test_solver();
  const char *cnfile = NULL;
  char res2file[80];
//  const char *cnfile = "E:/github_repo/ais10.cnf";
//  const char *cnfile = "E:/github_repo/unsat-5cnf-30.cnf";

  cnfile = "D:/docs/github_repo/sat-20.cnf";
//  cnfile = "E:/github_repo/sat-20.cnf";
  printf("************************************************************ sat-20 \n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n\n", res2file);

  cnfile = "D:/docs/github_repo/unsat-5cnf-30.cnf";
//  cnfile = "E:/github_repo/sat-20.cnf";
  printf("************************************************************ unsat-5cnf-30 \n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n\n", res2file);
//  return ;

  unsigned long t_asi10_first_clause, t_asi10_shortest_clause;
  unsigned long t_sud00009_first_clause, t_sud00009_shortest_clause;
  float optimizationRate;

  cnfile = "D:/docs/github_repo/ais10.cnf";
//  cnfile = "E:/github_repo/ais10.cnf";
  printf("************************************************************ ais10 \n");
  printf("==================================== ENUM_FIRST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_FIRST_CLAUSE.result");
  t_asi10_first_clause = solve2file(ENUM_FIRST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n\n", res2file);
  printf("================================= ENUM_SHORTEST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  t_asi10_shortest_clause = solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n\n", res2file);

  optimizationRate = (float)(t_asi10_first_clause - t_asi10_shortest_clause)
      / t_asi10_first_clause;
  printf("@@@@@@@@@@@@@@ optimization rate: %f%%\n\n",optimizationRate * 100);

  cnfile = "D:/docs/github_repo/sud00009.cnf";
//  cnfile = "E:/github_repo/sud00009.cnf";
  printf("************************************************************ sud00009 \n");
  printf("==================================== ENUM_SHORTEST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  t_sud00009_shortest_clause = solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n", res2file);
  printf("================================= ENUM_FIRST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_FIRST_CLAUSE.result");
  t_sud00009_first_clause = solve2file(ENUM_FIRST_CLAUSE, cnfile, res2file);
  printf("write to >>>> >>>> %s\n\n", res2file);

  optimizationRate = (float)(t_sud00009_shortest_clause - t_sud00009_first_clause)
      / t_sud00009_shortest_clause;
  printf("@@@@@@@@@@@@@@ optimization rate: %f%%\n\n",optimizationRate * 100);

  releaseBuf();
}
