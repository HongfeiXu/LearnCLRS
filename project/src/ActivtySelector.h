/***************************************************************************
*  @file       ActivitySelector.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.8 2017
*  @remark     An activity-selection problem
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef ACITVITYSELECTOR_H
#define ACTIVITYSELECTOR_H

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

//////////////////////////////////////////////////////////////////////////
// 贪婪算法实现

/*
 *  递归版本
 *
 *  @param s[i] 活动 a_i 开始时间
 *  @param f[i] 活动 a_i 结束时间
 *  @param k   指出要求解的子问题为 S_k，S_k为在活动 a_k 结束后开始的任务集合
 *  @param n   问题规模
 *  @param a   S_k 的一个最大兼容活动集
 *
 *  @remark 活动已按结束时间排序，这里选择最早结束的活动加入到最优解
 **/
void RecursiveAcitvitySelector(int s[], int f[], int k, int n, vector<int> &a);

/*
 *  迭代版本
 **/
void AcitvitySelector(int s[], int f[], int n, vector<int> &A);

//////////////////////////////////////////////////////////////////////////
// 动态规划实现（练习16.1-1）

/*
 *  带备忘机制的递归算法，参考 MemorizedMatrixChain() 算法，书本 p220~p221
 *
 *  @param s[] s[i] 是活动 a_i 的开始时间
 *  @param f[] f[i] 是活动 a_i 的结束时间
 *  @param n 活动集合的规模
 *  @param c[][] c[i][j] 为集合 S_ij 的最优解的大小
 *  @param memo[][] memo[i][j] 记录集合 S_ij 的最优解包含的一个活动
 *
 *  @remark S_ij 表示在活动 a_i 结束之后开始，且在 a_j 开始之前结束的那些活动的集合
 **/
void ActivitySelectorDP(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo);
void ActivitySelectorDpAux(vector<int> s, vector<int> f, int i, int j, int ** &c, int ** &memo);

/*
*  自底向上法,参考MatrixChainOrder() 算法，书本p213，
*  参考 https://code.csdn.net/mishifangxiangdefeng/exerciseforalgorithmsecond/tree/master/src/chapter16/Exercise16_1_1.cpp
*
*  @param s[] s[i] 是活动 a_i 的开始时间
*  @param f[] f[i] 是活动 a_i 的结束时间
*  @param n 活动集合的规模
*  @param c[][] c[i][j] 为集合 S_ij 的最优解的大小
*  @param memo[][] memo[i][j] 记录集合 S_ij 的最优解包含的一个活动
*
*  @remark S_ij 表示在活动 a_i 结束之后开始，且在 a_j 开始之前结束的那些活动的集合
**/
void ActivitySelectorDp_2(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo);

/*
* @param memo[][] memo[i][j] 记录集合 S_ij 的最优解包含的一个活动
* @param i, j     S_ij 的下标
* @param A        S_ij 的最大相互兼容活动子集（保存活动的下标）
*
* @remark         根据 memo 的信息来得到最优解
**/
void GetA(int ** &memo, int i, int j, vector<int> &A);

void ActivitySelectorTest();

#endif // !ACTIVITYSELECTOR_H
