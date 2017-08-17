/***************************************************************************
*  @file       Huffman.h
*  @author     ice-mj
*  @mail       icevmj@gmail.com
*  @date       8.17 2017
*  @platform   visual studio 2015, windows 10
***************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <map>
#include <queue>
#include <iostream>

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::cin;
using std::priority_queue;

class HuffmanNode {
public:
	char c;
	int frequence;
	HuffmanNode *lchild;
	HuffmanNode *rchild;

public:
	~HuffmanNode() { }
	HuffmanNode(char c_, int frequence_, HuffmanNode *lchild_ = nullptr, HuffmanNode *rchild_ = nullptr)
		: c(c_), frequence(frequence_), lchild(lchild_), rchild(rchild_) { }

	// 重载 < ，为了构造 priority_queue 时，frequence 越小，优先级越高
	bool operator<(const HuffmanNode &h_node) const
	{
		return this->frequence > h_node.frequence;
	}
};

// 用 HuffmanNode 初始化优先级队列
void InitNodes(priority_queue<HuffmanNode> &q, int node_num);

// 输出优先级队列中的所有元素
void ShowNodes(priority_queue<HuffmanNode> &q);

// 构造 HuffmanTree
void ConstructHuffmanTree(priority_queue<HuffmanNode> &q);

// 得到 HuffmanCode
void HuffmanCode(HuffmanNode *root, string &prefix, map<char, string> &results);

// 输出 HuffmanCode 的结果
void ShowResults(const map<char, string> &results);

// 测试
void HuffmanTest();



#endif // !HUFFMAN_H
