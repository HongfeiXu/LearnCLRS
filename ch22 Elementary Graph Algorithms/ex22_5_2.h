/*
ex 22.5-2
Show how the procedure STRONGLY-CONNECTED-COMPONENTS works on the
graph of Figure 22.6. Specifically, show the finishing times computed in line 1 and
the forest produced in line 3. Assume that the loop of lines 5–7 of DFS considers
vertices in alphabetical order and that the adjacency lists are in alphabetical order.
*/

#ifndef EX22_5_2_H
#define EX22_5_2_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

namespace EX22_5_2_NAMESPACE
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

const int k_vert_num = 10;

struct Edge {
	int start;
	int end;
	int value;
	Type type;
	Edge *next;
	
	Edge(int start_, int end_) : start(start_), end(end_), next(nullptr) { }
};

struct Vertex {
	int id;
	Color color;
	Edge *head;
	int discover;	// 记录结点第一次被发现的时间  discover
	int finish;		// 记录完成对该结点邻接链表扫描的时间  finish
	Vertex *parent;	// 指向遍历结果的父结点

	Vertex(int id_) : id(id_), color(WHITE), head(nullptr), parent(nullptr) { }
};

struct Graph {
	Vertex *V[k_vert_num + 1];	// kN 个结点

	Graph()
	{
		for (int i = 1; i <= k_vert_num; i++)
		{
			V[i] = new Vertex(i);
		}
	}
	~Graph()
	{
		for (int i = 1; i <= k_vert_num; i++)
		{
			delete V[i];
		}
	}
};

int time = 0;
bool flag = 0;	// 控制 DFS 中选点的模式（一种是正常顺序，另一种是以 u.f 的降序选顶点）
int topo_sort[k_vert_num + 1] = { k_vert_num };
const char k_start_char = 'p'; // 输入的顶点从 q 开始

void InsertEdge(Graph *G, Edge *E)
{
	if (G->V[E->start]->head == nullptr || G->V[E->start]->head->end > E->end)
	{
		E->next = G->V[E->start]->head;
		G->V[E->start]->head = E;
	}
	else
	{
		Edge *temp_edge = G->V[E->start]->head;
		Edge *temp_pre_edge = temp_edge;
		while (temp_edge && temp_edge->end < E->end)
		{
			temp_pre_edge = temp_edge;
			temp_edge = temp_edge->next;
		}
		if (temp_edge && temp_edge->end == E->end)
			return;
		E->next = temp_edge;
		temp_pre_edge->next = E;
	}
}

Graph* Reverse(const Graph *G)
{
	Graph *ret = new Graph;

	for (int i = 1; i <= k_vert_num; i++)
	{
		Edge *edge = G->V[i]->head;
		while (edge)
		{
			Edge *reverse_edge = new Edge(edge->end, edge->start);
			InsertEdge(ret, reverse_edge);
			edge = edge->next;
		}
	}
	return ret;
}

void PrintGraph(const Graph *G)
{
	for (int i = 1; i <= k_vert_num; i++)
	{
		cout << char(i + k_start_char);
		Edge *temp_edge = G->V[i]->head;
		while (temp_edge)
		{
			cout << "->" << char(temp_edge->end + k_start_char);
			temp_edge = temp_edge->next;
		}
		cout << endl;
	}
}

void DfsVisit(Graph *G, Vertex *u)
{
	if (flag != 0)		// 如果是第二次调用 DFS ，则输出每个强连通分量的信息
	{
		cout << char(u->id + k_start_char) << " ";
	}

	time++;
	u->discover = time;
	u->color = GRAY;

	// 扫描 u 的邻接链表
	Edge *edge = u->head;
	while (edge != nullptr)
	{
		Vertex *v = G->V[edge->end];
		if (v->color == WHITE)
		{
			v->parent = u;
			DfsVisit(G, v);
			// 树边
			edge->type = TREE;
		}
		else if (v->color == GRAY)
		{
			// 后向边
			edge->type = BACK;
		}
		else if (v->color == BLACK)
		{
			// 前向边
			if (u->discover < v->discover)
				edge->type = FORWARD;
			// 横向边
			else
				edge->type = CROSS;
		}
		edge = edge->next;
	}

	u->color = BLACK;
	time++;
	u->finish = time;
	// 把结果按 u.f 降序保存于 topo_sort 数组中
	if (flag == 0)
	{
		topo_sort[topo_sort[0]] = u->id;
		topo_sort[0]--;
	}
}

void DFS(Graph *G)
{
	for (int i = 1; i <= k_vert_num; i++)
	{
		G->V[i]->color = WHITE;
		G->V[i]->parent = nullptr;
	}

	// 时间戳置0
	time = 0;
	for (int i = 1; i <= k_vert_num; i++)
	{
		int j;			// 待选择的点的id
		if (flag == 0)  // 正常顺序选点
		{
			j = i;
		}
		else			// 按照 u.f 的降序选点	
		{
			j = topo_sort[i];
		}
		if (G->V[j]->color == WHITE)
		{
			DfsVisit(G, G->V[j]);
			if (flag != 0)			// 如果是第二次 DFS，则每次调用 DfsVisit 将会得到一个强连通分量，输出它
				cout << endl;
		}
	}
}

void StronglyConnectedComponent(Graph *G)
{
	// 重置 topo_sort 的值
	for (int i = 0; i <= k_vert_num; i++)
	{
		topo_sort[i] = 0;
	}
	topo_sort[0] = k_vert_num;

	// 计算每个顶点的 finish 值，并将结点 id 按照 finish 降序存在 topo_sort[] 中
	DFS(G);
	
	cout << "Vert id  Finish time" << endl;
	for (int i = 1; i <= k_vert_num; i++)
	{
		cout << char(G->V[i]->id + k_start_char) << "    \t" << G->V[i]->finish << endl;
	}

	Graph *G_reverse = Reverse(G);

	flag = 1;
	cout << "Each Strongly Connected Component:" << endl;
	DFS(G_reverse);
}

void Test()
{
	Graph *G = new Graph;
	const int k_edge_count = 14;

	// 14 条边
	vector<pair<char, char>> input = {
		make_pair('q', 's'),
		make_pair('s', 'v'),
		make_pair('v', 'w'),
		make_pair('w', 's'),
		make_pair('q', 'w'),
		make_pair('q', 't'),
		make_pair('t', 'y'),
		make_pair('y', 'q'),
		make_pair('t', 'x'),
		make_pair('x', 'z'),
		make_pair('z', 'x'),
		make_pair('u', 'y'),
		make_pair('r', 'y'),
		make_pair('r', 'u')
	};

	for (int i = 0; i < k_edge_count; i++)
	{
		Edge *temp_edge = new Edge(input[i].first - k_start_char, input[i].second - k_start_char);
		InsertEdge(G, temp_edge);
	}

	cout << "Graph G:\n";
	PrintGraph(G);

	StronglyConnectedComponent(G);
}

}


/*

Graph G:
q->s->t->w
r->u->y
s->v
t->x->y
u->y
v->w
w->s
x->z
y->q
z->x
Vert id  Finish time
q       16
r       20
s       7
t       15
u       19
v       6
w       5
x       12
y       14
z       11
Each Strongly Connected Component:
r
u
q y t
x z
s w v
请按任意键继续. . .

*/

#endif // !EX22_5_2_H
