#include "clause.h"

int *Clause::varBuf = nullptr;
uint32_t Clause::bufCapacity = 10;
uint32_t Clause::buffered = 0;

bool Clause::isUnitClause()
{
  if (nVarInClause != 1)
    return false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i])
      return true;
  }
  return false;
}

bool Clause::getUnit(uint32_t *var)
{
  if (nVarInClause != 1)
    return false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i]) {
      *var = i;
      return true;
    }
  }
  return false;
}

bool Clause::isUnitClauseFallback()
{
  bool found = false;
  for(uint32_t i = 0; i < len; ++i) {
    if (elem[i] != 0)
      if (!found)
        found = true;
    //        else
  }
  return false;
}

bool Clause::contains(int var)
{
  return (var < minV || var >= minV + len) ?
        false : elem[var-minV];

  if (var < minV || var >= minV + len)
    return false;
  return elem[var-minV];
}

void Clause::rmVar(int var)
{
  if (var < minV || var >= minV + len)
    return;
  if (true == elem[var-minV])
    --nVarInClause;
  elem[var-minV] = false;
}

void Clause::addVar(int var)
{
  if (var < minV || var >= minV + len)
    return;
  if (elem[var-minV] == false)
    ++nVarInClause;
  elem[var-minV] = true;
}

bool Clause::suspectVar(int var)
{
  if (var < len)
    elem[var] = false;
  return true;
}

void Clause::toString(char strbuf[])
{
  uint32_t strlen = 0;
  for (uint32_t offset = 0; offset < len; ++offset) {
    if (elem[offset]) {
      uint32_t transformed = base + offset;
      int var = FromBufferFormat(transformed);
      int addedBytes =  sprintf(strbuf + strlen, "%d ", var);
      strlen += addedBytes;
    }
  }
}

uint32_t Clause::toBufferFormat(int var)
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

int Clause::FromBufferFormat(uint32_t transformed)
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

void Clause::bufferVar(int var)
{
  // 超出缓存空间，缓存扩容
  if (buffered >= bufCapacity) {
    uint32_t newCapacity = bufCapacity + (bufCapacity >> 1); // 容量 1.5 倍
    int *newBuf = new int[newCapacity];
    memcpy(newBuf, varBuf, buffered);
    delete[] varBuf;
    varBuf = newBuf;
  }
  uint32_t transformed = toBufferFormat(var);
  varBuf[buffered++] = transformed;
  minV = transformed < minV ? transformed : minV;
  maxV = transformed > maxV ? transformed : maxV;
}

void Clause::finishBuffer()
{
  base = minV >> 1;
  len = ((maxV>>1) - base) + 1; // 变量个数，不包括取反
  len <<= 1; // 记录反变量的空间
  elem = new bool[len]; //malloc(sizeof(int) * n);
  memset(elem, 0, sizeof(elem[0]) * len);

  for (uint32_t i = 0; i < buffered; ++i) {
    uint32_t transformed = varBuf[i];
    if (elem[transformed-base] == false) {
      elem[transformed-base] = true;
      ++nVarInClause;
    }
  }
}

Clause::Clause(int _minV, int _maxV)
{
  //    len = ;
  nVarInClause = 0;
  minV = _minV;
  len = _maxV - _minV + 1;
  elem = new bool[len]; //malloc(sizeof(int) * n);

  for (uint32_t i = 0; i < len; ++i)
    elem[i] = false;
}

Clause::Clause(uint32_t _bufCapacity)
{
  minV = -1; // uint32_t max
  maxV = 0;

  if (nullptr == varBuf) {
    bufCapacity = _bufCapacity;
    varBuf = new int[bufCapacity];
  }
  buffered = 0;
}
