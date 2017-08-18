/***************************************************************************
*  @file       LCS.cpp
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Longest-common-subsequence problem
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "LCS.h"
#include <climits>
#include <algorithm>

using std::max;
using std::min;
using std::sort;

void LcsLength(const vector<char> &X, const vector<char> &Y, char ** &b, int ** &c)
{
	int m = X.size() - 1;
	int n = Y.size() - 1;

	b = new char *[m + 1];
	c = new int *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		b[i] = new char[n + 1];
		c[i] = new int[n + 1];
	}

	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			b[i][j] = ' ';
		}
	}

	for (int i = 0; i < m + 1; i++)
		c[i][0] = 0;
	for (int j = 0; j < n + 1; j++)
		c[0][j] = 0;

	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (X[i] == Y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '|';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '-';
			}
		}
	}
}

void PrintLcs(char ** &b, const vector<char> &X, int X_len, int Y_len)
{
	if (X_len == 0 || Y_len == 0)
		return;
	if (b[X_len][Y_len] == '\\')
	{
		PrintLcs(b, X, X_len - 1, Y_len - 1);
		cout << X[X_len];
	}
	else if (b[X_len][Y_len] == '|')
	{
		PrintLcs(b, X, X_len - 1, Y_len);
	}
	else
	{
		PrintLcs(b, X, X_len, Y_len - 1);
	}
}

void LcsLength_v2(const vector<char>& X, const vector<char>& Y, int **& c)
{
	int m = X.size() - 1;
	int n = Y.size() - 1;

	c = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		c[i] = new int[n + 1];
	}
	for (int i = 0; i < m + 1; i++)
		c[i][0] = 0;
	for (int j = 0; j < n + 1; j++)
		c[0][j] = 0;

	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (X[i] == Y[j])
				c[i][j] = c[i - 1][j - 1] + 1;
			else if (c[i - 1][j] >= c[i][j - 1])
				c[i][j] = c[i - 1][j];
			else
				c[i][j] = c[i][j - 1];
		}
	}
}

void PrintLcs_v2(const vector<char> &X, int X_len, int Y_len, int **&c)
{
	if (X_len == 0 || Y_len == 0)
		return;
	// 根据计算反推出前一个数据，而不是通过查找获得
	if (c[X_len][Y_len] == c[X_len - 1][Y_len - 1] + 1)
	{
		PrintLcs_v2(X, X_len - 1, Y_len - 1, c);
		cout << X[X_len];
	}
	else if (c[X_len][Y_len] == c[X_len - 1][Y_len])
		PrintLcs_v2(X, X_len - 1, Y_len, c);
	else
		PrintLcs_v2(X, X_len, Y_len - 1, c);
}

void LcsLengthMemoi(const vector<char> &X, const vector<char> &Y, char ** &b, int **&c)
{
	int m = X.size() - 1;
	int n = Y.size() - 1;

	c = new int *[m + 1];
	b = new char *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		c[i] = new int[n + 1];
		b[i] = new char[n + 1];
	}

	for (int i = 0; i < m + 1; i++)
		for (int j = 0; j < n + 1; j++)
		{
			c[i][j] = -1;
			b[i][j] = ' ';
		}
	for (int i = 0; i < m + 1; i++)
	{
		c[i][0] = 0;
	}
	for (int j = 0; j < n + 1; j++)
	{
		c[0][j] = 0;
	}
	LcsLengthMemoiAux(X, Y, m, n, b, c);
}

int LcsLengthMemoiAux(const vector<char> &X, const vector<char> &Y, int i, int j, char** &b, int **&c)
{
	if (c[i][j] >= 0)
		return c[i][j];
	else
	{
		if (X[i] == Y[j])
		{
			c[i][j] = LcsLengthMemoiAux(X, Y, i - 1, j - 1, b, c) + 1;
			b[i][j] = '\\';
		}
		else
		{
			int temp_1 = LcsLengthMemoiAux(X, Y, i - 1, j, b, c);
			int temp_2 = LcsLengthMemoiAux(X, Y, i, j - 1, b, c);
			if (temp_1 >= temp_2)
			{
				c[i][j] = temp_1;
				b[i][j] = '-';
			}
			else
			{
				c[i][j] = temp_2;
				b[i][j] = '|';
			}
		}
		return c[i][j];
	}
}

void LcsLength_v3(const vector<char> &X, const vector<char> &Y)
{
	// When computing a particular row of the table, only the previous row is needed.
	// Only two rows need to be kept in memory at a time.
	int m = X.size() - 1;
	int n = Y.size() - 1;
	// c[][] 是 2*min(m, n) 的矩阵
	int **c = nullptr;
	c = new int*[2];
	int len;
	m < n ? len = m : len = n;
	c[0] = new int[len + 1];
	c[1] = new int[len + 1];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < len + 1; j++)
		{
			c[i][j] = 0;
		}
	}

	if (m <= n)
	{
		//类似于上文的循环，只是 j%2 代表当前行，(j-1)%2 代表上一行，其余内容相似
		for (int j = 1; j < n + 1; j++)
		{
			for (int i = 1; i < m + 1; i++)
			{
				if (Y[j] == X[i])
					c[j % 2][i] = c[(j - 1) % 2][i - 1] + 1;
				else
				{
					if (c[(j - 1) % 2][i] >= c[j % 2][i - 1])
						c[j % 2][i] = c[(j - 1) % 2][i];
					else
						c[j % 2][i] = c[j % 2][i - 1];
				}
			}
		}
		cout << c[n % 2][m] << endl;
	}
	else
	{
		for (int i = 1; i < m + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (X[i] == Y[j])
					c[i % 2][j] = c[(i - 1) % 2][j - 1] + 1;
				else
				{
					if (c[(i - 1) % 2][j] > c[i % 2][j - 1])
						c[i % 2][j] = c[(i - 1) % 2][j];
					else
						c[i % 2][j] = c[i % 2][j - 1];
				}
			}
		}
		cout << c[m % 2][n] << endl;
	}
}

void LcsLength_v4(const vector<char>& X, const vector<char>& Y)
{
	// Actually only one row need be kept in memory at a time.When an element of the current row
	// is computed, it should be stored in a temporary variable.After the next element is computed, the
	// previous element may be placed in the row.
	int m = X.size() - 1;
	int n = Y.size() - 1;
	int *c = nullptr;
	int len;
	m < n ? len = m : len = n;
	c = new int[len + 1];
	for (int i = 0; i < len + 1; i++)
	{
		c[i] = 0;
	}
	if (m >= n)
	{
		int i = 0;
		int j = 0;
		for (i = 1; i < m + 1; i++)
		{
			for (j = 1; j < n + 1; j++)
			{
				// 注：对比 c[1..m][1..n]理解，这里 c[1..j-1]均已更新为这一行，而 c[j] 未被更新，故还存储上一行的内容
				// 所以，为了更新 c[i][j] 所须得 c[i][j-1] 存储在 c[j-1] 中， c[i-1][j] 存储在 c[j] 中
				// c[i-1][j-1] 需要另外存储或计算得到
				if (X[i] == Y[j])
				{
					c[j] = min(c[j - 1], c[j]) + 1;  // need prove...
				}
				else
				{
					c[j] = max(c[j - 1], c[j]);
				}
			}
		}
		cout << c[n] << endl;
	}
	else
	{
		for (int j = 1; j < n + 1; j++)
		{
			for (int i = 1; i < m + 1; i++)
			{
				if (X[i] == Y[j])
				{
					c[i] = min(c[i - 1], c[i]) + 1;
				}
				else
				{
					c[i] = max(c[i - 1], c[i]);
				}
			}
		}
		cout << c[m] << endl;
	}
}

void LcsLength_v5(const vector<int> &X, const vector<int> &Y, char ** &b, int ** &c)
{
	int m = X.size() - 1;
	int n = Y.size() - 1;

	b = new char *[m + 1];
	c = new int *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		b[i] = new char[n + 1];
		c[i] = new int[n + 1];
	}

	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			b[i][j] = ' ';
		}
	}

	for (int i = 0; i < m + 1; i++)
		c[i][0] = 0;
	for (int j = 0; j < n + 1; j++)
		c[0][j] = 0;

	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (X[i] == Y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '|';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '-';
			}
		}
	}
}

void PrintLcs_v5(char ** &b, const vector<int> &X, int X_len, int Y_len)
{
	if (X_len == 0 || Y_len == 0)
		return;
	if (b[X_len][Y_len] == '\\')
	{
		PrintLcs_v5(b, X, X_len - 1, Y_len - 1);
		cout << X[X_len] << ' ';
	}
	else if (b[X_len][Y_len] == '|')
	{
		PrintLcs_v5(b, X, X_len - 1, Y_len);
	}
	else
	{
		PrintLcs_v5(b, X, X_len, Y_len - 1);
	}
}

void Lmis(const vector<int> &X)
{
	vector<int> X_sorted(X);
	sort(X_sorted.begin() + 1, X_sorted.end());  // 从下标1开始为有效元素

	char ** b;
	int ** c;
	LcsLength_v5(X, X_sorted, b, c);
	PrintLcs_v5(b, X, X.size() - 1, X.size() - 1);
	cout << endl;
}

void LcsTest()
{
#if 1
	// test Lmis()
	vector<int> X { 0,3,7,4,2,5,1,8,9,10 };  // X[1..X.size()-1] 为有效元素
	Lmis(X);

#endif

#if 0
	// test LcsLength_v4()
	vector<char> X = { ' ', '1', '0', '0', '1', '0', '1', '0', '1' };
	vector<char> Y = { ' ', '0', '1', '0', '1', '1', '0', '1', '1', '0' };

	LcsLength_v4(X, Y);
#endif

#if 0
	// test LcsLength_v3()
	vector<char> X = { ' ', '1', '0', '0', '1', '0', '1', '0', '1' };
	vector<char> Y = { ' ', '0', '1', '0', '1', '1', '0', '1', '1', '0' };

	LcsLength_v3(X, Y);
#endif

#if 0
	// test LcsLength_v2() PrintLcs_v2()
	vector<char> X = { ' ', '1', '0', '0', '1', '0', '1', '0', '1' };
	vector<char> Y = { ' ', '0', '1', '0', '1', '1', '0', '1', '1', '0' };

	int **c = nullptr;
	LcsLength_v2(X, Y, c);
	for (unsigned i = 1; i < X.size(); i++)
	{
		for (unsigned j = 1; j < Y.size(); j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}

	PrintLcs_v2(X, X.size() - 1, Y.size() - 1, c);
	cout << endl;
#endif

#if 0
	// test LcsLengthMemoi()
	vector<char> X = { ' ', '1', '0', '0', '1', '0', '1', '0', '1' };
	vector<char> Y = { ' ', '0', '1', '0', '1', '1', '0', '1', '1', '0' };

	int **c = nullptr;
	char **b = nullptr;

	LcsLengthMemoi(X, Y, b, c);
	for (unsigned i = 1; i < X.size(); i++)
	{
		for (unsigned j = 1; j < Y.size(); j++)
		{
			cout << b[i][j];
		}
		cout << endl;
	}
	PrintLcs(b, X, X.size() - 1, Y.size() - 1);
	cout << endl;
#endif

#if 0
	// test LcsLength()
	vector<char> X = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	vector<char> Y = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };

	char ** b = nullptr;
	int ** c = nullptr;

	LcsLength(X, Y, b, c);
	for (unsigned i = 1; i < X.size(); i++)
	{
		for (unsigned j = 1; j < Y.size(); j++)
		{
			cout << b[i][j];
		}
		cout << endl;
	}
	PrintLcs(b, X, X.size() - 1, Y.size() - 1);
	cout << endl;
#endif
}
/*
// test Lmis()

3 4 5 8 9 10
请按任意键继续. . .

*/

/*
// test LcsLength_v2() PrintLcs_v2()

0 1 1 1 1 1 1 1 1
1 1 2 2 2 2 2 2 2
1 1 2 2 2 3 3 3 3
1 2 2 3 3 3 4 4 4
1 2 3 3 3 4 4 4 5
1 2 3 4 4 4 5 5 5
1 2 3 4 4 5 5 5 6
1 2 3 4 5 5 6 6 6
101011
请按任意键继续. . .

*/

/*
// test LcsLengthMemoi()

 \ \\
\-\||
\ \- \
 \ \\ \
  \- \-
	\ \\
	 \- \
	   \-
010101
请按任意键继续. . .

*/

/*
// test LcsLength()

|||\-\
\--|\-
||\-||
\|||\-
|\||||
|||\|\
\|||\|
BCBA
请按任意键继续. . .

*/