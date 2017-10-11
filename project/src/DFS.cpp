#include "DFS.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void DFS_NAMESPACE::LinkGraph::Print()
{
	for (int i = 1; i <= vert_num; i++)
	{
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

void DFS_NAMESPACE::LinkGraph::DFS()
{
	for (int i = 1; i <= vert_num; i++)
	{
		V[i].color = WHITE;
		V[i].parent = 0;
	}
	time = 0;  // 时间戳初始化
	topo_sort_result.clear();  // 清空
	for (int i = 1; i <= vert_num; i++)
	{
		if (V[i].color == WHITE)
			DfsVisit(i);
	}
}

void DFS_NAMESPACE::LinkGraph::DfsVisit(int u)
{
	time++;
	V[u].discover = time;
	V[u].color = GRAY;

	// 扫描 u 的邻接链表
	Edge *edge = V[u].head;
	while (edge != nullptr)
	{
		int v = edge->end;
		if (V[v].color == WHITE)
		{
			V[v].parent = u;
			DfsVisit(v);
			// 树边
			edge->type = TREE;
		}
		else if (V[v].color == GRAY)
		{
			// 后向边
			edge->type = BACK;
		}
		else if (V[v].color == BLACK)
		{
			// 前向边
			if (V[u].discover < V[v].discover)
				edge->type = FORWARD;
			// 横向边
			else
				edge->type = CROSS;
		}
		edge = edge->next;
	}

	V[u].color = BLACK;
	time++;
	V[u].finish = time;
	// 拓扑排序
	topo_sort_result.insert(topo_sort_result.begin(), u);
}

void DFS_NAMESPACE::LinkGraph::PrintBracket()
{
	for (int i = 1; i <= vert_num; i++)
	{
		cout << "vert:" << i << "{" << V[i].discover << ", " << V[i].finish << "}" << endl;
	}
}


void DFS_NAMESPACE::LinkGraph::PrintEdgeType()
{
	for (int i = 1; i <= vert_num; i++)
	{
		Edge *edge = V[i].head;
		while (edge != nullptr)
		{
			cout << edge->start << "->" << edge->end << ":";
			switch (edge->type)
			{
			case TREE:
				cout << "Tree edge" << endl;
				break;
			case BACK:
				cout << "Back edge" << endl;
				break;
			case FORWARD:
				cout << "Forward edge" << endl;
				break;
			case CROSS:
				cout << "Cross edge" << endl;
				break;
			}
			edge = edge->next;
		}
	}
}

void DFS_NAMESPACE::LinkGraph::TopologicalSort()
{
	if(topo_sort_result.empty())
		DFS();
	for (auto iter = topo_sort_result.begin(); iter != topo_sort_result.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

void DFS_NAMESPACE::DfsTest()
{
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
	LG->DFS();
	cout << "Bracket Info---------------------\n";
	LG->PrintBracket();
	cout << "EdgeType Info--------------------\n";
	LG->PrintEdgeType();
	cout << "TopologicalSort------------------\n";
	LG->TopologicalSort();  // 此输入图为有向有环图，需改变
#endif
}

/*

LG-------------------------------
1->2
2->4->5
3->2
4
5->4
Bracket Info---------------------
vert:1{1, 8}
vert:2{2, 7}
vert:3{9, 10}
vert:4{3, 4}
vert:5{5, 6}
EdgeType Info--------------------
1->2:Tree edge
2->4:Tree edge
2->5:Tree edge
3->2:Cross edge
5->4:Cross edge
TopologicalSort------------------
3 1 2 5 4
请按任意键继续. . .

*/

