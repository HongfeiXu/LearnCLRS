/*
 * 练习 16.2-2 设计动态规划算法求解 0-1 背包问题。
 * 要求运行时间为 O(nW)，n 为商品数量， W 是小偷能放进背包的最大商品总量。
 * 
 * 参考 http://www.cnblogs.com/yanlingyin/archive/2011/12/25/Knapsackproblem.html
 **/

#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
using std::max;

struct Goods{
	int id;
	int weight;
	int value;
}; 

int KnapsackProblem(Goods goods_list[], int n, int weight_max, int ** &m, int ** &aux)
{
	// 子问题 m[i,w] ： 用第 1,2,3,...,i 个物品装入重量最大为 w 的背包的最大价值。
	// 原问题即为 m[n, weight_max]
	
	// 动态分配数组 m[n+1][weight_max+1]
	m = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		m[i] = new int[weight_max + 1];
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < weight_max + 1; j++)
			m[i][j] = 0;  // 初始为 0

	// 辅助数组，用于记录 子问题 m[i,w] 最大价值背包中有没有放入 i，放入则记为 1，否则记为 0
	aux = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		aux[i] = new int[weight_max + 1];
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < weight_max; j++)
			aux[i][j] = 0;  // 初始为 0
	
	// 两种特殊子问题
	for (int i = 1; i <= n; i++)
		m[i][0] = 0;
	for (int w = 0; w <= weight_max; w++)
		m[0][w] = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int w = 1; w <= weight_max; w++)
		{
			if (goods_list[i].weight > w)
			{
				m[i][w] = m[i - 1][w];
				aux[i][w] = 0;
			}
			else
			{
				if (m[i - 1][w] >= m[i - 1][w - goods_list[i].weight] + goods_list[i].value)
				{
					m[i][w] = m[i - 1][w];
					aux[i][w] = 0;
				}
				else
				{
					m[i][w] = m[i - 1][w - goods_list[i].weight] + goods_list[i].value;
					aux[i][w] = 1;
				}
			}
		}
	}
	return m[n][weight_max];
}

void PrintResult(Goods goods_list[], int n, int weight_max, int ** &m, int ** &aux)
{
	int total_weight = weight_max;  // 最优解中背包中的实际总重量
	while (m[n][total_weight] == m[n][total_weight - 1])
	{
		total_weight--;
	}
	
	cout << "total_weight = " << total_weight << endl;

	while (total_weight > 0)
	{
		// 如果物品 n 在最优解中
		if (aux[n][total_weight] == 1)
		{
			cout << "goods " << n << " is in the bag" << endl;
			total_weight -= goods_list[n].weight;
			n--;
		}
		else
		{
			cout << "goods " << n << " is not in the bag" << endl;
			n--;
		}
	}
}

int main()
{
	const int kN = 5;          // 物品个数
	int weight_max = 15;       // 背包的容量
	Goods goods_list[kN + 1];  // GoodsList[1..kN] 为有效内容

	int weight_list[kN] = { 12, 1, 4, 1, 2 };
	int value_list[kN] = { 4, 2, 10, 1, 2 };

	for (int i = 0; i < kN; i++)
	{
		goods_list[i + 1].id = i + 1;
		goods_list[i + 1].weight = weight_list[i];
		goods_list[i + 1].value = value_list[i];
	}

	int ** m = nullptr;
	int ** aux = nullptr;
	int total_value = KnapsackProblem(goods_list, kN, weight_max, m, aux);

	cout << "best result: " << total_value << endl;
	PrintResult(goods_list, kN, weight_max, m, aux);

	return 0;
}

/*

best result: 15
total_weight = 8
goods 5 is in the bag
goods 4 is in the bag
goods 3 is in the bag
goods 2 is in the bag
请按任意键继续. . .

*/