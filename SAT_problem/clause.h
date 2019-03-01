#ifndef CLAUSE_H
#define CLAUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include <stdbool.h>

/**
 * @brief The Clause class
 * 至少两个单元表示 L -L
 * 0  1  2  3  4  5 ...
 * L -L  M -M  N -N ...
 *
 * 数字映射规律
 * var ->
 *  >0 ? (var - 1) * 2
 *  <0 ? (-var) * 2 - 1
 * 即 相邻偶数和奇数成 L, -L
 *
 * transformed = base + 数组下标
 */

class Clause
{
public:
  Clause(int _minV, int _maxV);
  Clause(uint32_t _bufCapacity);

  ~Clause()
  {
    delete[] elem;
//    free(elem);
  }

  bool isUnitClause();
  bool getUnit(int *var);
  bool isUnitClauseFallback();
  bool contains(int var);

  // 标记变量被去除
  void rmVar(int var);

  // 标记变量存在
  void addVar(int var);

  bool suspectVar(int var);

  void toString(char strbuf[]);

  static uint32_t toBufferFormat(int var);
  static int FromBufferFormat(uint32_t transformed);
  // 缓存变量，全部缓存之后再处理
  void bufferVar(int var);
  void finishBuffer();
  // 程序退出时释放缓存
  static void releaseBuf() { delete[] varBuf; }

  // 经过转换后，子句内最小变量
  uint32_t minTransformed;
  uint32_t maxTransformed;
  // 变量的最小序号
  uint32_t base;

  uint32_t len;
  bool *elem;
  uint32_t nVarInClause;

  static int *varBuf;
  static uint32_t bufCapacity;
  static uint32_t buffered;
};

int LogicNOT(uint32_t var);

#endif // CLAUSE_H
