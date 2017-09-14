#include "Graph.h"

//////////////////////////////////////////////////////////////////////////
// Definition of class LinkGraph's member functions and it's test function

void GRAPH_NAMESPACE::LinkGraph::OutDegree()
{
	for (int i = 1; i <= vert_num; i++)
	{
		int cnt = 0;
		Edge *temp_edge = V[i].head;
		while (temp_edge != nullptr)
		{
			cnt++;
			temp_edge = temp_edge->next;
		}
		cout << "OutDegree of Vertex " << i << ": " << cnt << endl;
	}
}

void GRAPH_NAMESPACE::LinkGraph::InDegree()
{
	int *indegree_arr = new int[vert_num + 1];
	fill(indegree_arr, indegree_arr + vert_num + 1, 0);

	for (int i = 1; i <= vert_num; i++)
	{
		Edge *temp_edge = V[i].head;
		while (temp_edge != nullptr)
		{
			indegree_arr[temp_edge->end]++;
			temp_edge = temp_edge->next;
		}
	}
	for (int i = 1; i <= vert_num; i++)
	{
		cout << "InDegree of Vertex " << i << ": " << indegree_arr[i] << endl;
	}
}

void GRAPH_NAMESPACE::LinkGraph::Print()
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

GRAPH_NAMESPACE::LinkGraph* GRAPH_NAMESPACE::LinkGraph::Transpose()
{
	LinkGraph* LG_new = new LinkGraph(vert_num);
	// 遍历图G中的每一条边，反转方向，加入新图中
	for (int i = 1; i <= vert_num; i++)
	{
		Edge *temp_edge = V[i].head;
		while (temp_edge != nullptr)
		{
			LG_new->AddSingleEdge(temp_edge->end, i);
			temp_edge = temp_edge->next;
		}
	}
	return LG_new;
}

GRAPH_NAMESPACE::LinkGraph* GRAPH_NAMESPACE::LinkGraph::Square()
{
	LinkGraph* LG_new = new LinkGraph(vert_num);
	for (int i = 1; i <= vert_num; i++)
	{
		Edge *temp_edge = V[i].head;
		while (temp_edge != nullptr)
		{
			// 把原来有的边加入到新图中
			LG_new->AddSingleEdge(temp_edge->start, temp_edge->end);
			// 把以 temp_edge 终点为起点的边加入新图中
			Edge *temp_edge_2 = V[temp_edge->end].head;
			while (temp_edge_2)
			{
				LG_new->AddSingleEdge(temp_edge->start, temp_edge_2->end);
				temp_edge_2 = temp_edge_2->next;
			}
			temp_edge = temp_edge->next;
		}
	}
	return LG_new;
}

void GRAPH_NAMESPACE::LinkGraphTest()
{
	cout << "LinkGraphTest" << endl;

	vector<pair<int, int>> input = {
		make_pair(1,2),
		make_pair(1,4),
		make_pair(2,5),
		make_pair(3,6),
		make_pair(3,5),
		make_pair(4,2),
		make_pair(5,4),
		make_pair(6,6) };
	LinkGraph *LG = new LinkGraph(input.size());
	for (auto &item : input)
		LG->AddSingleEdge(item.first, item.second);
	cout << "LG:\n";
	LG->Print();
	//LG->OutDegree();
	//LG->InDegree();
	cout << "LG_Trans:\n";
	LinkGraph *LG_Trans = LG->Transpose();
	LG_Trans->Print();
	cout << "LG_Sq:\n";
	LinkGraph *LG_Sq = LG->Square();
	LG_Sq->Print();
}

/*

LinkGraphTest
LG:
1->2->4
2->5
3->5->6
4->2
5->4
6->6
7
8
LG_Trans:
1
2->1->4
3
4->1->5
5->2->3
6->3->6
7
8
LG_Sq:
1->2->4->5
2->4->5
3->4->5->6
4->2->5
5->2->4
6->6
7
8
请按任意键继续. . .

*/

//////////////////////////////////////////////////////////////////////////
// Definition of class MatGraph's member functions and it's test function


void GRAPH_NAMESPACE::MatGraph::OutDegree()
{
	for (int i = 1; i <= vert_num; i++)
	{
		int cnt = 0;
		for (int j = 1; j <= vert_num; j++)
		{
			if (mat[i][j] != 0)
				cnt++;
		}
		cout << "OutDegree of Vertex " << i << ": " << cnt << endl;
	}
}

void GRAPH_NAMESPACE::MatGraph::InDegree()
{
	for (int i = 1; i <= vert_num; i++)
	{
		int cnt = 0;
		for (int j = 1; j <= vert_num; j++)
		{
			if (mat[j][i] != 0)
				cnt++;
		}
		cout << "InDegree of Vertex " << i << ": " << cnt << endl;
	}
}

void GRAPH_NAMESPACE::MatGraph::Print()
{
	for (int i = 1; i <= vert_num; i++)
	{
		for (int j = 1; j <= vert_num; j++)
			cout << mat[i][j] << ' ';
		cout << endl;
	}
}

GRAPH_NAMESPACE::MatGraph * GRAPH_NAMESPACE::MatGraph::Transpose()
{
	MatGraph *MG_new = new MatGraph(vert_num);

	for (int i = 1; i <= vert_num; i++)
	{
		for (int j = 1; j <= vert_num; j++)
		{
			if (mat[i][j] != 0)
				MG_new->AddSingleEdge(j, i);
		}
	}
	return MG_new;
}

GRAPH_NAMESPACE::MatGraph * GRAPH_NAMESPACE::MatGraph::Square()
{
	MatGraph *MG_new = new MatGraph(vert_num);
	for (int i = 1; i <= vert_num; i++)
	{
		for (int j = 1; j <= vert_num; j++)
		{
			if (mat[i][j] != 0)
			{
				MG_new->AddSingleEdge(i, j);
				for (int k = 1; k <= vert_num; k++)
				{
					if (mat[j][k] != 0)
						MG_new->AddSingleEdge(i, k);
				}
			}
		}
	}
	return MG_new;
}

void GRAPH_NAMESPACE::MatGraphTest()
{
	cout << "MatGraphTest" << endl;

	vector<pair<int, int>> input = {
		make_pair(1,2),
		make_pair(1,4),
		make_pair(2,5),
		make_pair(3,6),
		make_pair(3,5),
		make_pair(4,2),
		make_pair(5,4),
		make_pair(6,6) 
	};
	MatGraph *MG = new MatGraph(input.size());
	for (auto &item : input)
		MG->AddSingleEdge(item.first, item.second);
	cout << "MG:" << endl;
	MG->Print();
	cout << "MG->OutDegree:" << endl;
	MG->OutDegree();
	MatGraph *MG_Trans = MG->Transpose();
	cout << "MG_Trans:" << endl;
	MG_Trans->Print();
	MatGraph *MG_Sq = MG->Square();
	cout << "MG_Sq:" << endl;
	MG_Sq->Print();
	
}

/*

MatGraphTest
MG:
0 1 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 1 1 0 0
0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
MG->OutDegree:
OutDegree of Vertex 1: 2
OutDegree of Vertex 2: 1
OutDegree of Vertex 3: 2
OutDegree of Vertex 4: 1
OutDegree of Vertex 5: 1
OutDegree of Vertex 6: 1
OutDegree of Vertex 7: 0
OutDegree of Vertex 8: 0
MG_Trans:
0 0 0 0 0 0 0 0
1 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 1 0 0 0
0 1 1 0 0 0 0 0
0 0 1 0 0 1 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
MG_Sq:
0 1 0 1 1 0 0 0
0 0 0 1 1 0 0 0
0 0 0 1 1 1 0 0
0 1 0 0 1 0 0 0
0 1 0 1 0 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
请按任意键继续. . .

*/