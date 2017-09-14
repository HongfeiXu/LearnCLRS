/*

��ϰ 22.4-5 �������廷ͼ `G=(V, E)`��ִ������������һ�ְ취��
�����ظ������Ϊ 0 �Ľ�㣬����ý�㣬���ý�㼰�䷢���ıߴ�ͼ��ɾ����
����������`O(V+E)`��ʱ��ʵ������˼�롣���`G`������·�����ᷢ��ʲô�����

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

// �������ɭ�������ֱߵ�����
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
	int discover;  // ��¼����һ�α����ֵ�ʱ��  discover
	int finish;  // ��¼��ɶԸý���ڽ�����ɨ���ʱ��  finish
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

// ����ͼΪ����ͼ
class LinkGraph {
public:
	int vert_num;
	Vertex *V;     // vert list [1...vert_num] Ϊ��Ч����
	bool *vert_deleted; // ���Ա�Ǳ�ɾ���Ķ��㣬ֵΪ1ʱΪ�Ѿ�ɾ����ֵΪ0ʱΪδ��ɾ��

	int *vert_indegree;   // ÿ����������

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
			// ����ظ����ĳһ���ߣ���ɾ��֮��
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
		// ���ͼ�в����ڸñ�
		if (temp_edge == nullptr || temp_edge->end > end)
			return;
		else
		{
			// ��ɾ����Ϊ�߱�ĵ�һ��Ԫ��
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

	// ɾ������u���Լ�������u���ڵı�
	void DeleteVertex(int u)
	{
		vert_deleted[u] = true;

		// ɾ������u���ڽӱ�
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
