#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

// 同时找最小值和最大值
void findMinMax(const vector<int> &numbers, int &min, int &max)
{
	auto numbersSize = numbers.size();
	int minTemp, maxTemp;
	
	// 依照元素个数的奇偶进行分类讨论
	if(numbersSize % 2 == 0)
	{
		numbers[0] <= numbers[1] ? min = numbers[0], max = numbers[1] : min = numbers[1], max = numbers[0];
		for(int i = 2; i != numbersSize - 2; i += 2)
		{
			numbers[i] <= numbers[i + 1] ? minTemp = numbers[i], maxTemp = numbers[i + 1] : minTemp = numbers[i + 1], maxTemp = numbers[i];
			if(minTemp < min)
				min = minTemp;
			if(maxTemp > max)
				max = maxTemp;
		}
	}
	else
	{
		min = max = numbers[0];
		for(int i = 1; i != numbersSize - 2; i += 2)
		{
			numbers[i] < numbers[i + 1] ? minTemp = numbers[i], maxTemp = numbers[i + 1] : minTemp = numbers[i + 1], maxTemp = numbers[i];
			if(minTemp < min)
				min = minTemp;
			if(maxTemp > max)
				max = maxTemp;
		}
	}
}

int main()
{
	srand(time(0));

	// test 1
	vector<int> numbers(20);
	for(int i = 0; i != 20; ++i)
		numbers[i] = rand() % 100;

	int min, max;
	findMinMax(numbers, min, max);

	for(int i = 0; i != 20; i++)
		cout << numbers[i] << " ";
	cout << endl;
	cout << "Min = " << min << endl;
	cout << "Max = " << max << endl;

	// test 2
	vector<int> numbers_2(19);
	for(int i = 0; i != 19; ++i)
		numbers_2[i] = rand() % 100;

	findMinMax(numbers_2, min, max);

	for(int i = 0; i != 19; i++)
		cout << numbers_2[i] << " ";
	cout << endl;
	cout << "Min = " << min << endl;
	cout << "Max = " << max << endl;

	return 0;
}

/*

6 41 94 49 36 86 48 42 43 24 73 7 18 90 90 29 10 59 74 43
Min = 6
Max = 94
43 30 21 37 1 20 54 8 26 20 52 62 23 13 64 18 18 0 37
Min = 1
Max = 62
Press any key to continue . . .

*/