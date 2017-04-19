/***************************************************************************
*  @file       Test.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       4.19 2016
*  @remark     Test the functionality of BSTree template
***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "myUtility.h"  // RandomizeInPlace()
#include "BSTree.h"

// overload operator<<, so we can use OutputVec to print the infomation of *pNode
std::ostream & operator<< (std::ostream &os, const typename BSTree<int, std::string>::BSTNode * pNode)
{
	os << pNode->key << " " << pNode->value;
	return os;
}

int main()
{
	std::srand(unsigned(time(0)));

	BSTree<int, std::string> bstree;
	std::vector<typename BSTree<int, std::string>::BSTNode *> ptr_vec(8);
	ptr_vec[0] = new BSTree<int, std::string>::BSTNode(3, "Hello");
	ptr_vec[1] = new BSTree<int, std::string>::BSTNode(1, "World");
	ptr_vec[2] = new BSTree<int, std::string>::BSTNode(8, "WOW");
	ptr_vec[3] = new BSTree<int, std::string>::BSTNode(2, "Tree");
	ptr_vec[4] = new BSTree<int, std::string>::BSTNode(6, "Binary");
	ptr_vec[5] = new BSTree<int, std::string>::BSTNode(7, "Search");
	ptr_vec[6] = new BSTree<int, std::string>::BSTNode(5, "Node");
	ptr_vec[7] = new BSTree<int, std::string>::BSTNode(6, "Another Binary");

	std::cout << "Initial nodes:" << std::endl;
	OutputVec(ptr_vec, std::cout, ' ');
	RandomizeInPlace(ptr_vec);
	std::cout << "After Randomized:" << std::endl;
	OutputVec(ptr_vec, std::cout, ' ');
	for (auto &item : ptr_vec)
	{
		bstree.insert(item);
	}
	std::cout << "inorderTreeWalk:" << std::endl;
	bstree.inorderTreeWalk(std::cout);

	if (bstree.find(6))
		std::cout << "node with key 6 founded" << std::endl;
	if (bstree.find(-1))
		std::cout << "node with key -1 founded" << std::endl;
	if (bstree.search(7) != nullptr)
		std::cout << "node with key 7 founded" << std::endl;

	std::cout << "The minimum elem in the tree:";
	std::cout << bstree.minimum()->key << std::endl;
	std::cout << "The maximum elem in the tree:";
	std::cout << bstree.maximum()->key << std::endl;

	auto curr_node = bstree.search(3);
	auto succ_node = bstree.successor(curr_node);
	if (succ_node != nullptr)
	{
		std::cout << "The successor of node with key 3 is " << succ_node->key << std::endl;
	}

	auto pred_node = bstree.predecessor(curr_node);
	if (pred_node != nullptr)
	{
		std::cout << "The predecessor of node with key 3 is " << pred_node->key << std::endl;
	}
	std::cout << "deleteNodeHasKey 8" << std::endl;  // if there are many nodes have key 8, only delete the node inseted firstly.
	bstree.deleteNodeHasKey(8);
	std::cout << "inorderTreeWalk:" << std::endl;
	bstree.inorderTreeWalk(std::cout);
	std::cout << "Height of the tree: "<<bstree.treeHeight() << std::endl;

	return 0;
}

/*

Initial nodes:
3 Hello 1 World 8 WOW 2 Tree 6 Binary 7 Search 5 Node 6 Another Binary
After Randomized:
7 Search 6 Binary 2 Tree 5 Node 3 Hello 6 Another Binary 1 World 8 WOW
inorderTreeWalk:
1 World
2 Tree
3 Hello
5 Node
6 Binary
6 Another Binary
7 Search
8 WOW
node with key 6 founded
node with key 7 founded
The minimum elem in the tree:1
The maximum elem in the tree:8
The successor of node with key 3 is 5
The predecessor of node with key 3 is 2
deleteNodeHasKey 8
inorderTreeWalk:
1 World
2 Tree
3 Hello
5 Node
6 Binary
6 Another Binary
7 Search
Height of the tree: 5
Press any key to continue . . .

*/