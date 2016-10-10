/*
* 练习 2.2-2 选择排序
*/

#include <iostream>

using namespace std;

#define swap(a, b) do{auto temp = a; a = b; b =temp;} while(0)

// 函数声明
void selectionSort(int A[], int length);

int main()
{
    int A[] = { 9, 2, 7, 3, 10, -2 };
    int length = 6;

    selectionSort(A, length);

    for(auto item : A)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}

void selectionSort(int A[], int length)
{
    for(int i = 0; i < length - 1; ++i)
    {
        int min = i;
        for(int j = i + 1; j < length; ++j)
        {
            if(A[min] > A[j])
                min = j;
        }
        if(min != i)
            swap(A[min], A[i]);
    }
}

/*
-2 2 3 7 9 10
请按任意键继续. . .
*/