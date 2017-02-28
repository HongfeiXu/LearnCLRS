/*
假设数据分布在 [0,100) 之间，每个桶内部用链表表示，在数据入桶的同时进行插入排序。
然后把各个桶的数据合并。

参考：https://zh.wikipedia.org/wiki/%E6%A1%B6%E6%8E%92%E5%BA%8F

*/

#include <vector>
#include <random>
#include <iostream>
#include <ctime>
using namespace std;
const int BUCKET_NUM = 10;

struct ListNode
{
	explicit ListNode(int i = 0) : mData(i), mNext(NULL) { }
	ListNode *mNext;
	int mData;
};

ListNode *insert(ListNode *head, int val)
{
	ListNode *newNode = new ListNode(val);
	ListNode dummyNode;
	dummyNode.mNext = head;
	ListNode *pre, *curr;
	pre = &dummyNode;
	curr = head;
	while(NULL != curr && curr->mData <= val)
	{
		pre = curr;
		curr = curr->mNext;
	}
	newNode->mNext = curr;
	pre->mNext = newNode;
	return dummyNode.mNext;
	
}

ListNode *Merge(ListNode *head1, ListNode *head2)
{
	ListNode dummyNode;
	ListNode *dummy = &dummyNode;

	while(NULL != head1 && NULL != head2)
	{
		if(head1->mData <= head2->mData)
		{
			dummy->mNext = head1;
			head1 = head1->mNext;
		}
		else
		{
			dummy->mNext = head2;
			head2 = head2->mNext;
		}
		dummy = dummy->mNext;
	}
	if(NULL != head1)
		dummy->mNext = head1;
	if(NULL != head2)
		dummy->mNext = head2;

	// 由于这里待合并的两个链表大小是确定的，即第一个链表中的元素全部小于第二个，
	// 所以不需要上面的那种复杂合并也可完成这里的任务
	//dummy->mNext = head1;
	//while(NULL != head1->mNext)
	//{
	//	head1 = head1->mNext;
	//}
	//head1->mNext = head2;

	return dummyNode.mNext;
}

void BucketSort(int n, int arr[])
{
	vector<ListNode*> buckets(BUCKET_NUM, (ListNode*) (0));
	for(int i = 0; i != n; ++i)
	{
		int index = arr[i] / BUCKET_NUM;
		ListNode *head = buckets.at(index);
		buckets.at(index) = insert(head, arr[i]);
	}
	ListNode *head = buckets.at(0);
	for(int i = 1; i != BUCKET_NUM; ++i)
	{
		head = Merge(head, buckets.at(i));
	}
	for(int i = 0; i != n; i++)
	{
		arr[i] = head->mData;
		head = head->mNext;
	}
}

int main()
{
	srand(time(0));  // use current time as seed for random generator
	int arr[20];
	for(int i = 0; i != 20; i++)
		arr[i] = rand() % 100;

	cout << "Original:\n";
	for(int i = 0; i != 20; i++)
		cout << arr[i] << " ";
	cout << endl;
	
	BucketSort(20, arr);
	
	cout << "After Bucket-Sort:\n";
	for(int i = 0; i != 20; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}

/*

Original:
19 23 14 64 74 66 77 68 0 41 71 19 40 7 71 41 90 89 95 23
After Bucket-Sort:
0 7 14 19 19 23 23 40 41 41 64 66 68 71 71 74 77 89 90 95
Press any key to continue . . .

*/