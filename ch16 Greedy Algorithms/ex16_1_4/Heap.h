#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <algorithm>
#include <climits>

using std::swap;
using std::cout;
using std::endl;
using std::cerr;

/*
* Heap:
* A[1..A.length]
* A.heap_size 存储堆中的有效元素
*
**/
#define MAXLENGTH 1001

template<typename T>
class MinHeap{
public:
	T A[MAXLENGTH];

	int Info[MAXLENGTH];  // 记录每个节点的卫星数据，这里是 classroom 的 id

	int heap_size = 0;

private:
	int Parent(int i)
	{
		return i / 2;
	}
	int Left(int i)
	{
		return 2 * i;
	}
	int Right(int i)
	{
		return 2 * i + 1;
	}

public:
	MinHeap()
	{
		heap_size = 0;
	}

	MinHeap(T A_[], int heap_size_)
	{
		heap_size = heap_size_;
		for (int i = 1; i <= heap_size; i++)
			A[i] = A_[i];

	}

	void MinHeapify(int i)
	{
		int left = Left(i);
		int right = Right(i);
		int smallest = 0;

		if (left <= heap_size && A[left] < A[i])
			smallest = left;
		else
			smallest = i;
		if (right <= heap_size && A[right] < A[smallest])
			smallest = right;
		if (smallest != i)
		{
			swap(A[i], A[smallest]);
			swap(Info[i], Info[smallest]);
			MinHeapify(smallest);
		}
	}

	void BuildMinHeap()
	{
		for (int i = heap_size / 2; i >= 1; i--)
			MinHeapify(i);
	}

	void HeapSort()
	{
		BuildMinHeap();
		for (int i = heap_size; i >= 2; i--)
		{
			swap(A[i], A[1]);
			swap(Info[i], Info[1]);
			heap_size--;    // 去掉当前堆的最后一个节点
			MinHeapify(1);  // 对新的堆维护堆的性质
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// min priority queue 实现，基于 Heap

	// 实现 MINIMUM(S) 操作
	T HeapMinimum()
	{
		return A[1];
	}

	// 读取堆顶元素的卫星数据
	int HeapMinimumInfo()
	{
		return Info[1];
	}

	// 实现 EXTRACT-MIN(S) 操作
	T HeapExtractMin()
	{
		if (heap_size < 1)
		{
			cerr << "heap underflow" << endl;
			exit(EXIT_FAILURE);
		}
		int min = A[1];
		A[1] = A[heap_size];
		Info[1] = Info[heap_size];
		heap_size--;
		MinHeapify(1);

		return min;
	}

	// 实现 DECREASE-Key(S, x, k) 操作
	void HeapDecreaseKey(int i, T key)
	{
		if (key > A[i])
		{
			cerr << "new key is bigger than current key" << endl;
			exit(EXIT_FAILURE);
		}
		A[i] = key;
		while (i > 1 && A[i] < A[Parent(i)])
		{
			swap(A[i], A[Parent(i)]);
			swap(Info[i], Info[Parent(i)]);
			i = Parent(i);
		}
	}

	// 实现 INSERT(S, x) 操作
	void HeapInsert(T key)
	{
		heap_size++;
		A[heap_size] = 1000000000; // 增加一个关键字为 1000000000 的叶节点来扩展最小堆
		HeapDecreaseKey(heap_size, key);  // 调用 HeapIncreaseKey 为新节点设置关键字，同时保存最大堆的性质
	}

	void HeapInsert(T key, int room_id)
	{
		heap_size++;
		A[heap_size] = 1000000000;        // 增加一个关键字为 1000000000 的叶节点来扩展最小堆
		Info[heap_size] = room_id;        // 添加卫星数据
		HeapDecreaseKey(heap_size, key);  // 调用 HeapIncreaseKey 为新节点设置关键字，同时保存最大堆的性质
	}
};

void HeapTest()
{
	int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 }; // A[1..10] 为有效内容
	int n = 10;

	//////////////////////////////////////////////////////////////////////////
	// test MinHeap

	MinHeap<int> min_heap(A, 10);
	min_heap.BuildMinHeap();
	cout << "min_heap.heap_size = " << min_heap.heap_size << endl;
	cout << "min heap:" << endl;
	for (int i = 1; i <= min_heap.heap_size; i++)
	{
		cout << min_heap.A[i] << " ";
	}
	cout << endl;

#if 1
	// test min priority queue
	cout << "HeapMinimum:" << min_heap.HeapMinimum() << endl;
	cout << "ExtractMin:" << min_heap.HeapExtractMin() << endl;
	cout << "After ExtractMax:" << endl;
	for (int i = 1; i <= min_heap.heap_size; i++)
	{
		cout << min_heap.A[i] << " ";
	}
	cout << endl;

	min_heap.HeapInsert(5);
	cout << "After HeapInsert(5):" << endl;
	for (int i = 1; i <= min_heap.heap_size; i++)
	{
		cout << min_heap.A[i] << " ";
	}
	cout << endl;

	min_heap.HeapDecreaseKey(min_heap.heap_size, 6);
	cout << "After HeapIncreaseKey():" << endl;
	for (int i = 1; i <= min_heap.heap_size; i++)
	{
		cout << min_heap.A[i] << " ";
	}
	cout << endl;
#endif

#if 0
	// test HeapSort
	min_heap.HeapSort();
	cout << "after sort" << endl;
	for (int i = 1; i <= 10; i++)
	{
		cout << min_heap.A[i] << " ";
	}
	cout << endl;
#endif
}

#endif // !HEAP_H
