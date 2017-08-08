/***************************************************************************
*  @file       OptimalBst.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.8 2017
*  @remark     optimal binary search tree
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef OPTIMALBST_H
#define OPTIMALBST_H

#include <vector>
using std::vector;

/*
*  @param p 概率列表 p1, ..., pn
*  @param q 概率列表 q0, ..., qn
*  @param n 关键字个数
*  @param e[1..n+1, 0..n] e[i, j]保存在关键字 ki, ..., kj 构成的最优二叉搜索树中进行一次搜索的期望代价
*  @param w[1..n+1, 0..n] w[i, j]保存关键字 ki, ..., kj 构成子树的概率之和
*
*  @remark 直接递归实现，低效
**/
float OptimalBstUgly(float p[], float q[], int n, float ** &e, float ** &w);
float OptimalBstAuxUgly(float ** &e, float ** &w, int i, int j);

/*
 *  @param p 概率列表 p1, ..., pn
 *  @param q 概率列表 q0, ..., qn
 *  @param n 关键字个数
 *  @param e[1..n+1, 0..n] e[i, j]保存在关键字 ki, ..., kj 构成的最优二叉搜索树中进行一次搜索的期望代价
 *  @param w[1..n+1, 0..n] w[i, j]保存关键字 ki, ..., kj 构成子树的概率之和
 *  @param root[1..n, 1..n] root[i, j]记录包含关键字 ki, ..., kj 的子树的根。（只使用 1<=i<=j<=n的表项）
 **/
float OptimalBst(float p[], float q[], int n, float ** &e, float ** &w, int ** &root);
void ConstructOptimalBst(int ** &root, int i, int j);

void OptimalBstTest();


#endif // !OPTIMALBST_H
