/*

练习 22.4-5 在有向五环图 `G=(V, E)`上执行拓扑排序还有一种办法，
就是重复找入度为 0 的结点，输出该结点，将该结点及其发出的边从图中删除。
请解释如何在`O(V+E)`的时间实现这种思想。如果`G`包含环路，将会发生什么情况？

*/

#ifndef EX22_4_5_H
#define EX22_4_5_H

#include <climits>
#include <list>

using namespace std;

namespace EX22_4_5_NAMESPACE
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

// 这里图为有向图
class LinkGraph {
public:
	int vert_num;
	Vertex *V;     // vert list [1...vert_num] 为有效内容
	bool *vert_deleted; // 用以标记被删除的顶点，值为1时为已经删除，值为0时为未被删除

	int *vert_indegree;   // 每个顶点的入度

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_)
	{
		V = new Vertex[vert_num_ + 1];
		vert_indegree = new int[vert_num_ + 1];
		fill(vert_indegree, vert_indegree + vert_num_ + 1, 0);
		vert_deleted = new bool[vert_num_ + 1];
		fill(vert_deleted, vert_deleted + vert_num_ + 1, false);
	}
	~LinkGraph()
	{
		delete[] V;
		delete[] vert_indegree;
		delete[] vert_deleted;
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
		vert_indegree[end]++;
	}
	void AddDoubleEdge(int a, int b, int value = 1)
	{
		AddSingleEdge(a, b, value);
		AddSingleEdge(b, a, value);
	}
	void DeleteSingleEdge(int start, int end)
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
		vert_indegree[end]--;
	}
	void DeleteDoubleEdge(int a, int b)
	{
		DeleteSingleEdge(a, b);
		DeleteSingleEdge(b, a);
		vert_indegree[a]--;
		vert_indegree[b]--;
	}

	// 删除顶点u，以及所有与u相邻的边
	void DeleteVertex(int u)
	{
		vert_deleted[u] = true;

		// 删除所有u的邻接边
		Edge *edge = V[u].head;
		while (edge != nullptr)
		{
			int v = edge->end;
			edge = edge->next;
			DeleteDoubleEdge(u, v);
		}
		V[u].head = nullptr;
	}

	void TopologicalSort_v2();

	// Debug
	void Print();
	void PrintInDegree();
};

void Test();
} // namespace EX22_4_5_NAMESPACE



#endif
