/***************************************************************************
*  @file       OptimalBst.cpp
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.8 2017
*  @remark     optimal binary search tree
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "OptimalBst.h"
#include <climits>
#include <algorithm>
#include <iostream>
#include <vector>
#include "BSTree.h"
#include <string>

using std::min;
using std::cout;
using std::endl;
using std::vector;


float OptimalBstUgly(float p[], float q[], int n, float ** &e, float ** &w)
{
	e = new float*[n + 2];
	w = new float*[n + 2];
	for (int i = 0; i < n + 2; i++)
	{
		e[i] = new float[n + 2];
		w[i] = new float[n + 2];
	}
	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < n + 2; j++)
		{
			e[i][j] = FLT_MAX;
			w[i][j] = 0.0f;
		}
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			w[i][j] = w[i][j - 1] + p[j] + q[j];
		}
	}

	return OptimalBstAuxUgly(e, w, 1, n);
}

float OptimalBstAuxUgly(float ** &e, float ** &w, int i, int j)
{
	if (j == i - 1)
	{
		return e[i][j];
	}
	else if (i <= j)
	{
		for (int r = i; r <= j; r++)
		{
			e[i][j] = min(e[i][j], OptimalBstAuxUgly(e, w, i, r - 1) + OptimalBstAuxUgly(e, w, r + 1, j) + w[i][j]);
		}
		return e[i][j];
	}
	return -1.0f;
}

float OptimalBst(float p[], float q[], int n, float ** &e, float ** &w, int ** &root)
{
	e = new float*[n + 2];
	w = new float*[n + 2];
	for (int i = 0; i < n + 2; i++)
	{
		e[i] = new float[n + 2];
		w[i] = new float[n + 2];
	}
	root = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		root[i] = new int[n + 1];
	}

	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}

	for (int len = 1; len <= n; len++)
	{
		for (int i = 1; i <= n - len + 1; i++)
		{
			int j = i + len - 1;
			e[i][j] = FLT_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++)
			{
				float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
	return e[1][n];
}

void ConstructOptimalBst(int ** &root, int i, int j)
{
	int r = root[i][j];
	// 如果左子树是叶子
	if (r - 1 < i)
	{
		cout << "d" << r - 1 << " is the left child of k" << r << endl;
	}
	// 如果左子树不是叶子
	else
	{
		cout << "k" << root[i][r - 1] << " is the left child of k" << r << endl;
		// 对左子树递归调用 ConstructOptimalBst
		ConstructOptimalBst(root, i, r - 1);
	}
	// 如果右子树是叶子
	if (r + 1 > j)
	{
		cout << "d" << r << " is the right child of k" << r << endl;
	}
	// 如果右子树不是叶子
	else
	{
		// 对右子树递归调用 ConstructOptimalBst
		cout << "k" << root[r + 1][j] << " is the right child of k" << r << endl;
		ConstructOptimalBst(root, r + 1, j);
	}
}


void OptimalBstTest()
{
	float p[] = { 0.0f, 0.15f, 0.10f, 0.05f, 0.10f, 0.20f };
	float q[] = { 0.05f, 0.10f, 0.05f, 0.05f, 0.05f, 0.10f };
	
	//float p[] = { 0.0f, 0.04f, 0.06f, 0.08f, 0.02f, 0.10f, 0.12f, 0.14f };
	//float q[] = { 0.06f, 0.06f, 0.06f, 0.006f, 0.05f, 0.05f, 0.05f, 0.05f};

	int n = 5;
	float **e = nullptr;
	float **w = nullptr;
	int **root = nullptr;

//	cout << OptimalBstUgly(p, q, n, e, w) << endl;
	cout << "optimal expected search cost "<<OptimalBst(p, q, n, e, w, root) << endl;

	cout << "k" << root[1][n] << " is the root" << endl;
	ConstructOptimalBst(root, 1, n);

	for (int i = 0; i < n+2; i++)
	{
		delete[] e[i];
		delete[] w[i];
	}
	delete[] e;
	delete[] w;
	e = nullptr;
	w = nullptr;

	if (root != nullptr)
	{
		for (int i = 0; i < n + 1; i++)
		{
			delete[] root[i];
		}
		delete[] root;
		root = nullptr;
	}
}

/*

optimal expected search cost 2.75
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
请按任意键继续. . .

*/