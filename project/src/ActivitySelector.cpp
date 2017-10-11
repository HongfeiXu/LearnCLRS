/***************************************************************************
*  @file       ActivtySelector.cpp
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.8 2017
*  @remark     An activity-selection problem
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "ActivtySelector.h"

void RecursiveAcitvitySelector(int s[], int f[], int k, int n, vector<int> &A)
{
	int m = k + 1;
	while (m <= n && s[m] < f[k])  // find the first activity in S_k to finish
		m++;
	if (m <= n)
	{
		A.push_back(m);
		RecursiveAcitvitySelector(s, f, m, n, A);
	}
}

void AcitvitySelector(int s[], int f[], int n, vector<int> &A)
{
	A.clear();
	A.push_back(1);
	int k = 1;
	for (int m = 2; m <= n; m++)
	{
		if (s[m] >= f[k])
		{
			A.push_back(m);
			k = m;
		}
	}
}

void ActivitySelectorDP(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo)
{
	// 初始化 c[][] 和 memo[][]
	c = new int*[n + 2];
	memo = new int*[n + 2];
	for (int i = 0; i < n + 2; i++)
	{
		c[i] = new int[n + 2];
		memo[i] = new int[n + 2];
	}
	for (int i = 0; i < n + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			c[i][j] = 0;      // c[][] 默认置为 0
			memo[i][j] = -1;  // memo[][] 默认置为 -1
		}
	}

	ActivitySelectorDpAux(s, f, 0, n + 1, c, memo);
	cout << c[0][n + 1] << endl;
}

void ActivitySelectorDpAux(vector<int> s, vector<int> f, int i, int j, int ** &c, int ** &memo)
{
	if (c[i][j] > 0)// 已经计算了 S_ij 的最优解
		return;
	if (j < i + 2)  // 此时 S_ij 为空， c[i][j] = 0
		return;
	else
	{
		for (int k = i + 1; k <= j - 1; k++)
		{
			// 当 a_k 属于 S_ij 时，找最优的 k
			if (s[k] >= f[i] && f[k] <= s[j])
			{
				// 寻找 S_ik 中的兼容活动，更新 c[][]，memo[]
				ActivitySelectorDpAux(s, f, i, k, c, memo);
				// 寻找 S_kj 中的兼容活动，更新 c[][]，memo[]
				ActivitySelectorDpAux(s, f, k, j, c, memo);
				int temp = c[i][k] + c[k][j] + 1;
				if (c[i][j] < temp)
				{
					c[i][j] = temp;
					memo[i][j] = k;
				}
			}
		}
	}
}

void ActivitySelectorDp_2(vector<int> s, vector<int> f, int n, int ** &c, int ** &memo)
{
	// 初始化 c[][] 和 memo[][]
	c = new int*[n + 2];
	memo = new int*[n + 2];
	for (int i = 0; i < n + 2; i++)
	{
		c[i] = new int[n + 2];
		memo[i] = new int[n + 2];
	}
	for (int i = 0; i < n + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			c[i][j] = 0;      // c[][] 默认置为 0
			memo[i][j] = -1;  // memo[][] 默认置为 -1
		}
	}

	// 根据 S_ij 的定义，当 j < i+2 时（step < 2 时）， S_ij 必为空集，此时 c[i][j] = 0
	for (int step = 2; step <= n + 1; step++)
	{
		for (int i = 0; i <= n + 1 - step; i++)
		{
			int j = i + step;

			// 根据 S_ij 的定义，当 f[i] > s[j] 时， S_ij 必为空集，c[i][j] = 0
			if (f[i] <= s[j])
			{
				for (int k = i + 1; k <= j - 1; k++)
				{
					// 根据公式 16.2， 当 a_k 属于 S_ij 时，找最优的 k
					if (s[k] >= f[i] && f[k] <= s[j])
					{
						int temp = c[i][k] + c[k][j] + 1;
						if (c[i][j] < temp)
						{
							c[i][j] = temp;
							memo[i][j] = k;
						}
					}
				}
			}
		}
	}
	cout << c[0][n + 1] << endl;
}

void GetA(int ** &memo, int i, int j, vector<int> &A)
{
	int temp = memo[i][j];
	if (temp > 0)
	{
		GetA(memo, i, temp, A);
		A.push_back(temp);
		GetA(memo, temp, j, A);
	}
}

void ActivitySelectorTest()
{
	//////////////////////////////////////////////////////////////////////////
	// test greedy algorithm

	//int s[] = { 0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	//int f[] = { 0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };
	//int n = 11;

	//vector<int> a;

	//RecursiveAcitvitySelector(s, f, 0, n, a);
	//AcitvitySelctor(s, f, n, a);

	//for (int item : a)
	//	cout << "act" << item << " ";
	//cout << endl;

	//////////////////////////////////////////////////////////////////////////
	// test dynamic programming algorithm

	vector<int> s2 = { 0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	vector<int> f2 = { 0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };
	int n = 11;
	//增加结束活动 a_n+1，起始时间和结束时间均为 INT_MAX
	s2.push_back(INT_MAX);
	f2.push_back(INT_MAX);

	int ** c = nullptr;
	int ** memo = nullptr;
	vector<int> A;

	ActivitySelectorDP(s2, f2, n, c, memo);
	//ActivitySelectorDp_2(s2, f2, n, c, memo);
	GetA(memo, 0, n + 1, A);

	for (int item : A)
		cout << "act" << item << " ";
	cout << endl;
}