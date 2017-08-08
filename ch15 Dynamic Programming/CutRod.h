/***************************************************************************
*  @file       CutRod.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       7.13 2017
*  @remark     Use dynamic programming to solve a simple problem in deciding where to cut steel rods.
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef CUTROD_H
#define CUTROD_H

#include <vector>
using std::vector;

// Recusive top-down implementation
// inefficient, it solves the same subproblems repeatedly
int CutRod(const int price[], int length);

// Recusive top-down implementation, with memoization added
int MemoizedCutRod(const int price[], int length);
int MemoizedCutRodAux(const int price[], int length,  vector<int> &memo);

// Bottom-Up version
int BottomUpCutRod(const int price[], int length);

// Extended version of Bottom-Up-Cut-Rod
// compute not only the maximum revenue but also the optimal size of the first piece to cut off
int ExtendedBottomUpCutRod(const int price[], int length, vector<int> &s);
// Print out the complete list of piece sizes in an optimal decomposition of a rod of length len
void PrintCutRodSolution(const int price[], int len, vector<int> &s);

// Test 3 CutRod methods
void CutRodTest();


#endif // !CUTROD_H
