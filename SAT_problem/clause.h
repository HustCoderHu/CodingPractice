#ifndef CLAUSE_H
#define CLAUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "bitmap.h"

//#include <stdbool.h> // bool in C

class ClauseEdit;

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
  Clause(uint32_t varBufCapacity);

  ~Clause()
  {
    delete[] elem;
//    free(elem);
  }

  // 判定单子句
  bool isUnitClause();
  // 获取单子句的变元
  bool getUnit(int *var);
  bool isUnitClauseFallback();
  // 判定是否包含某个变元
  bool contains(int var);
  // 标记变量存在 或者 被去除
  void markVarExist(int var, bool flag);
  int getVar(uint32_t idx);
  bool verify(BitMap *resoMap);

  // 可读的变量 向 存储变量转换
  static uint32_t toBufferFormat(int var);
  // 反向
  static int FromBufferFormat(uint32_t transformed);
  // 缓存变量
  void bufferVar(int var);
  // 全部缓存之后转换为存储结构
  void finishBuffer();
  // 程序退出时释放缓存空间
  static void releaseBuf() { delete[] varBuf; }

  // 可读的子句
  void toString(char strbuf[]);

  // 经过转换后，子句内最小变量 minTransformed
  uint32_t base;
  // 最大
  uint32_t maxTransformed;

  // 底层存储结构
  uint16_t *elem;
  // 底层存储长度
  uint32_t len;
  // 子句里的变元个数
  uint32_t nVarInClause;

  // 缓存结构
  static int *varBuf;
  static uint32_t bufCapacity;
  static uint32_t buffered;
};

class ClauseEdit
{
public:
  ClauseEdit(uint32_t _len)
  {
    deletedVar = new int[_len];
    len = _len;
    nDeleted = 0;
  }
  ~ClauseEdit()
  {
    delete[] deletedVar;
  }

  void delVar(int var)
  {
    deletedVar[nDeleted++] = var;
  }
  void reset() { nDeleted = 0; }

  int *deletedVar;
  uint32_t len;
  uint32_t nDeleted;
};

#endif // CLAUSE_H
