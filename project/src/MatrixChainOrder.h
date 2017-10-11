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

// ʹ���Ե����Ϸ����������������Ż����⡣
// �ٶ����� Ai �Ĺ�ģΪ pi-1 x pi (i=1,2,..,n)�������������һ������ p=<p0,p1,...,pn>
// ��һ�������� m[1..n,1..n] ������� m[i,j]
// ����һ�������� s[1..n-1,2..n] ��¼����ֵ m[i,j] ��Ӧ�ķָ�� k
// �����ά�����ں����ж�̬���䣬���޸Ĵ���ָ��
void MatrixChainOrder(const vector<int> &p, int ** &m, int ** &s);

// Recusive top-down implementation with memoization
int MemorizedMatrixChainOrder(const vector<int> &p, int ** &m, int ** &s);
int LookUpChain(const vector<int> &p, int i, int j, int ** &m, int ** &s);

// ���ñ�s[1..n-1,2..n]�������Ž⣬���<A1,A2,..,An>���������Ż�����
void PrintOptimalParens(int **s, int i, int j);

// ���������Ŵ��۳˷�����,�ݹ��㷨
// ����Ϊ��������<A1,A2,...,An>, MatrixChainOrder �õ��ı� s �Լ��±� i �� j
template <typename T>
Matrix<T> MatrixChainMultiply(vector<Matrix<T>> &A, int ** &s, int i, int j);

// ����
void MartixChainOrderTest();

#endif // !MATRIXCHAINORDER_H
