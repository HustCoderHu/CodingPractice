#include "cnf.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const uint32_t LINE_MAX_LEN = 80;

Cnf::~Cnf()
{
  if (nullptr == bmap)
    return;
  for (uint32_t i = 0; i < nClause; ++i) {
    if (clVec[i] != nullptr) {
      delete clVec;
    }
  }
  delete[] clVec;
  delete bmap;
  Clause::releaseBuf();
}

Cnf *createCnf()
{
  Cnf *cnf = (Cnf*)malloc(sizeof(*cnf));
  cnf->nVar = 0;
  cnf->nClause = 0;
  cnf->bmap = nullptr;
  clVec = nullptr;
}

void destroy(Cnf *cnf)
{
  if (nullptr == cnf->bmap)
    return;
  for (uint32_t i = 0; i < nClause; ++i) {
    if (clVec[i] != nullptr) {
      delete clVec;
    }
  }
  free(cnf->clVec);
  free(cnf->bmap)
  Clause::releaseBuf();
}


void Cnf::parseFile(const char *fpath)
{
  FILE *fp = fopen(fpath, "r");

  char buf[LINE_MAX_LEN];
  memset(buf, 0, LINE_MAX_LEN);

  // 跳过注释
  fgets(buf, LINE_MAX_LEN, fp);
  while ('c' == buf[0] || '\n' == buf[0]) {
    fgets(buf, LINE_MAX_LEN, fp);
  }
  // p
  sscanf(buf, "p cnf %d %d", &cnf->nVar, &cnf->nClause);

  cout << "nVar: " << cnf->nVar << endl;
  cout << "nClause: " << cnf->nClause << endl;

  clVec = new Clause*[cnf->nClause];
  cnf->bmap = new BitMap(cnf->nClause);

  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    fgets(buf, LINE_MAX_LEN, fp);
    clVec[i] = parseLine(buf);
    markClauseExist(i, true);
  }

  fclose(fp);
}

Clause *Cnf::parseLine(char *buf)
{
  int var;
  //  uint32_t nVar = countNvar(buf);
  Clause *cl = new Clause(10);

  char* token = strtok(buf, " ");
  while ( token != NULL ) {
    var = atoi(token);
    if (0 == var)
      break;
    cl->bufferVar(var);
    token = strtok(NULL, " ");
  }
  cl->finishBuffer();
  return cl;
}

bool Cnf::getSimple(Cnf *cnf, int *var)
{
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    if (existClause(i)) {
      if (clVec[i]->getUnit(var)) {
        return true;
      }
    }
  }
  return false;
}

Clause *Cnf::getShortestClause(Cnf *cnf)
{
  uint32_t minLen = -1;
  Clause *shortest = nullptr;
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    if (existClause(i) && clVec[i]->nVarInClause <= minLen) {
      minLen = clVec[i]->nVarInClause;
      shortest = clVec[i];
    }
  }
  return shortest;
}

void Cnf::show(Cnf *cnf)
{
  char display[80];
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    if (existClause(i)) {
      clVec[i]->toString(display);
      printf("%s\n", display);
    }
  }
}

bool Cnf::existClause(Cnf *cnf, uint32_t pos)
{
  return get(cnf->bmap, pos);
}

void Cnf::markClauseExist(Cnf *cnf, uint32_t pos, bool exist)
{
  set(cnf->bmap, pos, exist);
}

void Cnf::restore(Cnf *cnf, CnfEdit *edit)
{
  //  BitMap *deletedClause = edit->deletedClause;
  if (edit->deletedClause != nullptr)
    OR(cnf->bmap, edit->deletedClause); // 还原子句的存在情况

  BitMap **varVec = edit->varVec;
  if (nullptr == varVec)
    return;
  for (uint32_t transformed = 0; transformed < edit->nVarPlusNOT; ++transformed) {
    if (nullptr == varVec[transformed])
      continue;
    BitMap *posMap = varVec[transformed];
    uint32_t var = Clause::FromBufferFormat(transformed);
    for (uint32_t p = 0; p < posMap->len; ++p) {
      if (posMap->get(p)) {
        clVec[p]->addVar(var);
      }
    }
  }
}
