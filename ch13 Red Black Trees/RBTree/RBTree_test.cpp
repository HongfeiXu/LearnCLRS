/***************************************************************************
*  @file       RBtree_test.cpp
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       6.2 2017
*  @remark     Test the functionality of RBTree template
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "myUtility.h"  // RandomizeInPlace()
#include "RBTree.h"

using ch13::RBTree;

// overload operator<<, so we can use OutputVec to print the infomation of *pNode
std::ostream& ch13::operator<< (std::ostream &os, const RBTree<int, std::string>::RBNode * pNode)
{
	os << pNode->key << " " << pNode->value;
	return os;
}

void ch13::RBTree_test()
{
	std::srand(unsigned(time(0)));

	RBTree<int, std::string> rbTree;
	std::vector<RBTree<int, std::string>::RBNode *> ptr_vec(8);
	ptr_vec[0] = new RBTree<int, std::string>::RBNode(1, "Cat");
	ptr_vec[1] = new RBTree<int, std::string>::RBNode(7, "Razor");
	ptr_vec[2] = new RBTree<int, std::string>::RBNode(5, "Grass");
	ptr_vec[3] = new RBTree<int, std::string>::RBNode(9, "Sun");
	ptr_vec[4] = new RBTree<int, std::string>::RBNode(3, "Apple");
	ptr_vec[5] = new RBTree<int, std::string>::RBNode(8, "Dog");
	ptr_vec[6] = new RBTree<int, std::string>::RBNode(2, "Knife");
	ptr_vec[7] = new RBTree<int, std::string>::RBNode(6, "Shark");

	std::cout << "Initial nodes:" << std::endl;
	OutputVec(ptr_vec, std::cout, ' ');
	RandomizeInPlace(ptr_vec);
	std::cout << "After Randomized:" << std::endl;
	OutputVec(ptr_vec, std::cout, ' ');

	for (auto &item : ptr_vec)
	{
		rbTree.insert(item);
	}
	std::cout << "inorderTreeWalk:" << std::endl;
	rbTree.inorderTreeWalk(std::cout);
	std::cout << "Tree: ";
	rbTree.printTree(std::cout);
	std::cout << std::endl;
	std::cout << "Tree BlackHeight: " << rbTree.treeBlackHeight() << std::endl;

	std::cout << "deleteNodeHasKey 8" << std::endl;  // if there are many nodes have key 8, only delete the node inseted firstly.
	rbTree.deleteNodeHasKey(8);
	std::cout << "inorderTreeWalk:" << std::endl;
	rbTree.inorderTreeWalk(std::cout);
	std::cout << "Tree: ";
	rbTree.printTree(std::cout);
	std::cout << std::endl;
	std::cout << "Tree BlackHeight: " << rbTree.treeBlackHeight() << std::endl;

	return;
}

/*

Initial nodes:
1 Cat 7 Razor 5 Grass 9 Sun 3 Apple 8 Dog 2 Knife 6 Shark
After Randomized:
5 Grass 3 Apple 8 Dog 1 Cat 9 Sun 2 Knife 6 Shark 7 Razor
inorderTreeWalk:
1 Cat  RED
2 Knife  BLACK
3 Apple  RED
5 Grass  BLACK
6 Shark  BLACK
7 Razor  RED
8 Dog  RED
9 Sun  BLACK
Tree: 5(2(1,3),8(6(,7),9))
Tree BlackHeight: 2
deleteNodeHasKey 8
inorderTreeWalk:
1 Cat  RED
2 Knife  BLACK
3 Apple  RED
5 Grass  BLACK
6 Shark  BLACK
7 Razor  RED
9 Sun  BLACK
Tree: 5(2(1,3),7(6,9))
Tree BlackHeight: 2
Press any key to continue . . .

*/