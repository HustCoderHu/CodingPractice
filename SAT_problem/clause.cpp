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

bool Clause::getUnit(int *var)
{
  if (nVarInClause != 1)
    return false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i]) {
      uint32_t transformed = base + i;
      *var = FromBufferFormat(transformed);
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
  uint32_t transformed = toBufferFormat(var);
  return (transformed < base || transformed >= base + len) ?
        false : elem[transformed-base];
}

void Clause::markVarExist(int var, bool flag)
{
  uint32_t transformed = toBufferFormat(var);
  if (transformed < base || transformed >= base + len)
    return;
  if (flag == elem[transformed-base])
    return;
  if (flag) {
    elem[transformed-base] = true;
    ++nVarInClause;
  } else {
    elem[transformed-base] = false;
    --nVarInClause;
  }
}

int Clause::getVar(uint32_t idx)
{
  uint32_t varIdx = 0;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i]) {
      if (varIdx == idx) {
        uint32_t transformed = base + i;
        return FromBufferFormat(transformed);
      } else
        ++varIdx;
    }
  }
  return -1;
}

bool Clause::verify(BitMap *resoMap)
{
  bool res = false;
  for (uint32_t i = 0; i < len; ++i) {
    if (elem[i]) {
      uint32_t transformed = base + i;
      int var = FromBufferFormat(transformed);
      if (var > 0)
        res = resoMap->get(var-1);
      else
        res = !resoMap->get(-var-1);
      if (res)
        break;
    }
  }
  return res;
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
  //  minTransformed = transformed < minTransformed ? transformed : minTransformed;
  base = transformed < base ? transformed : base;
  maxTransformed = transformed > maxTransformed ? transformed : maxTransformed;
}

void Clause::finishBuffer()
{
  //  base = minTransformed >> 1;
  len = ((maxTransformed>>1) - (base>>1)) + 1; // 变量个数，不包括取反
  len <<= 1; // 记录反变量的空间
  elem = new uint16_t[len]; //malloc(sizeof(int) * n);
  memset(elem, 0, sizeof(elem[0]) * len);

  for (uint32_t i = 0; i < buffered; ++i) {
    uint32_t transformed = varBuf[i];
    if (elem[transformed-base] == false) {
      elem[transformed-base] = true;
      ++nVarInClause;
    }
  }
}

Clause::Clause(uint32_t varBufCapacity)
{
  base = -1; // uint32_t max
  //  minTransformed = -1; // uint32_t max
  maxTransformed = 0;
  elem = nullptr;
  len = 0;
  nVarInClause = 0;

  if (nullptr == varBuf) {
    bufCapacity = varBufCapacity;
    varBuf = new int[bufCapacity];
  }
  buffered = 0;
}
