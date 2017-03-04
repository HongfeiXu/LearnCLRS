/*
* ��ϰ 2.1-4 ���ǰ�����nλ���������������������⣬�����������ֱ�洢������nԪ����A��B�С�
* �����������ĺ�Ӧ�ð���������ʽ�洢��һ��(n+1)Ԫ����C�С�
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
�밴���������. . .

*/