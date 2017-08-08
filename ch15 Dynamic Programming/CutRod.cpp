/***************************************************************************
*  @file       CutRod.cpp
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       7.13 2017
*  @remark     Use dynamic programming to solve a simple problem in deciding where to cut steel rods.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include "CutRod.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <time.h>
#include <iomanip>
#include "myUtility.h" // OutputVec

using std::max;
using std::vector;

int CutRod(const int price[], int length)
{
	if (length == 0)
		return 0;
	int gains = INT_MIN;
	for (int i = 1; i <= length; i++)
		gains = max(gains, price[i] + CutRod(price, length - i));
	return gains;
}

int MemoizedCutRod(const int price[], int length)
{
	vector<int> memo(length+1, INT_MIN);
	
	return MemoizedCutRodAux(price, length, memo);
}

int MemoizedCutRodAux(const int price[], int length, vector<int> &memo)
{
	if (memo[length] >= 0)
		return memo[length];

	int gains = INT_MIN;
	if (length == 0)
		gains = 0;
	else
	{
		gains = INT_MIN;
		for (int i = 1; i <= length; i++)
		{
			gains = max(gains, price[i] + MemoizedCutRodAux(price, length - i, memo));
		}
	}
	memo[length] = gains;

	return gains;
}

int BottomUpCutRod(const int price[], int length)
{
	vector<int> memo(length + 1, INT_MIN);
	memo[0] = 0;

	for (int j = 1; j <= length; j++)
	{
		int gains = INT_MIN;
		for (int i = 1; i <= j; i++)
			gains = max(gains, price[i] + memo[j - i]);
		memo[j] = gains;
	}
	return memo[length];
}

int ExtendedBottomUpCutRod(const int price[], int length, vector<int> &s)
{
	vector<int> memo(length + 1, INT_MIN);
	memo[0] = 0;
	s.clear();
	s.assign(length + 1, INT_MIN);
	s[0] = 0;

	for (int j = 1; j <= length; j++)
	{
		int gains = INT_MIN;
		for (int i = 1; i <= j; i++)
		{
			if (gains < price[i] + memo[j - i])
			{
				gains = price[i] + memo[j - i];
				// s[j] hold the optimal size i of the first piece to cut off 
				// when solving a subproblem of size j
				s[j] = i;  
			}
		}
		memo[j] = gains;
	}
	return memo[length];
}

void PrintCutRodSolution(const int price[], int length, vector<int> &s)
{
	while (length > 0)
	{
		std::cout << s[length] << " ";
		length -= s[length];
	}
}

void CutRodTest()
{
	// 钢条长度为0,1,2,...,40时的价格
	const int price[41] = 
	{ 
		0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,
		31, 35, 38, 39, 40, 47, 47, 50, 54, 60,
		61, 65, 68, 69, 70, 77, 77, 80, 84, 90,
		91, 95, 98, 99, 100, 107, 107, 110, 114, 120
	};
	int length = 40;
	vector<int> s;

	clock_t beginTime = clock();

	//int gains = CutRod(price, length);
	//int gains = MemoizedCutRod(price, length);
	//int gains = BottomUpCutRod(price, length);
	int gains = ExtendedBottomUpCutRod(price, length, s);
	
	clock_t endTime = clock();
	float timeTaken = static_cast<float>(endTime - beginTime) / CLOCKS_PER_SEC;

	std::cout << "length = " << length << " gains = " << gains << std::endl;
	std::cout << "Time taken = " << timeTaken << " seconds." << std::endl;

	std::cout << "The optimal size of the first piece to cut off:" << std::endl;
	OutputVec(s, std::cout);
	std::cout << std::endl;
	
	std::cout << "The complete list of piece sizes in an optimal decomposition of a rod of length 17: \n";
	PrintCutRodSolution(price, 17, s);

	std::cout << std::endl;
}

/*

length = 40 gains = 120
Time taken = 0 seconds.
The optimal size of the first piece to cut off:
0 1 2 3 2 2 6 1 2 3 10 1 2 3 2 2 6 1 2 3 10 1 2 3 2 2 6 1 2 3 10 1 2 3 2 2 6 1 2 3 10
The complete list of piece sizes in an optimal decomposition of a rod of length 17:
1 6 10
请按任意键继续. . .

*/
