/*

练习 8.2-4 设计一个算法，它能够对于任意给定的介于0到k之间的n个整数先进行预处理，在BigO(1)时间内回答输入的n个数中有多少个落在区间[a,b]内。
你所设计的算法的预处理时间为Theta(n+k)。

使用计数排序中构造数组C的思路。

*/

#include <iostream>

using namespace std;


int main()
{
	const int k = 6;
	const int n = 10;
	const int a = 2, b = 4;

	int A[n + 1] = { -1,6,0,2,4,5,3,1,2,3,6 };
	int C[k + 1];
	for(int i = 0; i <= k; i++)
		C[i] = 0;
	for(int i = 1; i <= n; i++)
		C[A[i]]++;  // C[i] 保存 A[1..n] 中值等于 i 的元素个数
	for(int i = 1; i <= k; i++)
		C[i] += C[i - 1];  // C[i] 保存 A[1..n] 中值小于等于 i 的元素个数

	if(a == 0)  // 如果起始元素范围为 0，则 C[b] 即为所求
		cout << C[b] << endl;
	else
		cout << C[b] - C[a - 1] << endl;
	
	return 0;
}


/*

5
Press any key to continue . . .

*/