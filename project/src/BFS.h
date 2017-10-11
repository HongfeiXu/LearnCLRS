/***************************************************************************
*  @file       BFS.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.19 2017
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef BFS_H
#define BFS_H

#include <climits>

namespace BFS_NAMESPACE
{
enum Color {
	WHITE = 0,
	GRAY,
	BLACK
};

class Edge {
public:
	int start;
	int end;
	int value;
	Edge *next;

public:
	Edge(int start_, int end_, int value_ = 1)
		: start(start_), end(end_), value(value_)
	{
	}
};

class Vertex {
public:
	Color color;
	int parent;
	int distance;
	Edge *head;

public:
	Vertex() :color(WHITE), parent(0), distance(INT_MAX), head(nullptr) { }
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
	int vert_num;
	Vertex *V;  // vert list

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_)
	{
		V = new Vertex[vert_num_ + 1];
	}
	~LinkGraph()
	{
		delete[] V;
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

	void BFS(int s);
	void PrintPath(int s, int v);
};

void BfsTest();
} // namespace BFS

#endif  // !BFS_NAMESPACE
