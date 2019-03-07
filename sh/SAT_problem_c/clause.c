#include "clause.h"

int *varBuf = NULL;
uint32_t bufCapacity = 10;
uint32_t buffered = 0;

Clause *createClause(uint32_t varBufCapacity)
{
  Clause *cl = (Clause*)malloc(sizeof(*cl));
  cl->base = -1; // uint32_t max
  //  minTransformed = -1; // uint32_t max
  cl->maxTransformed = 0;
  cl->elem = NULL;
  cl->len = 0;
  cl->nVarInClause = 0;

  if (NULL == varBuf) {
    bufCapacity = varBufCapacity;
    varBuf = (int*)malloc(sizeof(int)*bufCapacity);
  }
  buffered = 0;
  return cl;
}

void destroyClause(Clause *cl)
{
  if(cl->elem != NULL)
    free(cl->elem);
}

bool isUnitClause(Clause *cl)
{
  if (cl->nVarInClause != 1)
    return false;
  for (uint32_t i = 0; i < cl->len; ++i) {
    if (cl->elem[i])
      return true;
  }
  return false;
}

bool getUnit(Clause *cl, int *var)
{
  if (cl->nVarInClause != 1)
    return false;
  for (uint32_t i = 0; i < cl->len; ++i) {
    if (cl->elem[i]) {
      uint32_t transformed = cl->base + i;
      *var = FromBufferFormat(transformed);
      return true;
    }
  }
  return false;
}

bool isUnitClauseFallback(Clause *cl)
{
  bool found = false;
  for(uint32_t i = 0; i < cl->len; ++i) {
    if (cl->elem[i] != 0)
      if (!found)
        found = true;
    //        else
  }
  return false;
}

bool contains(Clause *cl, int var)
{
  uint32_t transformed = toBufferFormat(var);
  return (transformed < cl->base || transformed >= cl->base + cl->len) ?
        false : cl->elem[transformed-cl->base];
}

void markVarExist(Clause *cl, int var, bool flag)
{
  uint32_t base = cl->base;
  uint32_t len = cl->len;
  uint32_t transformed = toBufferFormat(var);
  if (transformed < base || transformed >= base + len)
    return;
  if (flag == cl->elem[transformed-base])
    return;
  if (flag) {
    cl->elem[transformed-base] = true;
    ++cl->nVarInClause;
  } else {
    cl->elem[transformed-base] = false;
    --cl->nVarInClause;
  }
}

int getVar(Clause *cl, uint32_t idx)
{
  uint32_t varIdx = 0;
  for (uint32_t i = 0; i < cl->len; ++i) {
    if (cl->elem[i]) {
      if (varIdx == idx) {
        uint32_t transformed = cl->base + i;
        return FromBufferFormat(transformed);
      } else
        ++varIdx;
    }
  }
  return -1;
}

bool verifyClause(Clause *cl, Bitmap *resoMap)
{
  bool res = false;
  for (uint32_t i = 0; i < cl->len; ++i) {
    if (cl->elem[i]) {
      uint32_t transformed = cl->base + i;
      int var = FromBufferFormat(transformed);
      if (var > 0)
        res = get(resoMap, var-1);
      else
        res = !get(resoMap, -var-1);
      if (res)
        break;
    }
  }
  return res;
}

void rmVar(Clause *cl,int var)
{
  uint32_t transformed = toBufferFormat(var);
  if (transformed < cl->base || transformed >= cl->base + cl->len)
    return;
  if (true == cl->elem[transformed-cl->base]) {
    cl->elem[transformed-cl->base] = false;
    --cl->nVarInClause;
  }
}

void addVar(Clause *cl, int var)
{
  uint32_t transformed = toBufferFormat(var);
  if (transformed < cl->base || transformed >= cl->base + cl->len)
    return;
  if (false == cl->elem[transformed-cl->base]) {
    cl->elem[transformed-cl->base] = true;
    ++cl->nVarInClause;
  }
}

void toString(Clause *cl, char strbuf[])
{
  uint32_t strlen = 0;
  for (uint32_t offset = 0; offset < cl->len; ++offset) {
    if (cl->elem[offset]) {
      uint32_t transformed = cl->base + offset;
      int var = FromBufferFormat(transformed);
      int addedBytes =  sprintf(strbuf + strlen, "%d ", var);
      strlen += addedBytes;
    }
  }
}

uint32_t toBufferFormat(int var)
{
  uint32_t transformed;
  if (var > 0) {
    transformed = (var - 1) << 1; // (var-1)*2
  } else {
    // (-var)*2-1
    // = (~var + 1) * 2 - 1
    // = (~var) * 2 + 1
    // = (~var) << 1 + 1
    transformed = ((~var) << 1) | 0x1;
  }
  return transformed;
}

int FromBufferFormat(uint32_t transformed)
{
  int var;
  if (transformed & 0x1) {
    // 原数是负数
    var = ~(transformed >> 1);
  } else {
    var = (transformed >> 1) + 1;
  }
  return var;
}

void bufferVar(Clause *cl, int var)
{
  // 超出缓存空间，缓存扩容
  if (buffered >= bufCapacity) {
    uint32_t newCapacity = bufCapacity + (bufCapacity >> 1); // 容量 1.5 倍
    int *newBuf = (int*)malloc(sizeof(*newBuf) * newCapacity);
    memcpy(newBuf, varBuf, buffered);
    free(varBuf);
    varBuf = newBuf;
  }
  uint32_t transformed = toBufferFormat(var);
  varBuf[buffered++] = transformed;
  //  minTransformed = transformed < minTransformed ? transformed : minTransformed;
  cl->base = transformed < cl->base ? transformed : cl->base;
  cl->maxTransformed = transformed > cl->maxTransformed ? transformed : cl->maxTransformed;
}

void finishBuffer(Clause *cl)
{
  //  cl->base = minTransformed >> 1;
  cl->len = ((cl->maxTransformed>>1) - (cl->base>>1)) + 1; // 变量个数，不包括取反
  cl->len <<= 1; // 记录反变量的空间
  cl->elem = malloc(sizeof(bool) * cl->len);
  memset(cl->elem, 0, sizeof(cl->elem[0]) * cl->len);

  for (uint32_t i = 0; i < buffered; ++i) {
    uint32_t transformed = varBuf[i];
    if (cl->elem[transformed-cl->base] == false) {
      cl->elem[transformed-cl->base] = true;
      ++cl->nVarInClause;
    }
  }
}

void releaseBuf()
{
  if (varBuf != NULL)
    free(varBuf);
}


