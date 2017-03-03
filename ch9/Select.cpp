/*

*/
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

const int ARRAYSIZE = 19;
const int COLUMESIZE = 5;

inline void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int Partition(vector<int> &A, int p, int r, int pivot)
{
	auto pivotIter = find(A.begin() + p, A.begin() + r + 1, pivot);
	int pivotIndex = pivotIter - A.begin();
	Swap(A[pivotIndex], A[r]);
	
	int x = A[r];
	int i = p - 1;
	for(int j = p; j <= r - 1; j++)
	{
		if(A[j] <= x)
		{
			i = i + 1;
			Swap(A[i], A[j]);
		}
	}
	Swap(A[i + 1], A[r]);

	return i + 1;
}

void InsertionSort(vector<int> &numbers)
{
	for(int i = 1; i < numbers.size(); i++)
	{
		int key = numbers[i];
		int j = i - 1;
		while(j >= 0 && numbers[j] > key)
		{
			numbers[j + 1] = numbers[j];
			j--;
		}
		numbers[j+1] = key;
	}
}

int Median(vector<int> numbers)
{
	InsertionSort(numbers);
	return numbers[(numbers.size() - 1) / 2];
}

int Select(vector<int> &A, int p, int r, int i)
{
	if(p == r)
		return A[p];
	vector<vector<int>> groups;
	// todo:分组，寻找中位数的中位数。
	for(int i = 0; i != floor(static_cast<double>(r - p + 1) / static_cast<double>(COLUMESIZE)); i++)
	{
		vector<int> oneGroup;
		for(int j = 0; j != COLUMESIZE; j++)
		{
			oneGroup.push_back(A[i*COLUMESIZE + j + p]);
		}
		groups.push_back(oneGroup);
	}
	if((r - p + 1) % COLUMESIZE != 0)
	{
		vector<int> oneGroup;
		for(int i = floor(static_cast<double>(r - p + 1) / static_cast<double>(COLUMESIZE)) * COLUMESIZE + p; i <= r; i++)
		{
			oneGroup.push_back(A[i]);
		}
		groups.push_back(oneGroup);
	}
	vector<int> median;
	for(auto &oneGroup : groups)
	{
		median.push_back(Median(oneGroup));
	}

	cout << "median:\n";
	for(auto item : median)
		cout << item << " ";
	cout << endl;

	int pivot;
	pivot = Select(median, 0, median.size() - 1, ceil(static_cast<double>(median.size())) / static_cast<double>(2));  // 递归调用 Select 寻找中位数的中位数


	int q = Partition(A, p, r, pivot);
	
	cout << "after partition:\n";
	for(int i = p; i <= r; i++)
		cout << A[i] << " ";
	cout << endl;

	int k = q - p + 1;
	if(i == k)
		return A[q];
	else if(i < k)
		return Select(A, p, q - 1, i);
	else
		return Select(A, q + 1, r, i - k);
}


// test
int main()
{
	srand(time(0));
	vector<int> A = { 6, 40, 36, 26, 99, 16, 70, 67, 33, 14, 66, 65, 72, 89, 7, 63, 45, 48, 15 };

	for(int i = 0; i != ARRAYSIZE; i++)
		cout << A[i] << " ";
	cout << endl;

	int min5 = Select(A, 0, ARRAYSIZE-1, 5);
	cout << "min5 = " << min5 << endl;

	//min5 = RandomizedSelect(A, 0, ARRAYSIZE - 1, 5);
	//cout << "min5 = " << min5 << endl;

	return 0;
}

/*

6 40 36 26 99 16 70 67 33 14 66 65 72 89 7 63 45 48 15
median:
36 33 66 45
median:
36
after partition:
33 36 66 45
after partition:
6 15 26 16 33 14 7 36 99 40 66 65 72 89 70 63 45 48 67
median:
16 7
median:
7
after partition:
7 16
after partition:
6 7 26 16 33 14 15
median:
16
after partition:
15 14 16 26 33
min5 = 16
Press any key to continue . . .

*/