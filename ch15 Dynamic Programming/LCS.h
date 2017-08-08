/***************************************************************************
*  @file       LCS.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Longest-common-subsequence problem
*  @platform   visual studio 2013, windows 10
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

void LcsTest();


#endif // !LCS_H