/***************************************************************************
*  @file       myUtility.cpp
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       4.19 2017
*  @remark     Implementations for algorithims from CLRS using C++ templates.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include <cmath>
#include "myUtility.h"

int Random(int a, int b)
{
	return std::rand() % (b - a) + a + 1;
}