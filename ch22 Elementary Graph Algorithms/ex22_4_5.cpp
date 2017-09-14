#include "ex22_4_5.h"
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <list>

using namespace std;


void EX22_4_5_NAMESPACE::LinkGraph::TopologicalSort_v2()
{
	queue<int> Q;
	for (int i = 1; i <= vert_num; i++)
	{
		if (vert_indegree[i] == 0)
			Q.push(i);
	}
	while (!Q.empty())
	{
		int u = Q.front();
		cout << u << " ";
		Q.pop();
		// todo ... delete vertex u
		Edge *edge = V[u].head;
		while (edge != nullptr)
		{
			int v = edge->end;
			// todo ... delete edge (u,v)
			vert_indegree[v]--;
			if (vert_indegree[v] == 0)
				Q.push(v);
			edge = edge->next;
		}
	}
	cout << endl;
}

void EX22_4_5_NAMESPACE::LinkGraph::Print()
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

void EX22_4_5_NAMESPACE::LinkGraph::PrintInDegree()
{
	for (int i = 1; i <= vert_num; i++)
	{
		if (vert_deleted[i])
			continue;
		cout << "vert " << i << "'s indegree = " << vert_indegree[i] << endl;
	}
}

void EX22_4_5_NAMESPACE::Test()
{
#if 0
	vector<pair<int, int>> input = {
		make_pair(1,2),
		make_pair(1,4),
		make_pair(2,5),
		make_pair(3,6),
		make_pair(3,5),
		make_pair(4,2),
		make_pair(5,4),
		make_pair(6,6)
	};
	LinkGraph *LG = new LinkGraph(6); // LG 中有 3个环
	for (auto &item : input)
		LG->AddSingleEdge(item.first, item.second);
	cout << "LG-------------------------------\n";
	LG->Print();
	LG->PrintInDegree();
	LG->TopologicalSort_v2();
#endif

#if 1
	vector<pair<int, int>> input = {
		make_pair(1,2),
		make_pair(3,2),
		make_pair(2,4),
		make_pair(2,5),
		make_pair(5,4),
	};
	LinkGraph *LG = new LinkGraph(5);
	for (auto &item : input)
		LG->AddSingleEdge(item.first, item.second);
	cout << "LG-------------------------------\n";
	LG->Print();
	cout << "InDegree-------------------------\n";
	LG->PrintInDegree();
	cout << "Topological Sort Result----------\n";
	LG->TopologicalSort_v2();
#endif
}

/*

LG-------------------------------
1->2
2->4->5
3->2
4
5->4
InDegree-------------------------
vert 1's indegree = 0
vert 2's indegree = 2
vert 3's indegree = 0
vert 4's indegree = 2
vert 5's indegree = 1
Topological Sort Result----------
1 3 2 5 4
请按任意键继续. . .

*/

