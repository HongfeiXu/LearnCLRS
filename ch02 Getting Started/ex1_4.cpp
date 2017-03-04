/*
* 练习 2.1-4 考虑把两个n位二进制整数加起来的问题，这两个整数分别存储在两个n元数组A和B中。
* 这两个整数的和应该按二进制形式存储在一个(n+1)元数组C中。
*/

#include <iostream>

using std::cout;
using std::endl;

void printArray(const int *arr, int length);

int main()
{
    int A[5] = { 1,0,0,1,1 };
    int B[5] = { 1,1,1,0,1 };
    int C[6] = { 0,0,0,0,0,0 };

    for(int i = 0; i < 5; ++i)
    {
            C[i + 1] = (A[i] + B[i] + C[i]) / 2;
        C[i] = (A[i] + B[i] + C[i]) % 2;
    }

    printArray(A, 5);
    printArray(B, 5);
    printArray(C, 6);

    return 0;
}

void printArray(const int *arr, int length)
{
    for(int i = 0; i < length; ++i)
    {
        cout << *(arr + i);
    }
    cout << endl;
}

/*

10011
11101
000011
请按任意键继续. . .

*/