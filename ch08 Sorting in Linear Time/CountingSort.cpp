/*

计数排序

输入：A[1..n]，A.length = n
输出：B[1..n]
临时：C[0..k]

*/

#include <iostream>
#include <memory>

using namespace std;

void countingSort(const int *A, int *B, const int n, const int k)
{
	unique_ptr<int[]> C(new int[k+1]);  // C[0..k] 位有效

	for(int i = 0; i <= k; i++)
		C[i] = 0;
	
	for(int j = 1; j <= n; j++)
		C[A[j]] += 1;
	
	for(int i = 1; i <= k; i++)
		C[i] = C[i] + C[i - 1];

	for(int j = n; j >= 1; j--)
	{
		B[C[A[j]]] = A[j];
		C[A[j]] -= 1;
	}

	C.release();
}

int main()
{
	const size_t len = 8;
	const int k = 5;

	int A[len + 1] = { -1,2,5,3,0,2,3,0,3 };  // A[1..len] 为有效
	int B[len + 1];
	B[0] = -1;  // B[1..len] 为有效

	countingSort(A, B, len, k);

	for(int i = 1; i <= len; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;

	for(int i = 1; i <= len; i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;

	return 0;
}


/*

2 5 3 0 2 3 0 3
0 0 2 2 3 3 3 5
Press any key to continue . . .

*/