/***************************************************************************
*  @file       Graph.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.18 2017
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <utility>  // pair
#include <algorithm>

using namespace std;

namespace GRAPH_NAMESPACE
{
//////////////////////////////////////////////////////////////////////////
// An adjacency-list representation of G

class Edge {
public:
	int start;
	int end;
	int value;
	Edge *next;

public:
	Edge(int start_, int end_, int value_ = 1) : 
		start(start_), end(end_), value(value_), next(nullptr) { }
};

class Vertex {
public:
	Edge *head;

public:
	Vertex(): head(nullptr) { }
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
	Vertex *V;  // vert list V[1..vert_num] 为有效元素

public:
	LinkGraph(int vert_num_) : vert_num(vert_num_)
	{
		V = new Vertex[vert_num_ + 1];
	}
	~LinkGraph() { delete[]V; }

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

	void OutDegree();  // O(E+V)
	void InDegree();   // O(E+V)
	void Print();

	// 练习 22.1-3 有向图的转置
	LinkGraph* Transpose();  // O(V+E)
	// 练习 22.1-5 有向图的平方
	LinkGraph* Square();
};

void LinkGraphTest();

//////////////////////////////////////////////////////////////////////////
// The adjacency-matrix representation of G

class MatGraph {
private:
	int vert_num;
	int **mat;

public:
	MatGraph(int vert_num_) : vert_num(vert_num_)
	{
		mat = new int *[vert_num_ + 1];
		for (int i = 0; i <= vert_num_; i++)
		{
			mat[i] = new int[vert_num_ + 1];
		}
		for (int i = 0; i <= vert_num_; i++)
		{
			for (int j = 0; j <= vert_num_; j++)
			{
				mat[i][j] = 0;
			}
		}
	}
	~MatGraph()
	{
		for (int i = 0; i <= vert_num; i++)
		{
			delete[] mat[i];
		}
		delete[] mat;
		mat = nullptr;
	}
	void AddSingleEdge(int start, int end, int value = 1)
	{
		mat[start][end] = value;
	}
	void AddDoubleEdge(int a, int b, int value = 1)
	{
		mat[a][b] = 1;
		mat[b][a] = 1;
	}
	void DeleteSingleEdge(int start, int end)
	{
		mat[start][end] = 0;
	}
	void DeleteDoubleEdge(int a, int b)
	{
		mat[a][b] = 0;
		mat[b][a] = 0;
	}

	void OutDegree();  // O(E+V)
	void InDegree();   // O(E+V)
	void Print();

	// 练习 22.1-3 有向图的转置
	MatGraph* Transpose();
	// 练习 22.1-5 有向图的平方
	MatGraph* Square();
};

void MatGraphTest();
}

#endif // !GRAPH_H
