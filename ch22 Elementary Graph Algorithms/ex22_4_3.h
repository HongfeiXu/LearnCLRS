/*

��ϰ 22.4-3 ����һ���㷨��������ȷ��һ�������� ����ͼG=(V,E) ���Ƿ����һ����·��
���������㷨������ʱ��ΪO(V)����һʱ�������|E|��

���
����������ͼ���������˼·��
����ͼ��������ڻ�·����ش���һ����ͼ����һ��������˸���ͼ�����ж������>=1��
����ͼ��������ڻ�·����ش���һ����ͼ����һ����·����˻�·�����ж���Ķ�>=2��
��һ����ɾ�����ж�<=1�Ķ��㼰��صıߣ�������������Щ����ص���������Ķȼ�һ��
�ڶ�������������Ϊ1�Ķ���������У����Ӹö�����ȡ��һ�������ظ�����һ��
��������δɾ�����㣬����ڻ�������û�л���

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

// ����LinkGraph Ϊ����ͼ��ʹ��ʱͨ��AddDoubleEdge �� DeleteDoubleEdge ����ɾ��
class LinkGraph {
public:
	int vert_num;
	int edge_num;  // ��¼�����������ж��Ƿ��л�·�������������ͼ��ÿ���߻�ʹ edge_num + 2��
	               // �ʶ�������ͼ����� edge_num/2 > vert_num-1 ��һ�����ڻ�
	Vertex *V;     // vert list [1...vert_num] Ϊ��Ч����
	bool *vert_deleted; // ���Ա�Ǳ�ɾ���Ķ��㣬ֵΪ1ʱΪ�Ѿ�ɾ����ֵΪ0ʱΪδ��ɾ��

	int *vert_degree;   // ÿ������Ķ�

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
			// ����ظ����ĳһ���ߣ���ɾ��֮��
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
	}
	void DeleteDoubleEdge(int a, int b)
	{
		DeleteSingleEdge(a, b);
		DeleteSingleEdge(b, a);
		edge_num--;
		vert_degree[a]--;
		vert_degree[b]--;
	}

	// ɾ������u���Լ�������u���ڵı�
	void DeleteVertex(int u)
	{
		vert_deleted[u] = true;

		// ɾ������u���ڽӱ�
		Edge *edge = V[u].head;
		while (edge!=nullptr)
		{
			int v = edge->end;
			edge = edge->next;
			DeleteDoubleEdge(u, v);
		}
		V[u].head = nullptr;
	}

	// ����ɾȥ��Ϊ1�Ľ�㣬���������еĽ�㶼��ɾ�������޻��������л�
	bool DoseUndirectedGraphHasLoop();

	// Debug
	void Print();
	void PrintDegree();
};

void Test();
} // namespace EX22_4_3_NAMESPACE

#endif  // !EX22_4_3_H
