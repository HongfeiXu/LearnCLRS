/***************************************************************************
*  @file       RBtree_test.cpp
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       7.5 2017
*  @remark     Test the functionality of OSTree template
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "myUtility.h"  // RandomizeInPlace()
#include "OSTree.h"

using ch14::OSTree;

// overload operator<<, so we can use OutputVec to print the infomation of *pNode
std::ostream& ch14::operator<< (std::ostream &os, const OSTree<int, std::string>::OSNode * pNode)
{
	os << "key: " << pNode->key << " value:" << pNode->value << " size:" << pNode->size;
	return os;
}

void ch14::OSTree_test()
{
	std::srand(unsigned(time(0)));

	OSTree<int, std::string> osTree;
	std::vector<OSTree<int, std::string>::OSNode *> ptr_vec(8);
	ptr_vec[0] = new OSTree<int, std::string>::OSNode(1, "Cat");
	ptr_vec[1] = new OSTree<int, std::string>::OSNode(7, "Razor");
	ptr_vec[2] = new OSTree<int, std::string>::OSNode(5, "Grass");
	ptr_vec[3] = new OSTree<int, std::string>::OSNode(9, "Sun");
	ptr_vec[4] = new OSTree<int, std::string>::OSNode(3, "Apple");
	ptr_vec[5] = new OSTree<int, std::string>::OSNode(8, "Dog");
	ptr_vec[6] = new OSTree<int, std::string>::OSNode(2, "Knife");
	ptr_vec[7] = new OSTree<int, std::string>::OSNode(6, "Shark");

	std::cout << "Initial nodes:" << std::endl;
	OutputVec(ptr_vec, std::cout, '\n');
	RandomizeInPlace(ptr_vec);
	std::cout << "After Randomized:" << std::endl;
	OutputVec(ptr_vec, std::cout, '\n');

	for (auto &item : ptr_vec)
	{
		osTree.insert(item);

	}
	std::cout << "inorderTreeWalk:" << std::endl;
	osTree.inorderTreeWalk(std::cout);

	std::cout << "Tree: ";
	osTree.printTree(std::cout);
	std::cout << std::endl;

	OSTree<int, std::string>::OSNode *p = osTree.osSelect(7);
	std::cout << p->key << " " << p->value << std::endl;

	unsigned r = osTree.osRank(p);
	std::cout << "rank of p = " << r << std::endl;

	std::cout << "deleteNodeHasKey 8" << std::endl;  // if there are many nodes have key 8, only delete the node inseted firstly.
	osTree.deleteNodeHasKey(8);
	std::cout << "inorderTreeWalk:" << std::endl;
	osTree.inorderTreeWalk(std::cout);
	std::cout << "Tree: ";
	osTree.printTree(std::cout);
	std::cout << std::endl;

	return;
}

/*

Initial nodes:
1 Cat s:1 |  7 Razor s:1 |  5 Grass s:1 |  9 Sun s:1 |  3 Apple s:1 |  8 Dog s:1 |  2 Knife s:1 |  6 Shark s:1 |
After Randomized:
3 Apple s:1 |  9 Sun s:1 |  1 Cat s:1 |  8 Dog s:1 |  2 Knife s:1 |  5 Grass s:1 |  6 Shark s:1 |  7 Razor s:1 |
inorderTreeWalk:
1 Cat s:2  BLACK
2 Knife s:1  RED
3 Apple s:8  BLACK
5 Grass s:1  RED
6 Shark s:3  BLACK
7 Razor s:1  RED
8 Dog s:5  RED
9 Sun s:1  BLACK
Tree: 3(1(,2),8(6(5,7),9))
8 Dog
rank of p = 7
deleteNodeHasKey 8
inorderTreeWalk:
1 Cat s:2  BLACK
2 Knife s:1  RED
3 Apple s:7  BLACK
5 Grass s:1  BLACK
6 Shark s:4  RED
7 Razor s:1  RED
9 Sun s:2  BLACK
Tree: 3(1(,2),6(5,9(7,)))
请按任意键继续. . .

*/