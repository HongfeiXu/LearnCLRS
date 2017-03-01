#include <iostream>
#include <random>
#include <ctime>
using namespace std;

const int ARRAYSIZE = 20;

int Partition(int A[], int p, int r)
{
	cout << "Partition with " << A[r] << " : \n";
	int x = A[r];
	int i = p - 1;
	for(int j = p; j <= r - 1; j++)
	{
		if(A[j] <= x)
		{
			i = i + 1;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	int temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;

	for(int i = 0; i != ARRAYSIZE; i++)
		cout << A[i] << " ";
	cout << endl;

	return i + 1;
}

int RandomPartition(int A[], int p, int r)
{
	int i = rand() % (r - p + 1) + p;
	int temp = A[i];
	A[i] = A[r];
	A[r] = temp;

	return Partition(A, p, r);
}

int RandomizedSelect(int A[], int p, int r, int i)
{
	if(p == r)
		return A[p];
	int q = RandomPartition(A, p, r);
	int k = q - p + 1;
	if(i == k)
		return A[q];
	else if(i < k)
		return RandomizedSelect(A, p, q - 1, i);
	else
		return RandomizedSelect(A, q + 1, r, i - k);
}

int main()
{
	srand(time(0));
	int A[ARRAYSIZE];
	for(int i = 0; i != ARRAYSIZE; i++)
		A[i] = rand() % 100;

	for(int i = 0; i != ARRAYSIZE; i++)
		cout << A[i] << " ";
	cout << endl;

	int min5 = RandomizedSelect(A, 0, ARRAYSIZE-1, 5);
	cout << "min5 = " << min5 << endl;

	return 0;
}

/*

70 74 20 80 1 74 71 84 98 72 77 25 16 57 48 4 80 92 1 12
Partition with 1 :
1 1 20 80 70 74 71 84 98 72 77 25 16 57 48 4 80 92 12 74
Partition with 92 :
1 1 20 80 70 74 71 84 72 77 25 16 57 48 4 80 74 12 92 98
Partition with 16 :
1 1 12 4 16 74 71 84 72 77 25 20 57 48 80 80 74 70 92 98
min5 = 16
Press any key to continue . . .

*/