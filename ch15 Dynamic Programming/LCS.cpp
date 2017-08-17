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

void LcsLengthMemoi(const vector<char> &X, const vector<char> &Y, char ** &b, char **&c)
{
	int m = X.size() - 1;
	int n = Y.size() - 1;

	c = new char *[m + 1];
	b = new char *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		c[i] = new char[n + 1];
		b[i] = new char[n + 1];
	}

	for(int i = 0; i < m + 1; i++)
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

int LcsLengthMemoiAux(const vector<char> &X, const vector<char> &Y, int i, int j, char** &b, char **&c)
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

void LcsTest()
{
#if 1
	// test LcsLengthMemoi()
	vector<char> X = { ' ', '1', '0', '0', '1', '0', '1', '0', '1' };
	vector<char> Y = { ' ', '0', '1', '0', '1', '1', '0', '1', '1', '0' };

	char **c = nullptr;
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