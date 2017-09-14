/***************************************************************************
*  @file       DFS.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.19 2017
*  @remark     DFS and Topological sort
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef DFS_H
#define DFS_H

#include <climits>
#include <list>

using namespace std;

namespace DFS_NAMESPACE
{
enum Color {
	WHITE = 0,
	GRAY,
	BLACK
};

// 深度优先森林中四种边的类型
enum Type {
	NONE = 0,
	TREE,
	BACK,
	FORWARD,
	CROSS
};

class Edge {
public:
	int start;
	int end;
	Type type;
	int value;
	Edge *next;

public:
	Edge(int start_, int end_, int value_ = 1)
		: start(start_), end(end_), type(NONE), value(value_)
	{
	}
};

class Vertex {
public:
	Color color;
	int discover;  // 记录结点第一次被发现的时间  discover
	int finish;  // 记录完成对该结点邻接链表扫描的时间  finish
	int parent;
	Edge *head;

public:
	Vertex() :color(WHITE), parent(0), head(nullptr) { }
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
public:
	int time;   // DFS 用到的时间戳
	int vert_num;
	Vertex *V;  // vert list [1...vert_num] 为有效内容
	list<int> topo_sort_result;  // 存储拓扑排序后的结点序号。[1...vert_num]
	

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_)
	{
		V = new Vertex[vert_num_ + 1];
	}
	~LinkGraph()
	{
		delete[] V;
		topo_sort_result.clear();
	}
	void AddSingleEdge(int start, int end, int value = 1)
	{
		Edge *new_edge = new Edge(start, end, value);
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
	void AddDoubleEdge(int a, int b, int value = 1)
	{
		AddSingleEdge(a, b, value);
		AddSingleEdge(b, a, value);
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

	void Print();

	void DFS();
	void DfsVisit(int u);
	void PrintBracket();
	void PrintEdgeType();

	void TopologicalSort();
};

void DfsTest();
} // namespace DFS

#endif  // !DFS_NAMESPACE
