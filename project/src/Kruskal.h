#ifndef KRUSKAL_H
#define KRUSKAL_H

/***************************************************************************
*  @file       Kruskal.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       9.15 2017
*  @remark     MST-KRUSKAL, Learn DisjointSet
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <tuple>
#include "DisjointSets.h"

using namespace std;

namespace KRUSKAL_NAMESPACE
{
class Edge {
public:
	int start;
	int end;
	int weight;		// 权重
	Edge *next;

public:
	Edge(int start_, int end_, int weight_) :
		start(start_), end(end_), weight(weight_), next(nullptr)
	{
	}
};

class Vertex {
public:
	Edge *head;

public:
	Vertex() : head(nullptr) { }
	~Vertex()
	{
		Edge *temp = head;
		while (temp != nullptr)
		{
			Edge *pre = temp;
			temp = temp->next;
			delete pre;
		}
	}
};

class LinkGraph {
private:
	int vert_num;
	Vertex *V;					// vert list V[1..vert_num] 为有效元素

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_)
	{
		V = new Vertex[vert_num_ + 1];
	}
	~LinkGraph() { delete[]V; }

	void AddSingleEdge(int start, int end, int weight = 0)
	{
		Edge *new_edge = new Edge(start, end, weight);
		if (V[start].head == nullptr || V[start].head->end > end)
		{
			new_edge->next = V[start].head;
			V[start].head = new_edge;
		}
		else
		{
			Edge *temp_edge = V[start].head;
			Edge *pre = V[start].head;
			while (temp_edge != nullptr && temp_edge->end < end)
			{
				pre = temp_edge;
				temp_edge = temp_edge->next;
			}
			// 如果重复添加某一条边，则删除之。
			if (temp_edge != nullptr && temp_edge->end == end)
			{
				delete new_edge;
				return;
			}
			new_edge->next = temp_edge;
			pre->next = new_edge;
		}
	}

	void AddDoubleEdge(int a, int b, int weight = 0)
	{
		AddSingleEdge(a, b, weight);
		AddSingleEdge(b, a, weight);
	}

	void DeletSingleEdge(int start, int end)
	{
		Edge *temp_edge = V[start].head;
		Edge *pre = temp_edge;
		while (temp_edge != nullptr && temp_edge->end < end)
		{
			pre = temp_edge;
			temp_edge = temp_edge->next;
		}
		// 如果图中不存在该边
		if (temp_edge == nullptr || temp_edge->end > end)
			return;
		else
		{
			// 待删除边为边表的第一个元素
			if (temp_edge == V[start].head)
				V[start].head = temp_edge->next;
			else

				pre->next = temp_edge->next;
			delete temp_edge;
		}
	}

	void DeleteDoubleEdge(int a, int b)
	{
		DeletSingleEdge(a, b);
		DeletSingleEdge(b, a);
	}

	void Print()
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

	vector<Edge*> MstKruskal()
	{
		vector <Edge*> A;	// 保存某棵最小生成树的边
		DisjointSet disjoint_set;			// 维护互不相交的元素集合，每个集合代表当前森林中的一棵树。
		disjoint_set.init_set(vert_num);	// 得到 vert_num 个森林

		vector<Edge*> E;	// 保存图G的所有边
		for (int i = 1; i <= vert_num; i++)
		{
			Edge *temp_edge = V[i].head;
			while (temp_edge != nullptr)
			{
				E.push_back(temp_edge);
				temp_edge = temp_edge->next;
			}
		}

		sort(E.begin(), E.end(), [](const Edge* lhs, const Edge *rhs) { return lhs->weight < rhs->weight; });

		for (auto temp_edge : E)
		{
			int u = temp_edge->start;
			int v = temp_edge->end;
			if (disjoint_set.find_set(u) != disjoint_set.find_set(v))
			{
				A.push_back(temp_edge);
				disjoint_set.union_set(u, v);
			}
		}

		return A;
	}
};

void KruskalTest()
{
	vector<tuple<int, int, int>> input = {
		make_tuple(1,2,4),
		make_tuple(1,8,8),
		make_tuple(2,3,8),
		make_tuple(3,4,7),
		make_tuple(3,6,4),
		make_tuple(3,9,2),
		make_tuple(4,5,9),
		make_tuple(4,6,14),
		make_tuple(5,6,10),
		make_tuple(6,7,2),
		make_tuple(7,8,1),
		make_tuple(7,9,6),
		make_tuple(8,9,7)
	};
	const int k_vert_num = 9;
	LinkGraph *LG = new LinkGraph(k_vert_num);
	for (auto &item : input)
		LG->AddDoubleEdge(get<0>(item), get<1>(item), get<2>(item));

	cout << "LG:\n";
	LG->Print();

	vector<Edge*> A = LG->MstKruskal();
	cout << "MST:\n";
	for (auto item : A)
	{
		cout << item->start << "->" << item->end << " : " << item->weight << endl;
	}
}

/*

LG:
1->2->8
2->1->3
3->2->4->6->9
4->3->5->6
5->4->6
6->3->4->5->7
7->6->8->9
8->1->7->9
9->3->7->8
MST:
7->8 : 1
3->9 : 2
6->7 : 2
1->2 : 4
3->6 : 4
3->4 : 7
1->8 : 8
4->5 : 9
请按任意键继续. . .

*/
}

#endif // !KRUSKAL_H
