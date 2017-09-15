/***************************************************************************
*  @file       DisjointSets.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       9.15 2017
*  @remark     Disjoint Sets
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <cstdio>
#include <cassert>

const int k_max_size = 100;

class DisjointSet{
public:
	int node_num;
	int parent[k_max_size + 1];	// {1..node_num} Ϊ��Ч
	int rank[k_max_size + 1];

public:
	DisjointSet() { }
	DisjointSet(int node_num_) : node_num(node_num_)
	{
		assert(node_num_ <= k_max_size);
		for (int i = 1; i <= node_num; i++)
		{
			make_set(i);
		}
	}

	void init_set(int node_num_)
	{
		node_num = node_num_;
		assert(node_num_ <= k_max_size);
		for (int i = 1; i <= node_num; i++)
		{
			make_set(i);
		}
	}

	// ��ʼ������
	void make_set(int x)
	{
		assert(x <= node_num);

		parent[x] = x;
		rank[x] = 0;
	}

	// Ѱ��x���ڼ��ϣ�����ʱѹ��·��
	int find_set(int x)
	{
		assert(x <= node_num);

		if (x != parent[x])
		{
			parent[x] = find_set(parent[x]);
		}
		return parent[x];
	}

	// ���Ⱥϲ�x��y���ڵļ���
	void union_set(int x, int y)
	{
		x = find_set(x);
		y = find_set(y);
		if (rank[x] > rank[y])
			parent[y] = x;
		else if (rank[x] < rank[y])
			parent[x] = y;
		else
		{
			parent[x] = y;
			rank[y]++;
		}
	}
};

void Test()
{
	const int k_node_num = 16;
	DisjointSet disjoint_set(k_node_num);

	for (int i = 1; i <= k_node_num; i++)
	{
		disjoint_set.make_set(i);
	}

	disjoint_set.union_set(2, 1);
	disjoint_set.union_set(3, 4);
	disjoint_set.union_set(1, 4);
	printf("disjoint_set.find_set(1) = %d\n", disjoint_set.find_set(1));

	printf("Parent:\n");
	for (int i = 1; i <= k_node_num; i++)
	{
		printf("%d ", disjoint_set.parent[i]);
	}
	printf("\n");
}

#endif // !DISJOINTSET_H
