/*
 *  算法导论 练习 16.1-4 
 *  假定有一组活动，我们需要将它们安排到一些教室，任意活动都可以在任意教室进行。我们希望使用最少的教室完成所有活动。
 *  设计一个高效的贪心算法求每个活动应该在哪个教室进行。
 *  参考 http://blog.csdn.net/mishifangxiangdefeng/article/details/7747779
 **/

#include <algorithm>
#include <vector>
#include "Heap.h"

using std::sort;
using std::vector;

#define  N 11

// 存储每个活动的信息 A[1..N] 为有效信息
struct activity{
	int room_id;
	int start;
	int end;
}A[N+1];

// 用于对活动排序，这里按照活动的 start 顺序从小到大排序
bool cmp(const activity &lhs, const activity &rhs)
{
	return lhs.start < rhs.start;
}

void Greedy()
{
	// 按照活动的 start 顺序对活动进行排序
	sort(A + 1, A + N, cmp);

	// 小顶堆，用于存放已经使用的教室，按照教室中所有活动的 end 顺序
	MinHeap<int> min_heap;

	int room_id_count = 0;

	// 从第1个活动开始，逐个查找教室
	for (int i = 1; i <= N; i++)
	{
		// 如果还没有分配教室，先分配一个给活动A[i]，并设置 room_id
		if (min_heap.heap_size == 0)
		{
			min_heap.HeapInsert(A[i].end, ++room_id_count);
			A[i].room_id = room_id_count;
			continue;
		}

		// 如果当前活动的 start 晚于 堆顶教室的活动 end，则把活动安排在堆顶的那个教室
		if (A[i].start >= min_heap.HeapMinimum())
		{
			int temp_room_id = min_heap.HeapMinimumInfo();

			// 删除堆顶元素
			min_heap.HeapExtractMin();
			// 插入 temp_room_id 号房间的新信息
			min_heap.HeapInsert(A[i].end, temp_room_id);

			A[i].room_id= temp_room_id;
		}
		// 如果当前活动的start 早于 堆顶教室的活动 end，则申请一个新教室用来进行活动
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
请按任意键继续. . .

*/