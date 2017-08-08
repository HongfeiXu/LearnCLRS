/***************************************************************************
*  @file       LCS.cpp
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.7 2017
*  @remark     Longest-common-subsequence problem
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "LCS.h"

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

void LcsTest()
{
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
}

/*

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