/*

练习 22.4-3 给出一个算法，用它来确定一个给定的 无向图G=(V,E) 中是否包含一个回路。
所给出的算法的运行时间为O(V)，这一时间独立于|E|。

解答：
类似于有向图拓扑排序的思路：
有向图：如果存在回路，则必存在一个子图，是一个环。因此该子图中所有顶点入度>=1。
无向图：如果存在回路，则必存在一个子图，是一个环路。因此环路中所有顶点的度>=2。
第一步：删除所有度<=1的顶点及相关的边，并将另外与这些边相关的其它顶点的度减一。
第二步：将度数变为1的顶点排入队列，并从该队列中取出一个顶点重复步骤一。
如果最后还有未删除顶点，则存在环，否则没有环。

*/

#ifndef EX22_4_3_H
#define EX22_4_3_H

#include <climits>
#include <list>

using namespace std;

namespace EX22_4_3_NAMESPACE
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

// 这里LinkGraph 为无向图，使用时通过AddDoubleEdge 和 DeleteDoubleEdge 来增删边
class LinkGraph {
public:
	int vert_num;
	int edge_num;  // 记录边数，用以判断是否有环路，这里对于无向图的每条边会使 edge_num + 2，
	               // 故对于无向图，如果 edge_num/2 > vert_num-1 则一定存在环
	Vertex *V;     // vert list [1...vert_num] 为有效内容
	bool *vert_deleted; // 用以标记被删除的顶点，值为1时为已经删除，值为0时为未被删除

	int *vert_degree;   // 每个顶点的度

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_), edge_num(0)
	{
		V = new Vertex[vert_num_ + 1];
		vert_degree = new int[vert_num_ + 1];
		fill(vert_degree, vert_degree + vert_num_ + 1, 0);
		vert_deleted = new bool[vert_num_ + 1];
		fill(vert_deleted, vert_deleted + vert_num_ + 1, false);
	}
	~LinkGraph()
	{
		delete[] V;
		delete[] vert_degree;
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
		edge_num++;
	}
	void AddDoubleEdge(int a, int b, int value = 1)
	{
		AddSingleEdge(a, b, value);
		AddSingleEdge(b, a, value);
		edge_num++;
		vert_degree[a]++;
		vert_degree[b]++;
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
	}
	void DeleteDoubleEdge(int a, int b)
	{
		DeleteSingleEdge(a, b);
		DeleteSingleEdge(b, a);
		edge_num--;
		vert_degree[a]--;
		vert_degree[b]--;
	}

	// 删除顶点u，以及所有与u相邻的边
	void DeleteVertex(int u)
	{
		vert_deleted[u] = true;

		// 删除所有u的邻接边
		Edge *edge = V[u].head;
		while (edge!=nullptr)
		{
			int v = edge->end;
			edge = edge->next;
			DeleteDoubleEdge(u, v);
		}
		V[u].head = nullptr;
	}

	// 不断删去度为1的结点，如果最后所有的结点都被删除，则无环，否则有环
	bool DoseUndirectedGraphHasLoop();

	// Debug
	void Print();
	void PrintDegree();
};

void Test();
} // namespace EX22_4_3_NAMESPACE

#endif  // !EX22_4_3_H
