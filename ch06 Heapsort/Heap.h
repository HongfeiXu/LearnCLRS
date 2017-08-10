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
class MaxHeap{
public:
	T A[MAXLENGTH];
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
	MaxHeap()
	{
		heap_size = 0;
	}

	MaxHeap(T A_[], int heap_size_)
	{
		heap_size = heap_size_;
		for (int i = 1; i <= heap_size; i++)
			A[i] = A_[i];

	}

	/*
	*  MaxHeapify 用于维护最大堆性质。
	*  输入为数组 A 和一个下标 i。
	*  假定根节点为 left[i] 和 right[i] 的二叉树都是 最大堆 ，
	*  但这时 A[i] 有可能小于其孩子，违背了最大堆的性质，
	*  通过让 A[i] 在最大堆中逐级下降，是的以下标 i 为根节点的子树重新遵循最大堆的性质。
	*
	**/
	void MaxHeapify(int i)
	{
		int left = Left(i);
		int right = Right(i);
		int largest = 0;

		// 从 A[i] A[Left[i]] 和 A[Right[i]] 中选择最大的
		if (left <= heap_size && A[left] > A[i])
			largest = left;
		else
			largest = i;
		if (right <= heap_size && A[right] > A[largest])
			largest = right;
		// 如果 A[i] 不是最大的节点，交换 A[i] 和 A[largest] 的值，递归处理以 A[largest] 为根的子树
		if (largest != i)
		{
			swap(A[i], A[largest]);
			MaxHeapify(largest);
		}
	}

	/*
	*  BuildMaxHeap 采用自底向上的方法利用 MaxHeapify 把 A[1..heap_size] 变为最大堆
	**/
	void BuildMaxHeap()
	{
		// A[heap_size/2 + 1..heap_size] 均为叶节点，可视为只包含一个元素的堆，
		// 故只对其它节点调用一次 MaxHeapify
		for (int i = heap_size / 2; i >= 1; i--)
			MaxHeapify(i);
	}

	/*
	*  基于最大堆的排序
	*  最终数组 A[] 内的数据为从小到大排序的，heap_size 变为了 2
	**/
	void HeapSort()
	{
		BuildMaxHeap();
		for (int i = heap_size; i >= 2; i--)
		{
			swap(A[i], A[1]);
			heap_size--;    // 去掉当前堆的最后一个节点
			MaxHeapify(1);  // 对新的堆维护堆的性质
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// max priority queue 实现，基于 Heap

	// 实现 MAXIMUM(S) 操作
	T HeapMaximum()
	{
		return A[1];
	}

	// 实现 EXTRACT-MAX(S) 操作
	T HeapExtractMax()
	{
		if (heap_size < 1)
		{
			cerr << "heap underflow" << endl;
			exit(EXIT_FAILURE);
		}
		int max = A[1];
		A[1] = A[heap_size];
		heap_size--;
		MaxHeapify(1);

		return max;
	}

	// 实现 INCREASE-Key(S, x, k) 操作
	void HeapIncreaseKey(int i, T key)
	{
		if (key < A[i])
		{
			cerr << "new key is smaller than current key" << endl;
			exit(EXIT_FAILURE);
		}
		A[i] = key;
		while (i > 1 && A[i] > A[Parent(i)])
		{
			swap(A[i], A[Parent(i)]);
			i = Parent(i);
		}
	}

	// 实现 INSERT(S, x) 操作
	void HeapInsert(T key)
	{
		heap_size++;
		A[heap_size] = -10000000; // 增加一个关键字为 -10000000的叶节点来扩展最大堆
		HeapIncreaseKey(heap_size, key);  // 调用 HeapIncreaseKey 为新节点设置关键字，同时保存最大堆的性质
	}
};

template<typename T>
class MinHeap{
public:
	T A[MAXLENGTH];
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
};

void HeapTest()
{
	int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 }; // A[1..10] 为有效内容
	int n = 10;
	
	//////////////////////////////////////////////////////////////////////////
	// test MaxHeap

	MaxHeap<int> max_heap(A, 10);
	max_heap.BuildMaxHeap();

	cout << "max_heap.heap_size = " << max_heap.heap_size << endl;
	cout << "max heap:" << endl;
	for (int i = 1; i <= max_heap.heap_size; i++)
	{
		cout << max_heap.A[i] << " ";
	}
	cout << endl;

#if 0
	// test max priority queue
	cout << "HeapMaximum:" << max_heap.HeapMaximum() << endl;
	cout << "ExtractMax:" << max_heap.HeapExtractMax() << endl;
	cout << "After ExtractMax:" << endl;
	for (int i = 1; i <= max_heap.heap_size; i++)
	{
		cout << max_heap.A[i] << " ";
	}
	cout << endl;

	max_heap.HeapInsert(5);
	cout << "After HeapInsert(5):" << endl;
	for (int i = 1; i <= max_heap.heap_size; i++)
	{
		cout << max_heap.A[i] << " ";
	}
	cout << endl;

	max_heap.HeapIncreaseKey(max_heap.heap_size, 11);
	cout << "After HeapIncreaseKey():" << endl;
	for (int i = 1; i <= max_heap.heap_size; i++)
	{
		cout << max_heap.A[i] << " ";
	}
	cout << endl;
#endif

#if 0
	// test HeapSort
	max_heap.HeapSort();
	cout << "after sort" << endl;
	for (int i = 1; i <= 10; i++)
	{
		cout << max_heap.A[i] << " ";
	}
	cout << endl;
#endif

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
