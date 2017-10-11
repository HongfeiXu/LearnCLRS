/***************************************************************************
*  @file       MatrixChainOrder.cpp
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Matrix Chain multiplication
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "MatrixChainOrder.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;


void MatrixChainOrder(const vector<int> &p, int ** &m, int ** &s)
{
	int n = p.size() - 1;
	m = new int *[n + 1];  // array2D m[1..n,1..n] store the m[i,j] costs
	s = new int *[n + 1];  // array2D s[1..n-1,2..n] records which index of k achieved the optimal cost in commputing m[i,j]

	for (int i = 0; i < n + 1; i++)
	{
		m[i] = new int[n + 1];
		s[i] = new int[n + 1];
	}
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;

	for (int len = 2; len <= n; len++)  // len is chain length
	{
		for (int i = 1; i <= n - len + 1; i++)
		{
			int j = i + len - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

int MemorizedMatrixChainOrder(const vector<int> &p, int ** &m, int ** &s)
{
	int n = p.size() - 1;
	m = new int *[n + 1];
	s = new int *[n + 1];

	for (int i = 0; i < n + 1; i++)
	{
		m[i] = new int[n + 1];
		s[i] = new int[n + 1];
	}
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = i; j < n + 1; j++)
		{
			m[i][j] = INT_MAX;
		}
	}
	return LookUpChain(p, 1, n, m, s);
}

int LookUpChain(const vector<int> &p, int i, int j, int ** &m, int ** &s)
{
	if (m[i][j] < INT_MAX)
		return m[i][j];
	if (i == j)
		m[i][j] = 0;
	else
	{
		for (int k = i; k < j; k++)
		{
			int q = LookUpChain(p, i, k, m, s) + LookUpChain(p, k + 1, j, m, s) + p[i - 1] * p[k] * p[j];
			if (q < m[i][j])
			{
				m[i][j] = q;
				s[i][j] = k;
			}
		}
	}
	return m[i][j];
}

void PrintOptimalParens(int ** s, int i, int j)
{
	if (i == j)
		cout << "A" << i;
	else
	{
		cout << "(";
		PrintOptimalParens(s, i, s[i][j]);
		PrintOptimalParens(s, s[i][j] + 1, j);
		cout << ")";
	}
}

template <typename T>
Matrix<T> MatrixChainMultiply(vector<Matrix<T>> &A, int ** &s, int i, int j)
{
	if (i == j)
		return A[i];
	else
	{
		Matrix<T> B1 = MatrixChainMultiply(A, s, i, s[i][j]);
		Matrix<T> B2 = MatrixChainMultiply(A, s, s[i][j] + 1, j);
		return B1 * B2;
	}
}

void MartixChainOrderTest()
{
	vector<int> p{ 30, 35, 15, 5, 10, 20, 25 };
	int **m = nullptr;
	int **s = nullptr;

//	MatrixChainOrder(p, m, s);
	MemorizedMatrixChainOrder(p, m, s);  // Recusive top-down implementation with memoization

	cout << "m[][]:\n";
	for (unsigned i = 1; i <= p.size() - 1; i++)
	{
		for (unsigned j = i; j <= p.size() - 1; j++)
			cout << m[i][j] << " ";
		cout << "\n";
	}
	cout << "s[][]:\n";
	for (unsigned i = 1; i <= p.size() - 1; i++)
	{
		for (unsigned j = i + 1; j <= p.size() - 1; j++)
			cout << s[i][j] << " ";
		cout << "\n";
	}

	cout << "Optimal cost: m[1,n] = " << m[1][p.size() - 1] << endl;
	cout << "Optimal Parens: ";
	PrintOptimalParens(s, 1, p.size() - 1);
	cout << endl;

	for (unsigned i = 0; i < p.size(); i++)
	{
		delete[] m[i];
		delete[] s[i];
	}
	delete[] m;
	delete[] s;

	m = nullptr;
	s = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// test MatrixChainMultiply
	vector<Matrix<int>> A;
	Matrix<int> m1(2, 1, 1);
	Matrix<int> m2(1, 5, 2);
	Matrix<int> m3(5, 7, 3);
	A.push_back(Matrix<int>());  // 占位，使得有效矩阵从下标1开始
	A.push_back(m1);
	A.push_back(m2);
	A.push_back(m3);

	cout << "Input Matrix Chain:" << endl;
	for (unsigned i = 1; i < A.size(); i++)
	{
		A[i].printMat();
		if (i != A.size() - 1)
			cout << "-->\n";
	}

	vector<int> p2;
	for (unsigned i = 1; i < A.size(); i++)
	{
		p2.push_back(A[i].getRows());
	}
	p2.push_back(A.back().getCols());
	MatrixChainOrder(p2, m, s);
	
	cout << "m[][]:\n";
	for (unsigned i = 1; i <= p2.size() - 1; i++)
	{
		for (unsigned j = i; j <= p2.size() - 1; j++)
			cout << m[i][j] << " ";
		cout << "\n";
	}
	cout << "s[][]:\n";
	for (unsigned i = 1; i <= p2.size() - 1; i++)
	{
		for (unsigned j = i + 1; j <= p2.size() - 1; j++)
			cout << s[i][j] << " ";
		cout << "\n";
	}

	cout << "Optimal cost: m[1,n] = " << m[1][p2.size() - 1] << endl;
	cout << "Optimal Parens: ";
	PrintOptimalParens(s, 1, p2.size() - 1);
	cout << endl;

	Matrix<int> resutl(MatrixChainMultiply(A, s, 1, A.size()-1));
	cout << "Multiply Result:\n";
	resutl.printMat();

	for (unsigned i = 0; i < p2.size(); i++)
	{
		delete[] m[i];
		delete[] s[i];
	}
	delete[] m;
	delete[] s;
}

/*

0 15750 7875 9375 11875 15125
0 2625 4375 7125 10500
0 750 2500 5375
0 1000 3500
0 5000
0
s[][]:
1 1 3 3 3
2 3 3 3
3 3 3
4 5
5

Optimal cost: m[1,n] = 15125
Optimal Parens: ((A1(A2A3))((A4A5)A6))
Input Matrix Chain:
1
1
-->
2       2       2       2       2
-->
3       3       3       3       3       3       3
3       3       3       3       3       3       3
3       3       3       3       3       3       3
3       3       3       3       3       3       3
3       3       3       3       3       3       3
m[][]:
0 10 49
0 35
0
s[][]:
1 1
2

Optimal cost: m[1,n] = 49
Optimal Parens: (A1(A2A3))
Multiply Result:
30      30      30      30      30      30      30
30      30      30      30      30      30      30
请按任意键继续. . .

*/