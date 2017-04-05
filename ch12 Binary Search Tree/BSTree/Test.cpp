#include <iostream>
#include <string>
#include "BSTree.h"

int main()
{
	BSTree<int, std::string> bstree;
	typename BSTree<int, std::string>::BSTNode arr[] = { {3, "Hello"}, {1, "World"}, {8, "WOW"}, {2, "Tree"}, {6, "Binary"}, {7, "Search"}, {5, "Node"} };
	for (auto &item : arr)
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

	return 0;
}


/*

1 World
2 Tree
3 Hello
5 Node
6 Binary
7 Search
8 WOW

2 Tree
1 World
5 Node
7 Search
6 Binary
8 WOW
3 Hello

6 founded
7 founded
The minimum elem in the tree:
1
The maximum elem in the tree:
8
The successor of 3 is 5
The predecessor of 3 is 1
Press any key to continue . . .

*/
