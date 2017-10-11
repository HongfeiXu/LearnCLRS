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
// ̰���㷨ʵ��

/*
 *  �ݹ�汾
 *
 *  @param s[i] � a_i ��ʼʱ��
 *  @param f[i] � a_i ����ʱ��
 *  @param k   ָ��Ҫ����������Ϊ S_k��S_kΪ�ڻ a_k ������ʼ�����񼯺�
 *  @param n   �����ģ
 *  @param a   S_k ��һ�������ݻ��
 *
 *  @remark ��Ѱ�����ʱ����������ѡ����������Ļ���뵽���Ž�
 **/
void RecursiveAcitvitySelector(int s[], int f[], int k, int n, vector<int> &a);

/*
 *  �����汾
 **/
void AcitvitySelector(int s[], int f[], int n, vector<int> &A);

//////////////////////////////////////////////////////////////////////////
// ��̬�滮ʵ�֣���ϰ16.1-1��

/*
 *  ���������Ƶĵݹ��㷨���ο� MemorizedMatrixChain() �㷨���鱾 p220~p221
 *
 *  @param s[] s[i] �ǻ a_i �Ŀ�ʼʱ��
 *  @param f[] f[i] �ǻ a_i �Ľ���ʱ��
 *  @param n ����ϵĹ�ģ
 *  @param c[][] c[i][j] Ϊ���� S_ij �����Ž�Ĵ�С
 *  @param memo[][] memo[i][j] ��¼���� S_ij �����Ž������һ���
 *
 *  @remark S_ij ��ʾ�ڻ a_i ����֮��ʼ������ a_j ��ʼ֮ǰ��������Щ��ļ���
 **/
void ActivitySelectorDP(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo);
void ActivitySelectorDpAux(vector<int> s, vector<int> f, int i, int j, int ** &c, int ** &memo);

/*
*  �Ե����Ϸ�,�ο�MatrixChainOrder() �㷨���鱾p213��
*  �ο� https://code.csdn.net/mishifangxiangdefeng/exerciseforalgorithmsecond/tree/master/src/chapter16/Exercise16_1_1.cpp
*
*  @param s[] s[i] �ǻ a_i �Ŀ�ʼʱ��
*  @param f[] f[i] �ǻ a_i �Ľ���ʱ��
*  @param n ����ϵĹ�ģ
*  @param c[][] c[i][j] Ϊ���� S_ij �����Ž�Ĵ�С
*  @param memo[][] memo[i][j] ��¼���� S_ij �����Ž������һ���
*
*  @remark S_ij ��ʾ�ڻ a_i ����֮��ʼ������ a_j ��ʼ֮ǰ��������Щ��ļ���
**/
void ActivitySelectorDp_2(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo);

/*
* @param memo[][] memo[i][j] ��¼���� S_ij �����Ž������һ���
* @param i, j     S_ij ���±�
* @param A        S_ij ������໥���ݻ�Ӽ����������±꣩
*
* @remark         ���� memo ����Ϣ���õ����Ž�
**/
void GetA(int ** &memo, int i, int j, vector<int> &A);

void ActivitySelectorTest();

#endif // !ACTIVITYSELECTOR_H
