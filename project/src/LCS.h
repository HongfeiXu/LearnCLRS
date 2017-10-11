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
// c[0..m, 0..n] ���� Xi �� Yj �� LCS ����
// b[1..m, 1..n] �����������Ž�
void LcsLength(const vector<char> &X, const vector<char> &Y, char ** &b, int ** &c);
void PrintLcs(char ** &b, const vector<char> &X, int X_len, int Y_len);

// ��ϰ 15.4-2 ���α���룬���������ı� c ��ԭʼ���� X �� Y ���ع� LCS��
// Ҫ������ʱ��Ϊ O(m+n)������ʹ�ñ� b��
void LcsLength_v2(const vector<char> &X, const vector<char> &Y, int **&c);
void PrintLcs_v2(const vector<char> &X, int X_len, int Y_len, int **&c);


// ��ϰ 15.4-3 ��� LCS-LENGTH �Ĵ������汾������ʱ��Ϊ O(mn)
void LcsLengthMemoi(const vector<char> &X, const vector<char> &Y, char ** &b, int **&c);
int LcsLengthMemoiAux(const vector<char> &X, const vector<char> &Y, int i, int j, char** &b, int **&c);

// ��ϰ 15.4-4 ˵�����ֻʹ�ñ� c �� 2*min(m, n) ����� O(1) �Ķ���ռ������� LCS �ĳ��ȡ�
// Ȼ��˵�����ֻ�� min(m, n) ����� O(1) �Ķ���ռ������ͬ�Ĳ�����
void LcsLength_v3(const vector<char> &X, const vector<char> &Y);  // ʹ�� 2*min(m, n) ������
void LcsLength_v4(const vector<char> &X, const vector<char> &Y);  // ʹ�� min(m, n) �����δ֤����ȷ�ԡ�

// just a version for Int number
void LcsLength_v5(const vector<int> &X, const vector<int> &Y, char ** &b, int ** &c);
void PrintLcs_v5(char ** &b, const vector<int> &X, int X_len, int Y_len);
// ��ϰ 15.4-5 ���һ�� O(n^2) ʱ����㷨����һ�� n ���������е����������������longest monotonically increasing subsequence
void Lmis(const vector<char> &X);



void LcsTest();

#endif // !LCS_H