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
*  @param p �����б� p1, ..., pn
*  @param q �����б� q0, ..., qn
*  @param n �ؼ��ָ���
*  @param e[1..n+1, 0..n] e[i, j]�����ڹؼ��� ki, ..., kj ���ɵ����Ŷ����������н���һ����������������
*  @param w[1..n+1, 0..n] w[i, j]����ؼ��� ki, ..., kj ���������ĸ���֮��
*
*  @remark ֱ�ӵݹ�ʵ�֣���Ч
**/
float OptimalBstUgly(float p[], float q[], int n, float ** &e, float ** &w);
float OptimalBstAuxUgly(float ** &e, float ** &w, int i, int j);

/*
 *  @param p �����б� p1, ..., pn
 *  @param q �����б� q0, ..., qn
 *  @param n �ؼ��ָ���
 *  @param e[1..n+1, 0..n] e[i, j]�����ڹؼ��� ki, ..., kj ���ɵ����Ŷ����������н���һ����������������
 *  @param w[1..n+1, 0..n] w[i, j]����ؼ��� ki, ..., kj ���������ĸ���֮��
 *  @param root[1..n, 1..n] root[i, j]��¼�����ؼ��� ki, ..., kj �������ĸ�����ֻʹ�� 1<=i<=j<=n�ı��
 **/
float OptimalBst(float p[], float q[], int n, float ** &e, float ** &w, int ** &root);
void ConstructOptimalBst(int ** &root, int i, int j);

void OptimalBstTest();


#endif // !OPTIMALBST_H
