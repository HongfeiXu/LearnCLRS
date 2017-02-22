/*

��������
	���ڼ�������Ļ�������ʵ�ֶ���ͬλ���Ĵ�д���ʵ�����

ʹ�û����������е��� COW DOG SEA RUG ROW MOB BOX TAB BAR EAR TAR DIG BIG TEA NOW FOX

��Ҫ����ĸӳ�䵽 �� 0 �� 25 �����֣�Ȼ����� countingSort��
Ȼ���ɵ�λ����λ����ÿһ����ĸ��ת��Ϊ���֣����� countingSort�����ں�������ɶԵ��ʵ�һ�����򣬹���Ҫ����λ���ε��á�
ע��ÿ�ε��� countingSort ��Ҫʹ����һ�����ɵĽ����

*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// �� words �е��ʵ�ĳһλ���� countingSort
void countingSort(const int *A, int *B,  const int len, const int k, const vector<string> &words, vector<string> &result)
{
	unique_ptr<int[]> C(new int[k + 1]);  // C[0..k] λ��Ч

	for(int i = 0; i <= k; i++)
		C[i] = 0;

	for(int j = 0; j < len; j++)
		C[A[j]] += 1;

	for(int i = 1; i <= k; i++)
		C[i] = C[i] + C[i - 1];

	for(int j = len - 1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j];
		result[C[A[j]] - 1] = words[j];  // �����ʷŵ��任���λ��
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
	const int k = 25;  // ��ĸ��Ӧ���ֵķ�Χ 0 ~ 25
	const int len = words.size();  // ���ŵ�������

	vector<string> temp(words.begin(), words.end());  // ���� words ������м���
	for(int i = d - 1; i >= 0; --i)  // �����λ�����λ
	{
		int *A = new int[len];

		// ���ַ�ת��Ϊ��Ӧ�����ֱ��������� A ��
		int c = 0;
		for(vector<string>::iterator iterBegin = temp.begin(); c != temp.size(); c++)
			A[c] = mapChar2Num((*(iterBegin + c))[i]);

		int *B = new int[len];  // ������ B ����������

		countingSort(A, B, len, k, temp, result);
		temp.assign(result.begin(), result.end());

		//for(auto &item : result)
		//	cout << item << " ";
		//cout << endl;

		delete[] A;  // �ͷ��ڴ�
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


	const int d = 3;  // 3 λԪ�� ��Ӧÿ���ַ������ַ��±� 0 1 2��λ��ĸ�����λ��

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