#include "BFS.h"
#include <queue>
#include <iostream>
#include <utility>

using namespace std;

void BFS_NAMESPACE::LinkGraph::Print()
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

void BFS_NAMESPACE::LinkGraph::BFS(int s)
{
	for (int i = 1; i <= vert_num; i++)
	{
		V[i].color = WHITE;
		V[i].distance = INT_MAX;
		V[i].parent = 0;
	}
	V[s].color = GRAY;
	V[s].distance = 0;
	V[s].parent = 0;

	queue<int> Q;
	Q.push(s);
	while (!Q.empty())	
	{
		int u = Q.front();
		Q.pop();

		Edge *edge = V[u].head;
		while (edge != nullptr)
		{
			int v = edge->end;
			if (V[v].color == WHITE)
			{
				V[v].color = GRAY;
				V[v].distance = V[u].distance + 1;
				V[v].parent = u;
				Q.push(v);
			}
			edge = edge->next;
		}
		V[u].color = BLACK;
	}
}

void BFS_NAMESPACE::LinkGraph::PrintPath(int s, int v)
{
	if (v == s)
		cout << s;
	else if (V[v].parent == 0)
		cout << "no path from " << s << " to " << v << " exists" << endl;
	else
	{
		PrintPath(s, V[v].parent);
		cout << "->" << v;
	}
}

void BFS_NAMESPACE::BfsTest()
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
	LinkGraph *LG = new LinkGraph(6);
	for (auto &item : input)
		LG->AddSingleEdge(item.first, item.second);
	cout << "LG:\n";
	LG->Print();
	LG->BFS(3);
	cout << "After BFS(3), PrintPath(3,2):\n";
	LG->PrintPath(3,2);
#endif

#if 1
	// 练习 22.2-2
	vector<pair<int, int>> input_2 =
	{
		make_pair(1,2),
		make_pair(1,5),
		make_pair(2,6),
		make_pair(6,3),
		make_pair(6,7),
		make_pair(3,4),
		make_pair(3,7),
		make_pair(4,7),
		make_pair(4,8),
		make_pair(7,8)
	};
	LinkGraph *LG_2 = new LinkGraph(8);
	for (auto &item : input_2)
		LG_2->AddDoubleEdge(item.first, item.second);
	cout << "LG_2:\n";
	LG_2->Print();
	LG_2->BFS(4);
	cout << endl;
	cout << "distance:" << endl;
	for (int i = 1; i <= LG_2->vert_num; i++)
	{
		cout << LG_2->V[i].distance << " ";
	}
	cout << endl;
	cout << "parent:" << endl;
	for (int i = 1; i <= LG_2->vert_num; i++)
	{
		cout << LG_2->V[i].parent << " ";
	}
	cout << endl;
#endif
}

/*

LG:
1->2->4
2->5
3->5->6
4->2
5->4
6->6
7
8
After BFS(3), PrintPath(3,2):
3->5->4->2请按任意键继续. . .

*/
