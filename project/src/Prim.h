#ifndef PRIM_H
#define PRIM_H

/***************************************************************************
*  @file       Prim.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       9.15 2017
*  @remark     MST-PRIM, Learn make_heap pop_heap, use vector as a heap
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

namespace PRIM_NAMESPACE
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
	int id;
	Edge *head;
	// v.key 保存的是连接 v 和树中结点的所有边中最小边的权重。如果不存在这样的边，则 v.key = INF
	int key;
	// v.parent给出的是结点　ｖ　在树中的父节点
	int parent;

public:
	Vertex() : head(nullptr) { }
	Vertex(int id_) : id(id_), head(nullptr) { }
	void set_id(int id_) { id = id_; }
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
		for (int i = 1; i <= vert_num_; i++)
		{
			V[i].set_id(i);
		}
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

	void MstPrim(int root)	//  root 为最小生成树的根节点
	{
		for (int i = 1; i <= vert_num; i++)
		{
			V[i].key = INT_MAX;
			V[i].parent = 0;
		}

		V[root].key = 0;

		vector<Vertex*> V_vec;
		for (int i = 1; i <= vert_num; i++)
		{
			V_vec.push_back(&V[i]);
		}

		auto cmp = [](Vertex *lhs, Vertex *rhs) { return lhs->key > rhs->key; };
				
		while (!V_vec.empty())
		{
			make_heap(V_vec.begin(), V_vec.end(), cmp);	// 利用 cmp 建小顶堆
			pop_heap(V_vec.begin(), V_vec.end(), cmp);	// moves the largest to the end
			Vertex *u = V_vec.back();
			V_vec.pop_back();

			Edge *temp_edge = u->head;
			while (temp_edge != nullptr)
			{
				Vertex *v = &V[temp_edge->end];

				auto v_iter = find(V_vec.begin(), V_vec.end(), v);
				if ((v_iter != V_vec.end()) &&
					temp_edge->weight < (*v_iter)->key)
				{
					(*v_iter)->key = temp_edge->weight;
					(*v_iter)->parent = u->id;
				}
				temp_edge = temp_edge->next;
			}
		}

		// 使用层次遍历的方式输出最小生成树的所有边
		queue<Vertex *> queue;
		queue.push(&V[root]);
		vector<pair<int, int>> tree_edge;
		
		while (!queue.empty())
		{
			Vertex* temp_vert = queue.front();
			queue.pop();
			for (int i = 1; i <= vert_num; i++)
			{
				if (V[i].parent == temp_vert->id)
				{
					tree_edge.push_back(make_pair(temp_vert->id, V[i].id));
					queue.push(&V[i]);
				}
			}
		}
		cout << "The edges in MST:\n";
		for (unsigned i = 0 ; i < tree_edge.size(); i++)
		{
			cout << tree_edge[i].first << "-" << tree_edge[i].second << endl;
		}
	}
};

void PrimTest()
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
	LG->MstPrim(1);
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
The edges in MST:
1-2
2-3
3-4
3-6
3-9
4-5
6-7
7-8
请按任意键继续. . .

*/

}

#endif // !PRIM_H
