/*

基数排序：
	基于计数排序的基数排序，实现对相同位数的大写单词的排序

使用基数排序排列单词 COW DOG SEA RUG ROW MOB BOX TAB BAR EAR TAR DIG BIG TEA NOW FOX

需要将字母映射到 从 0 到 25 的数字，然后进行 countingSort。
然后由低位到高位，对每一组字母，转换为数字，调用 countingSort，并在函数中完成对单词的一次排序，共需要单词位数次调用。
注：每次调用 countingSort 需要使用上一次生成的结果。

*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// 对 words 中单词的某一位进行 countingSort
void countingSort(const int *A, int *B,  const int len, const int k, const vector<string> &words, vector<string> &result)
{
	unique_ptr<int[]> C(new int[k + 1]);  // C[0..k] 位有效

	for(int i = 0; i <= k; i++)
		C[i] = 0;

	for(int j = 0; j < len; j++)
		C[A[j]] += 1;

	for(int i = 1; i <= k; i++)
		C[i] = C[i] + C[i - 1];

	for(int j = len - 1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j];
		result[C[A[j]] - 1] = words[j];  // 将单词放到变换后的位置
		C[A[j]] -= 1;
	}

	C.release();
}

// 'A' --> 0  'B' --> 1  ...  'Z' --> 25
inline int mapChar2Num(char c)
{
	return static_cast<int>(c) - static_cast<int>('A');
}

void radixSort(const vector<string> &words, const int d, vector<string> &result)
{
	const int k = 25;  // 字母对应数字的范围 0 ~ 25
	const int len = words.size();  // 待排单词数量

	vector<string> temp(words.begin(), words.end());  // 保存 words 排序的中间结果
	for(int i = d - 1; i >= 0; --i)  // 从最低位到最高位
	{
		int *A = new int[len];

		// 将字符转化为对应的数字保存在数组 A 中
		int c = 0;
		for(vector<string>::iterator iterBegin = temp.begin(); c != temp.size(); c++)
			A[c] = mapChar2Num((*(iterBegin + c))[i]);

		int *B = new int[len];  // 用数组 B 保留运算结果

		countingSort(A, B, len, k, temp, result);
		temp.assign(result.begin(), result.end());

		//for(auto &item : result)
		//	cout << item << " ";
		//cout << endl;

		delete[] A;  // 释放内存
		delete[] B;
	}
}

int main()
{
	vector<string> words { "COW", "DOG", "SEA", "RUG", "ROW", "MOB", "BOX", "TAB", "DIG", "BIG", "TEA", "NOW", "FOX" };

	cout << "Input:\n";
	for(auto &item : words)
		cout << item << " ";
	cout << endl;


	const int d = 3;  // 3 位元素 对应每个字符串中字符下标 0 1 2（位字母的最低位）

	vector<string> result(words.size());
	
	radixSort(words, d, result);

	cout << "Output:\n";
	for(auto &item : result)
		cout << item << " ";
	cout << endl;

	return 0;
}

/*

Input:
COW DOG SEA RUG ROW MOB BOX TAB DIG BIG TEA NOW FOX
Output:
SEA TEA MOB TAB DOG RUG DIG BIG COW ROW NOW BOX FOX
TAB SEA TEA DIG BIG MOB DOG COW ROW NOW BOX FOX RUG
BIG BOX COW DIG DOG FOX MOB NOW ROW RUG SEA TAB TEA
Press any key to continue . . .

*/