/***************************************************************************
*  @file       myUtility.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       4.19 2016
*  @remark     Implementations for algorithims from CLRS using C++ templates.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <cmath>
#include <vector>
#include <iostream>

//  RANDOMIZE-IN-PLACE(A)-----------------------------

int Random(int a, int b)
{
	return std::rand() % (b - a) + a + 1;
}

template<typename T>
void RandomizeInPlace(std::vector<T> &A)
{
	auto n = A.size();
	for (decltype(n) i = 0; i != n - 1; ++i)
	{
		int target = Random(i, n - 1);
		std::swap(A[i], A[target]);
	}
}

template <typename T>
void OutputVec(const std::vector<T> &A, std::ostream &os, char separator)
{
	for (auto item : A)
	{
		os << item << separator;
	}
	os << std::endl;
}


#endif // !MY_UTILITY_H
