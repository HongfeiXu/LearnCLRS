#include "ex22_4_3.h"
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <list>

using namespace std;

bool EX22_4_3_NAMESPACE::LinkGraph::DoseUndirectedGraphHasLoop()
{
	queue<int> vert_queue;  // 保存度为 1 的顶点
	for (int i = 1; i <= vert_num; i++)
	{
		// 若该结点已经被删除
		if(vert_deleted[i])
			continue;
		if (vert_degree[i] == 0)
		{
			DeleteVertex(i);
		}
		else if (vert_degree[i] == 1)
			vert_queue.push(i);
	}
	while (!vert_queue.empty())
	{
		int v = vert_queue.front();
		vert_queue.pop();
		DeleteVertex(v);
		for (int i = 1; i <= vert_num; i++)
		{
			// 若该结点已经被删除
			if (vert_deleted[i])
				continue;
			if (vert_degree[i] == 0)
				DeleteVertex(i);
			else if (vert_degree[i] == 1)
				vert_queue.push(i);
		}
	}
	for (int i = 1; i <= vert_num; i++)
	{
		if (!vert_deleted[i])
			return true;
	}
	return false;
}

void EX22_4_3_NAMESPACE::LinkGraph::Print()
{
	for (int i = 1; i <= vert_num; i++)
	{
		if (vert_deleted[i])  // 如果该结点i已被删除，则跳过此结点
			continue;
		cout << i;
		Edge *temp_edge = V[i].head;
		while (temp_edge != nullptr)
		{
			cout << "->" << temp_edge->end;
			temp_edge = temp_edge->next;
		}
		cout << endl;
	}
}

void EX22_4_3_NAMESPACE::LinkGraph::PrintDegree()
{
	for (int i = 1; i <= vert_num; i++)
	{
		if(vert_deleted[i])
			continue;
		cout << "vert " << i << "'s degree = " << vert_degree[i] << endl;
	}
}

void EX22_4_3_NAMESPACE::Test()
{
#if 1
	vector<pair<int, int>> input = {
		make_pair(1,2),
		make_pair(1,4),
		make_pair(3,5),
		make_pair(2,4),
	};
	LinkGraph *LG = new LinkGraph(5);
	for (auto &item : input)
		LG->AddDoubleEdge(item.first, item.second);
	cout << "LG-------------------------------\n";
	LG->Print();
	if (LG->DoseUndirectedGraphHasLoop())
		cout << "This undirected graph has loop!\n";
	else
		cout << "This undirected graph has no loop!\n";
	LG->DeleteDoubleEdge(2, 4);
	cout << "LG-------------------------------\n";
	LG->Print();
	if (LG->DoseUndirectedGraphHasLoop())
		cout << "This undirected graph has loop!\n";
	else
		cout << "This undirected graph has no loop!\n";
#endif
}

/*

LG-------------------------------
1->2->4
2->1->4
3->5
4->1->2
5->3
This undirected graph has loop!
LG-------------------------------
1->2->4
2->1
4->1
This undirected graph has no loop!
请按任意键继续. . .

*/

