#include <iostream>
#include <string>
#include <vector>

#include "myUtility.h"  // RandomizeInPlace()
#include "BSTree.h"

// жиди typename BSTree<int, std::string>::BSTNode * ЕФ << 
std::ostream & operator<< (std::ostream &os, const typename BSTree<int, std::string>::BSTNode * pNode)
{
	os << pNode->key << " " << pNode->value;
	return os;
}

int main()
{
	BSTree<int, std::string> bstree;
	std::vector<typename BSTree<int, std::string>::BSTNode *> ptr_vec(7);
	ptr_vec[0] = new BSTree<int, std::string>::BSTNode(3, "Hello");
	ptr_vec[1] = new BSTree<int, std::string>::BSTNode(1, "World");
	ptr_vec[2] = new BSTree<int, std::string>::BSTNode(8, "WOW");
	ptr_vec[3] = new BSTree<int, std::string>::BSTNode(2, "Tree");
	ptr_vec[4] = new BSTree<int, std::string>::BSTNode(6, "Binary");
	ptr_vec[5] = new BSTree<int, std::string>::BSTNode(7, "Search");
	ptr_vec[6] = new BSTree<int, std::string>::BSTNode(5, "Node");

	OutputVec(ptr_vec, std::cout, ' ');
	RandomizeInPlace(ptr_vec);
	OutputVec(ptr_vec, std::cout, ' ');

	for (auto &item : ptr_vec)
	{
		bstree.insert(item);
	}

	bstree.inorderTreeWalk(std::cout);
	std::cout << std::endl;
	bstree.postorderTreeWalk(std::cout);
	std::cout << std::endl;


	if (bstree.find(6))
		std::cout << "6 founded" << std::endl;
	if (bstree.find(-1))
		std::cout << "-1 founded" << std::endl;

	if (bstree.search(7) != nullptr)
		std::cout << "7 founded" << std::endl;

	std::cout << "The minimum elem in the tree:" << std::endl;
	std::cout << bstree.minimum()->key << std::endl;
	std::cout << "The maximum elem in the tree:" << std::endl;
	std::cout << bstree.maximum()->key << std::endl;

	auto curr_node = bstree.search(3);
	auto succ_node = bstree.successor(curr_node);
	if (succ_node != nullptr)
	{
		std::cout << "The successor of 3 is " << succ_node->key << std::endl;
	}

	auto pred_node = bstree.predecessor(curr_node);
	if (pred_node != nullptr)
	{
		std::cout << "The predecessor of 3 is " << pred_node->key << std::endl;
	}

	bstree.deleteNodeHasKey(8);
	bstree.inorderTreeWalk(std::cout);
	std::cout << "Height of the tree: "<<bstree.treeHeight() << std::endl;

	return 0;
}