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
* A.heap_size �洢���е���ЧԪ��
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
	*  MaxHeapify ����ά���������ʡ�
	*  ����Ϊ���� A ��һ���±� i��
	*  �ٶ����ڵ�Ϊ left[i] �� right[i] �Ķ��������� ���� ��
	*  ����ʱ A[i] �п���С���亢�ӣ�Υ�������ѵ����ʣ�
	*  ͨ���� A[i] �����������½����ǵ����±� i Ϊ���ڵ������������ѭ���ѵ����ʡ�
	*
	**/
	void MaxHeapify(int i)
	{
		int left = Left(i);
		int right = Right(i);
		int largest = 0;

		// �� A[i] A[Left[i]] �� A[Right[i]] ��ѡ������
		if (left <= heap_size && A[left] > A[i])
			largest = left;
		else
			largest = i;
		if (right <= heap_size && A[right] > A[largest])
			largest = right;
		// ��� A[i] �������Ľڵ㣬���� A[i] �� A[largest] ��ֵ���ݹ鴦���� A[largest] Ϊ��������
		if (largest != i)
		{
			swap(A[i], A[largest]);
			MaxHeapify(largest);
		}
	}

	/*
	*  BuildMaxHeap �����Ե����ϵķ������� MaxHeapify �� A[1..heap_size] ��Ϊ����
	**/
	void BuildMaxHeap()
	{
		// A[heap_size/2 + 1..heap_size] ��ΪҶ�ڵ㣬����Ϊֻ����һ��Ԫ�صĶѣ�
		// ��ֻ�������ڵ����һ�� MaxHeapify
		for (int i = heap_size / 2; i >= 1; i--)
			MaxHeapify(i);
	}

	/*
	*  �������ѵ�����
	*  �������� A[] �ڵ�����Ϊ��С��������ģ�heap_size ��Ϊ�� 2
	**/
	void HeapSort()
	{
		BuildMaxHeap();
		for (int i = heap_size; i >= 2; i--)
		{
			swap(A[i], A[1]);
			heap_size--;    // ȥ����ǰ�ѵ����һ���ڵ�
			MaxHeapify(1);  // ���µĶ�ά���ѵ�����
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// max priority queue ʵ�֣����� Heap

	// ʵ�� MAXIMUM(S) ����
	T HeapMaximum()
	{
		return A[1];
	}

	// ʵ�� EXTRACT-MAX(S) ����
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

	// ʵ�� INCREASE-Key(S, x, k) ����
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

	// ʵ�� INSERT(S, x) ����
	void HeapInsert(T key)
	{
		heap_size++;
		A[heap_size] = -10000000; // ����һ���ؼ���Ϊ -10000000��Ҷ�ڵ�����չ����
		HeapIncreaseKey(heap_size, key);  // ���� HeapIncreaseKey Ϊ�½ڵ����ùؼ��֣�ͬʱ�������ѵ�����
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
			heap_size--;    // ȥ����ǰ�ѵ����һ���ڵ�
			MinHeapify(1);  // ���µĶ�ά���ѵ�����
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// min priority queue ʵ�֣����� Heap

	// ʵ�� MINIMUM(S) ����
	T HeapMinimum()
	{
		return A[1];
	}

	// ʵ�� EXTRACT-MIN(S) ����
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

	// ʵ�� DECREASE-Key(S, x, k) ����
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

	// ʵ�� INSERT(S, x) ����
	void HeapInsert(T key)
	{
		heap_size++;
		A[heap_size] = 1000000000; // ����һ���ؼ���Ϊ 1000000000 ��Ҷ�ڵ�����չ��С��
		HeapDecreaseKey(heap_size, key);  // ���� HeapIncreaseKey Ϊ�½ڵ����ùؼ��֣�ͬʱ�������ѵ�����
	}
};

void HeapTest()
{
	int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 }; // A[1..10] Ϊ��Ч����
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
