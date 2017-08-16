#include "Heap.h"

// TODO...
// freq_array[1..n]
int Huffman(int freq_array[], int n)
{
	MinHeap<int> Q(freq_array, n);
	for (int i = 1; i < n; i++)
	{
		int min_1 = Q.HeapExtractMin();
		int min_2 = Q.HeapExtractMin();
		int new_freq = min_1 + min_2;
		Q.HeapInsert(new_freq);
	}
	return Q.HeapExtractMin();
}