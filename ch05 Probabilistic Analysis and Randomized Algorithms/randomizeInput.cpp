/*	
* 构造随机排列数组的方式：
* 1. PERMUTE-BY-SORTING(A) 
* 为数组的每个元素A[i]赋一个随机的优先级P[i]，然后依据优先级对数组A中的元素进行排序。
* 2. RANDOMIZE-IN-PLACE(A)
* 原址排列给定数组，在进行第 i 次迭代时，元素A[i]是从元素A[i]到A[n]中随机选取的。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>		// rand(), srand()
#include <ctime>		// time()

using namespace std;

// 类型定义
typedef struct
{
	int key;				// 存储待随机排序的数据
	unsigned priority;		// 存储对应数据的优先级（在方法1中使用）
}Elem;

// 函数声明
int Random(int a, int b);
void PermuteBySorting(vector<Elem> &A);
bool operator<(const Elem &a, const Elem &b);		
void PrintVector(const vector<Elem> &A);
void RandomizeInPlace(vector<Elem> &A);

int main()
{
	srand(unsigned(time(0)));		// seed before any calls to rand(), and the start of the program. -- cppreference

	cout << "----------------Test PermuteBySorting------------------\n\n";
	vector<Elem> A { {1,0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0} };
	PrintVector(A);
	PermuteBySorting(A);
	PrintVector(A);

	cout << "-----------------Test RandomizeInPlace-----------------\n\n";
	A = { { 1,0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 } };
	PrintVector(A);
	RandomizeInPlace(A);
	PrintVector(A);

	return 0;
}

// PERMUTE-BY-SORTING(A)-------------------------------
void PermuteBySorting(vector<Elem> &A)
{
	auto n = A.size();
	for(decltype(n) i = 0; i != n; ++i)		
	{
		A[i].priority = Random(1, n*n*n);
	}
	sort(A.begin(), A.end());
}

// 获取 a..b 之间的一个随机数（包括a和b）
int Random(int a, int b)
{
	return rand() % (b - a) + a + 1;
}

// 重载符号 “<”，使用结构体Elem中的元素 priority 排序
bool operator<(const Elem &a, const Elem &b)
{
	return a.priority < b.priority;
}

// 打印 vector<Elem> A 中的 key 元素
void PrintVector(const vector<Elem> &A)
{
	for(auto i : A)
	{
		cout <<"key: " <<i.key << "\t priority: " << i.priority << endl;
	}
	cout << endl;
}

//  RANDOMIZE-IN-PLACE(A)-----------------------------
void RandomizeInPlace(vector<Elem> &A)
{
	auto n = A.size();
	for(decltype(n) i = 0; i != n - 1; ++i)
	{
		int target = Random(i, n - 1);		
		auto temp = A[i].key;
		A[i].key = A[target].key;
		A[target].key = temp;
	}
}
/*
----------------Test PermuteBySorting------------------

key: 1   priority: 0
key: 2   priority: 0
key: 3   priority: 0
key: 4   priority: 0
key: 5   priority: 0
key: 6   priority: 0
key: 7   priority: 0

key: 5   priority: 51
key: 1   priority: 54
key: 3   priority: 176
key: 6   priority: 183
key: 4   priority: 244
key: 7   priority: 278
key: 2   priority: 322

-----------------Test RandomizeInPlace-----------------

key: 1   priority: 0
key: 2   priority: 0
key: 3   priority: 0
key: 4   priority: 0
key: 5   priority: 0
key: 6   priority: 0
key: 7   priority: 0

key: 4   priority: 0
key: 7   priority: 0
key: 5   priority: 0
key: 3   priority: 0
key: 2   priority: 0
key: 1   priority: 0
key: 6   priority: 0

请按任意键继续. . .

*/