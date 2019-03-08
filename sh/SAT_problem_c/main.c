#include <stdio.h>
#include "solver.h"

void test_solver();
unsigned long solve2file(VAR_SELECT_STRATEGE s,
                         const char *cnfile, const char* res2file);

int main(int argc, char *argv[])
{
  //  test_solver();
  const char *cnfile = NULL;
  char res2file[80];
//  const char *cnfile = "E:/github_repo/ais10.cnf";
//  const char *cnfile = "E:/github_repo/unsat-5cnf-30.cnf";

  printf("*************************************** sat-20 \n");
  cnfile = "E:/github_repo/sat-20.cnf";
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to %s\n\n", res2file);

  unsigned long t_asi10_first_clause, t_asi10_shortest_clause;
  unsigned long t_sud00009_first_clause, t_sud00009_shortest_clause;
  float optimizationRate;

  printf("*************************************** ais10 \n");
  cnfile = "E:/github_repo/ais10.cnf";
  printf("==================================== ENUM_FIRST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_FIRST_CLAUSE.result");
  t_asi10_first_clause = solve2file(ENUM_FIRST_CLAUSE, cnfile, res2file);
  printf("write to %s\n\n", res2file);
  printf("================================= ENUM_SHORTEST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  t_asi10_shortest_clause = solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to %s\n", res2file);

  optimizationRate = (float)(t_asi10_first_clause - t_asi10_shortest_clause)
      / t_asi10_first_clause;
  printf("@@@@@@@@@@@@@@ optimization rate: %f%%\n\n",optimizationRate * 100);

  printf("*************************************** sud00009 \n");
  cnfile = "E:/github_repo/sud00009.cnf";
  printf("==================================== ENUM_SHORTEST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_SHORTEST_CLAUSE.result");
  t_sud00009_shortest_clause = solve2file(ENUM_SHORTEST_CLAUSE, cnfile, res2file);
  printf("write to %s\n", res2file);
  printf("================================= ENUM_FIRST_CLAUSE\n");
  strcpy(res2file, cnfile);
  strcpy((char*)res2file + strlen(res2file), ".ENUM_FIRST_CLAUSE.result");
  t_sud00009_first_clause = solve2file(ENUM_FIRST_CLAUSE, cnfile, res2file);
  printf("write to %s\n", res2file);

  optimizationRate = (float)(t_sud00009_shortest_clause - t_sud00009_first_clause)
      / t_sud00009_shortest_clause;
  printf("@@@@@@@@@@@@@@ optimization rate: %f%%\n\n",optimizationRate * 100);

  releaseBuf();
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

void test_solver()
{
  //  for (int i = 0; i < 10; ++i)
  //    cout << rand() << endl;
  //  return;

  //  Cnf *cnf = buildCnf();
  //  cout << sizeof(bool) << endl;
  Cnf *cnf = createCnf();

  //  const char *fpath = "E:/github_repo/sat-20.cnf";
  const char *fpath = "E:/github_repo/ais10.cnf";
  //  const char *fpath = "E:/github_repo/sud00009.cnf";
  //  const char *fpath = "E:/github_repo/unsat-5cnf-30.cnf";

  //  const char *fpath = "D:/docs/github_repo/sat-20.cnf";
  //  const char *fpath = "D:/docs/github_repo/ais10.cnf";
  //  const char *fpath = "D:/docs/github_repo/sud00009.cnf";
  //  const char *fpath = "D:/docs/github_repo/unsat-5cnf-30.cnf";
  //  const char *fpath = "D:/docs/github_repo/tst_v10_c100.cnf";

  parseFile(cnf, fpath);
  Solver *sl = createSolver(ENUM_SHORTEST_CLAUSE);
  solve(sl, cnf);
  showResult(sl, cnf);

  //  char buf[] = "-1 2 3 4 -5 -6 -7 8 9 10 11 -12 -13 14 15 -16 17 18 19 20 0";
  //  int var;
  //  char* token = strtok(buf, " ");
  //  while ( token != NULL ) {
  //    var = atoi(token);
  //    token = strtok(NULL, " ");
  //    sl.resoBmap->set(abs(var)-1, var > 0);
  //  }

  //  Clause *cl;
  //  char buf1[] = "3 -5 18  0";
  //  cl = Cnf::parseLine(buf1);
  //  cout << cl->verify(sl.resoBmap) << endl;
  //  cout << endl;
  verifyCnf(sl, cnf);

  destroySolver(sl);
  destroyCnf(cnf);
  //  delete cnf;
}
