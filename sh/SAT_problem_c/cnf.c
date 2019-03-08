#include "cnf.h"

const uint32_t LINE_MAX_LEN = 80;

Cnf *createCnf()
{
  Cnf *cnf = (Cnf*)malloc(sizeof(*cnf));
  cnf->nVar = 0;
  cnf->nClause = 0;
  cnf->bmap = NULL;
  cnf->clVec = NULL;
  return cnf;
}

void destroyCnf(Cnf *cnf)
{
  if (NULL == cnf->bmap)
    return;
  Clause **clVec = cnf->clVec;
  uint32_t i;
  for (i = 0; i < cnf->nClause; ++i) {
    if (clVec[i] != NULL) {
      free(clVec[i]);
    }
  }
  free(clVec);
  free(cnf->bmap);
}

void parseFile(Cnf *cnf, const char* fpath)
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

  printf("nVar: %d\n", cnf->nVar);
  printf("nClause: %d\n", cnf->nClause);

  Clause **clVec;
  clVec = (Clause**)malloc(sizeof(*clVec[0]) * cnf->nClause);
  cnf->clVec = clVec;
  cnf->bmap = createBitmap(cnf->nClause);

  uint32_t i;
  for (i = 0; i < cnf->nClause; ++i) {
    fgets(buf, LINE_MAX_LEN, fp);
    clVec[i] = parseLine(buf);
    markClauseExist(cnf, i, true);
  }

  fclose(fp);
}

Clause *parseLine(char *buf)
{
  int var;
  //  uint32_t nVar = countNvar(buf);
  Clause *cl = createClause(10);

  char* token = strtok(buf, " ");
  while ( token != NULL ) {
    var = atoi(token);
    if (0 == var)
      break;
    bufferVar(cl, var);
    token = strtok(NULL, " ");
  }
  finishBuffer(cl);
  return cl;
}

bool getSimple(Cnf *cnf, int *var)
{
  uint32_t i;
  for (i = 0; i < cnf->nClause; ++i) {
    if (existClause(cnf, i)) {
      Clause **clVec = cnf->clVec;
      if (getUnit(clVec[i], var))
        return true;
    }
  }
  return false;
}

Clause *getShortestClause(Cnf *cnf)
{
  Clause **clVec = cnf->clVec;
  uint32_t minLen = -1;
  Clause *shortest = NULL;
  uint32_t i;
  for (i = 0; i < cnf->nClause; ++i) {
    if (existClause(cnf, i) && clVec[i]->nVarInClause <= minLen) {
      minLen = clVec[i]->nVarInClause;
      shortest = clVec[i];
    }
  }
  return shortest;
}

Clause *getFirstExistClause(Cnf *cnf)
{
  for (uint32_t i = 0; i < cnf->nClause; ++i) {
    if (existClause(cnf, i)) {
      return cnf->clVec[i];
    }
  }
  return NULL;
}

bool isEmpty(Cnf *cnf)
{
  return isAllFalse(cnf->bmap);
}

void showCnf(Cnf *cnf)
{
  char display[80];
  uint32_t i;
  for (i = 0; i < cnf->nClause; ++i) {
    if (existClause(cnf, i)) {
      Clause *cl = cnf->clVec[i];
      toString(cl, display);
      printf("%s\n", display);
    }
  }
}

bool existClause(Cnf *cnf, uint32_t pos)
{
  return get(cnf->bmap, pos);
}

void markClauseExist(Cnf *cnf, uint32_t pos, bool exist)
{
  set(cnf->bmap, pos, exist);
}

void restore(Cnf *cnf, CnfEdit *edit)
{
  //  BitMap *deletedClause = edit->deletedClause;
  if (edit->deletedClause != NULL)
    OR(cnf->bmap, edit->deletedClause); // 还原子句的存在情况

  Bitmap **varVec = edit->varVec;
  if (NULL == varVec)
    return;
  uint32_t transformed;
  for (transformed = 0; transformed < edit->nVarPlusNOT; ++transformed) {
    if (NULL == varVec[transformed])
      continue;
    Bitmap *posMap = varVec[transformed];
    uint32_t var = FromBufferFormat(transformed);
    uint32_t p;
    for (p = 0; p < posMap->len; ++p) {
      if (get(posMap, p)) {
        Clause *cl = cnf->clVec[p];
        addVar(cl, var);
      }

    }
  }
}




