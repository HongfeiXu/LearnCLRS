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

	// ���� < ��Ϊ�˹��� priority_queue ʱ��frequence ԽС�����ȼ�Խ��
	bool operator<(const HuffmanNode &h_node) const
	{
		return this->frequence > h_node.frequence;
	}
};

// �� HuffmanNode ��ʼ�����ȼ�����
void InitNodes(priority_queue<HuffmanNode> &q, int node_num);

// ������ȼ������е�����Ԫ��
void ShowNodes(priority_queue<HuffmanNode> &q);

// ���� HuffmanTree
void ConstructHuffmanTree(priority_queue<HuffmanNode> &q);

// �õ� HuffmanCode
void HuffmanCode(HuffmanNode *root, string &prefix, map<char, string> &results);

// ��� HuffmanCode �Ľ��
void ShowResults(const map<char, string> &results);

// ����
void HuffmanTest();



#endif // !HUFFMAN_H
