/***************************************************************************
*  @file       MatrixChainOrder.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Matrix Chain multiplication
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef MATRIXCHAINORDER_H
#define MATRIXCHAINORDER_H

#include <vector>
#include "Matrix.h"

using std::vector;

// 使用自底向上方法，求解矩阵链括号化问题。
// 假定矩阵 Ai 的规模为 pi-1 x pi (i=1,2,..,n)，问题的输入是一个序列 p=<p0,p1,...,pn>
// 用一个辅助表 m[1..n,1..n] 保存代价 m[i,j]
// 用另一个辅助表 s[1..n-1,2..n] 记录最优值 m[i,j] 对应的分割点 k
// 这里二维数组在函数中动态分配，并修改传入指针
void MatrixChainOrder(const vector<int> &p, int ** &m, int ** &s);

// Recusive top-down implementation with memoization
int MemorizedMatrixChainOrder(const vector<int> &p, int ** &m, int ** &s);
int LookUpChain(const vector<int> &p, int i, int j, int ** &m, int ** &s);

// 利用表s[1..n-1,2..n]构造最优解，输出<A1,A2,..,An>的最优括号化方案
void PrintOptimalParens(int **s, int i, int j);

// 矩阵链最优代价乘法计算,递归算法
// 输入为矩阵序列<A1,A2,...,An>, MatrixChainOrder 得到的表 s 以及下标 i 和 j
template <typename T>
Matrix<T> MatrixChainMultiply(vector<Matrix<T>> &A, int ** &s, int i, int j);

// 测试
void MartixChainOrderTest();

#endif // !MATRIXCHAINORDER_H
