/*
*
* 用几种不同的方法来查找最大子数组，规定函数的参数如下。FindMaximumSubarray_*(int A[], int low, int high, Result *presult)
* 其中A为待查数组，low 和 high 是其要被查找的那一段的下标范围。比如要查长度为5的数组 int A[5]。则 low = 0, high = 4。
* Result为新定义的一个结构体，用来存储查找的结果。
*
*/

#include <iostream>
#include <climits>		// INT_MIN

using namespace std;

// 用此结构体存储查找的结果，包括最大子数组的和，以及下标范围。
typedef struct{
	int maxSum;
	int leftPos;
	int rightPos;
}Result;

// 函数声明
void FindMaximumSubarray_Violence(int A[], int low, int high, Result &result);
void FindMaximumSubarray_Linear(int A[], int low, int high, Result &result);
void FindMaximumCrossingSubarray(int A[], int low, int mid, int high, Result &result);
void FindMaximumSubarray_DC(int A[], int low, int high, Result &result);

int main()
{
	int A[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	
	Result result;
	FindMaximumSubarray_Violence(A, 0, 15, result);
	printf("FindMaximumSubarray_Violence:\n");
	printf("The result is:\n\n");
	printf("leftPos: %d\n", result.leftPos);
	printf("rightPos: %d\n", result.rightPos);
	printf("maxSum: %d\n\n", result.maxSum);

	FindMaximumSubarray_Linear(A, 0, 15, result);
	printf("FindMaximumSubarray_Linear:\n");
	printf("The result is:\n\n");
	printf("leftPos: %d\n", result.leftPos);
	printf("rightPos: %d\n", result.rightPos);
	printf("maxSum: %d\n\n", result.maxSum);

	FindMaximumSubarray_DC(A, 0, 15, result);
	printf("FindMaximumSubarray_DC:\n");
	printf("The result is:\n\n");
	printf("leftPos: %d\n", result.leftPos);
	printf("rightPos: %d\n", result.rightPos);
	printf("maxSum: %d\n\n", result.maxSum);

	return 0;
}

// 法三：分治法求解
void FindMaximumCrossingSubarray(int A[], int low, int mid, int high, Result &result)
{
	Result middleLeft;
	middleLeft.leftPos = -1;
	middleLeft.rightPos = mid;
	middleLeft.maxSum = INT_MIN;
	int currentSum = 0;
	for(int i = mid; i >= low; --i)
	{
		currentSum += A[i];
		if(currentSum > middleLeft.maxSum)
		{
			middleLeft.maxSum = currentSum;
			middleLeft.leftPos = i;
		}
	}

	Result middleRight;
	middleRight.leftPos = mid + 1;
	middleRight.rightPos = -1;
	middleRight.maxSum = INT_MIN;
	currentSum = 0;
	for(int i = mid + 1; i <= high; ++i)
	{
		currentSum += A[i];
		if(currentSum > middleRight.maxSum)
		{
			middleRight.maxSum = currentSum;
			middleRight.rightPos = i;
		}
	}

	result.leftPos = middleLeft.leftPos;
	result.rightPos = middleRight.rightPos;
	result.maxSum = middleLeft.maxSum + middleRight.maxSum;
}

void FindMaximumSubarray_DC(int A[], int low, int high, Result &result)
{
	if(low == high)
	{
		result.leftPos = result.rightPos = low;
		result.maxSum = A[low];
	}
	else
	{
		int mid = (low + high) / 2;
		FindMaximumSubarray_DC(A, low, mid, result);			// 寻找左半最大子数组
		Result resultLeft = result;
		FindMaximumSubarray_DC(A, mid + 1, high, result);		// 寻找右半最大子数组
		Result resultRight = result;
		FindMaximumCrossingSubarray(A, low, mid, high, result);	// 寻找跨越重点最大子数组
		Result resultCrossing = result;
		if(resultLeft.maxSum > resultRight.maxSum && resultLeft.maxSum > resultCrossing.maxSum)
			result = resultLeft;
		else if(resultRight.maxSum > resultLeft.maxSum && resultRight.maxSum > resultCrossing.maxSum)
			result = resultRight;
		else
			result = resultCrossing;
	}
}


// 法二：线性时间求解
void FindMaximumSubarray_Linear(int A[], int low, int high, Result &result)
{
	result.leftPos = -1;
	result.rightPos = -1;
	result.maxSum = INT_MIN;
	int j = low;
	int currentSum = 0;
	for(int i = low; i != high; ++i)
	{
		currentSum += A[i];
		if(currentSum > result.maxSum)
		{
			result.maxSum = currentSum;
			result.leftPos = j;
			result.rightPos = i;
		}
		if(currentSum < 0)
		{
			currentSum = 0;
			j = i + 1;
		}
	}
}



// 法一：暴力求解法
void FindMaximumSubarray_Violence(int A[], int low, int high, Result &result)
{
	result.leftPos = -1;
	result.rightPos = -1;
	result.maxSum = INT_MIN;

	for(int i = low; i != high; ++i)
	{
		int currentSum = 0;
		for(int j = i; j != high; ++j)
		{
			currentSum += A[j];
			if(currentSum > result.maxSum)
			{
				result.maxSum = currentSum;
				result.leftPos = i;
				result.rightPos = j;
			}
		}
	}
}

/*

FindMaximumSubarray_Violence:
The result is:

leftPos: 7
rightPos: 10
maxSum: 43

FindMaximumSubarray_Linear:
The result is:

leftPos: 7
rightPos: 10
maxSum: 43

FindMaximumSubarray_DC:
The result is:

leftPos: 7
rightPos: 10
maxSum: 43

请按任意键继续. . .

*/

