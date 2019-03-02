#include "cnf.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

static uint32_t lenInt(int v);

//#define LINE_MAX_LEN 80

Cnf::Cnf()
{
  nVar = 0;
  nClause = 0;
  nCur = 0;
  clVec = nullptr;
  bmap = nullptr;
}

Cnf::~Cnf()
{
  delete bmap;
  for (uint32_t i = 0; i < nClause; ++i) {
    if (clVec[i]) {
      delete clVec;
    }
  }
  delete[] clVec;
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
  sscanf(buf, "p cnf %d %d", &nVar, &nClause);

  cout << "nVar: " << nVar << endl;
  cout << "nClause: " << nClause << endl;

  clVec = new Clause*[nClause];
  bmap = new BitMap(nClause);

  for (nCur = 0; nCur < nClause; ++nCur) {
    fgets(buf, LINE_MAX_LEN, fp);
    clVec[nCur] = parseLine(buf);
    markClauseExist(nCur, true);
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

uint32_t Cnf::countNvar(char buf[])
{
  uint32_t nVar = 0;
  char pre = ' ';
  for (uint32_t i = 0; buf[i] != '\0'; ++i) {
    if (isdigit(buf[i]) && (' ' == pre || '-' == pre))
      ++nVar;
    pre = buf[i];
  }
  return nVar;
}

bool Cnf::getSimple(int *var)
{
  for (uint32_t i = 0; i < nClause; ++i) {
    if (existClause(i)) {
      if (clVec[i]->getUnit(var)) {
        return true;
      }
    }
  }
  return false;
}

Clause *Cnf::getShortestClause()
{
  uint32_t minLen = -1;
  Clause *shortest = nullptr;
  for (uint32_t i = 0; i < nClause; ++i) {
    if (existClause(i) && clVec[i]->nVarInClause < minLen) {
      minLen = clVec[i]->nVarInClause;
      shortest = clVec[i];
    }
  }
  return shortest;
}

Clause *Cnf::getRandomClause()
{
  int idx = rand() % (nClause>>3);
  uint32_t j = 0;
  for (uint32_t i = 0; i < idx; ++j) {
    j = j >= nClause ? j-nClause : j;
    if (existClause(j)) {
      ++i;
    }
  }
  return clVec[j];
}

void Cnf::show()
{
  char display[80];
  for (uint32_t i = 0; i < nClause; ++i) {
    if (existClause(i)) {
      clVec[i]->toString(display);
      printf("%s\n", display);
    }
  }
}

bool Cnf::existClause(uint32_t pos)
{
  return bmap->get(pos);
}

void Cnf::markClauseExist(uint32_t pos, bool exist)
{
  bmap->set(pos, exist);
}

void Cnf::restore(CnfEdit *edit)
{
  //  BitMap *deletedClause = edit->deletedClause;
  if (edit->deletedClause != nullptr)
    bmap->OR(edit->deletedClause); // 还原子句的存在情况

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

static uint32_t lenInt(int v)
{
  if (v < 0)
    v = -v;
  unsigned int len = 1;

  v /= 10;
  while (v != 0) {
    ++len;
    v /= 10;
  }
  return len;
}
