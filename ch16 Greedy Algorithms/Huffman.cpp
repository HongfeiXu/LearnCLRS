#include "Huffman.h"

void InitNodes(priority_queue<HuffmanNode> &q, int node_num)
{
	char c;
	int frequence;
	for (int i = 0; i < node_num; i++)
	{
		cout << "Please input character and frequence" << endl;
		cin >> c >> frequence;
		HuffmanNode h_node(c, frequence);
		q.push(h_node);
	}
}

void ShowNodes(priority_queue<HuffmanNode> &q)
{
	while (!q.empty())
	{
		HuffmanNode h_node = q.top();
		q.pop();
		cout << h_node.c << ", " << h_node.frequence << endl;
	}
}

void ConstructHuffmanTree(priority_queue<HuffmanNode> &q)
{
	while (q.size() != 1)
	{
		HuffmanNode *lchild = new HuffmanNode(q.top());
		q.pop();
		HuffmanNode *rchild = new HuffmanNode(q.top());
		q.pop();

		q.push(HuffmanNode('R', lchild->frequence + rchild->frequence, lchild, rchild));
	}
}

void HuffmanCode(HuffmanNode *root, string &prefix, map<char, string> &results)
{
	string prefix_bak = prefix;

	if (root->lchild == nullptr)
		return;

	// handle left sub tree
	prefix += "0";
	// 如果是叶节点则输出，否则递归打印左子树
	if (root->lchild->lchild == nullptr)
		results[root->lchild->c] = prefix;
	else
		HuffmanCode(root->lchild, prefix, results);

	prefix = prefix_bak;

	// handle right sub tree
	prefix += "1";
	// 如果是叶节点则输出，否则递归打印右子树
	if (root->rchild->rchild == nullptr)
		results[root->rchild->c] = prefix;
	else
		HuffmanCode(root->rchild, prefix, results);
}

void ShowResults(const map<char, string> &results)
{
	for (auto it = results.begin(); it != results.end(); it++)
	{
		cout << it->first << ", " << it->second << endl;
	}
}

void HuffmanTest()
{
	priority_queue<HuffmanNode> q;
	InitNodes(q, 6);
	//ShowNodes(q);
	
	ConstructHuffmanTree(q);
	HuffmanNode *root = &q.top();
	string prefix = "";
	map<char, string> results;
	HuffmanCode(root, prefix, results);
	ShowResults(results);
}

/*

Please input character and frequence
f 5
Please input character and frequence
e 9
Please input character and frequence
c 12
Please input character and frequence
b 13
Please input character and frequence
d 16
Please input character and frequence
a 45
a, 0
b, 101
c, 100
d, 111
e, 1101
f, 1100
请按任意键继续. . .

*/