/***************************************************************************
*  @file       LCS.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Longest-common-subsequence problem
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef LCS_H
#define LCS_H

#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

// input X = <x1, x2, ..., xm>, Y = <y1, y2, ..., yn>
// c[0..m, 0..n] 保存 Xi 和 Yj 的 LCS 长度
// b[1..m, 1..n] 帮助构造最优解
void LcsLength(const vector<char> &X, const vector<char> &Y, char ** &b, int ** &c);
void PrintLcs(char ** &b, const vector<char> &X, int X_len, int Y_len);

// 练习 15.4-2 设计伪代码，利用完整的表 c 及原始序列 X 和 Y 来重构 LCS。
// 要求运行时间为 O(m+n)，不能使用表 b。
void LcsLength_v2(const vector<char> &X, const vector<char> &Y, int **&c);
void PrintLcs_v2(const vector<char> &X, int X_len, int Y_len, int **&c);


// 练习 15.4-3 设计 LCS-LENGTH 的带备忘版本，运行时间为 O(mn)
void LcsLengthMemoi(const vector<char> &X, const vector<char> &Y, char ** &b, int **&c);
int LcsLengthMemoiAux(const vector<char> &X, const vector<char> &Y, int i, int j, char** &b, int **&c);

// 练习 15.4-4 说明如何只使用表 c 中 2*min(m, n) 个表项及 O(1) 的额外空间来计算 LCS 的长度。
// 然后说明如何只用 min(m, n) 个表项及 O(1) 的额外空间完成相同的操作。
void LcsLength_v3(const vector<char> &X, const vector<char> &Y);  // 使用 2*min(m, n) 个表项
void LcsLength_v4(const vector<char> &X, const vector<char> &Y);  // 使用 min(m, n) 个表项，未证明正确性。

// just a version for Int number
void LcsLength_v5(const vector<int> &X, const vector<int> &Y, char ** &b, int ** &c);
void PrintLcs_v5(char ** &b, const vector<int> &X, int X_len, int Y_len);
// 练习 15.4-5 设计一个 O(n^2) 时间的算法，求一个 n 个数的序列的最长单调递增子序列longest monotonically increasing subsequence
void Lmis(const vector<char> &X);



void LcsTest();

#endif // !LCS_H