/*
 *  �㷨���� ��ϰ 16.1-4 
 *  �ٶ���һ����������Ҫ�����ǰ��ŵ�һЩ���ң�������������������ҽ��С�����ϣ��ʹ�����ٵĽ���������л��
 *  ���һ����Ч��̰���㷨��ÿ���Ӧ�����ĸ����ҽ��С�
 *  �ο� http://blog.csdn.net/mishifangxiangdefeng/article/details/7747779
 **/

#include <algorithm>
#include <vector>
#include "Heap.h"

using std::sort;
using std::vector;

#define  N 11

// �洢ÿ�������Ϣ A[1..N] Ϊ��Ч��Ϣ
struct activity{
	int room_id;
	int start;
	int end;
}A[N+1];

// ���ڶԻ�������ﰴ�ջ�� start ˳���С��������
bool cmp(const activity &lhs, const activity &rhs)
{
	return lhs.start < rhs.start;
}

void Greedy()
{
	// ���ջ�� start ˳��Ի��������
	sort(A + 1, A + N, cmp);

	// С���ѣ����ڴ���Ѿ�ʹ�õĽ��ң����ս��������л�� end ˳��
	MinHeap<int> min_heap;

	int room_id_count = 0;

	// �ӵ�1�����ʼ��������ҽ���
	for (int i = 1; i <= N; i++)
	{
		// �����û�з�����ң��ȷ���һ�����A[i]�������� room_id
		if (min_heap.heap_size == 0)
		{
			min_heap.HeapInsert(A[i].end, ++room_id_count);
			A[i].room_id = room_id_count;
			continue;
		}

		// �����ǰ��� start ���� �Ѷ����ҵĻ end����ѻ�����ڶѶ����Ǹ�����
		if (A[i].start >= min_heap.HeapMinimum())
		{
			int temp_room_id = min_heap.HeapMinimumInfo();

			// ɾ���Ѷ�Ԫ��
			min_heap.HeapExtractMin();
			// ���� temp_room_id �ŷ��������Ϣ
			min_heap.HeapInsert(A[i].end, temp_room_id);

			A[i].room_id= temp_room_id;
		}
		// �����ǰ���start ���� �Ѷ����ҵĻ end��������һ���½����������л
		else
		{
			min_heap.HeapInsert(A[i].end, ++room_id_count);
			A[i].room_id = room_id_count;
		}
	}
	cout << "we need "<< room_id_count << " rooms" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << "activity (" << A[i].start << "," << A[i].end << ")" << " in room: " << A[i].room_id << endl;
	}
}

int main()
{
	vector<int> start = { 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	vector<int> end= { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	for (int i = 1; i <= N; i++)
	{
		A[i].start = start[i-1];
		A[i].end = end[i-1];
	}

	Greedy();

	return 0;
}

/*

we need 5 rooms
activity (0,6) in room: 1
activity (1,4) in room: 2
activity (2,13) in room: 3
activity (3,5) in room: 4
activity (3,8) in room: 5
activity (5,7) in room: 2
activity (5,9) in room: 4
activity (6,10) in room: 1
activity (8,11) in room: 2
activity (8,12) in room: 5
activity (12,14) in room: 4
�밴���������. . .

*/