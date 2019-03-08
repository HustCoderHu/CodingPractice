#ifndef CLAUSE_H
#define CLAUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "bitmap.h"

//#include <stdbool.h> // bool in C

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

typedef struct
{
  // 经过转换后，子句内最小变量 minTransformed
  uint32_t base;
  // 最大
  uint32_t maxTransformed;

  // 底层存储结构
  bool *elem;
  // 底层存储长度
  uint32_t len;
  // 子句里的变元个数
  uint32_t nVarInClause;
} Clause;

Clause *createClause(uint32_t varBufCapacity);
void destroyClause(Clause *cl);

// 判定单子句
bool isUnitClause(Clause *cl);
// 获取单子句的变元
bool getUnit(Clause *cl, int *var);
bool isUnitClauseFallback(Clause *cl);
// 判定是否包含某个变元
bool contains(Clause *cl, int var);
// 标记变量存在 或者 被去除
void markVarExist(Clause *cl, int var, bool flag);
int getVar(Clause *cl, uint32_t idx);
bool verifyClause(Clause *cl, Bitmap *resoMap);

// 标记变量被去除
void rmVar(Clause *cl, int var);
// 标记变量存在
void addVar(Clause *cl, int var);

// 可读的变量 向 存储变量转换
uint32_t toBufferFormat(int var);
// 反向
int FromBufferFormat(uint32_t transformed);
// 缓存变量
void bufferVar(Clause *cl, int var);
// 全部缓存之后转换为存储结构
void finishBuffer(Clause *cl);
// 程序退出时释放缓存空间
void releaseBuf();

// 可读的子句
void toString(Clause *cl, char strbuf[]);

// 缓存结构
//extern int *varBuf;
//extern uint32_t bufCapacity;
//extern uint32_t buffered;

#endif // CLAUSE_H
