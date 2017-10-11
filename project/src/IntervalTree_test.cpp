/***************************************************************************
*  @file       IntervalTree_test.cpp
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       7.6 2017
*  @remark     Test the functionality of IntervalTree template
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "myUtility.h"  // RandomizeInPlace()
#include "IntervalTree.h"

using ch14_2::IntervalTree;

// overload operator<<, so we can use OutputVec to print the infomation of *pNode
std::ostream& ch14_2::operator<< (std::ostream &os, const IntervalTree<int, std::string>::IntervalNode * pNode)
{
	os << "key: "<<pNode->key << " interval: (" <<  pNode->interval.first << "," << pNode->interval.second << ")" << " value: " << pNode->value << " max:" << pNode->max;
	return os;
}

void ch14_2::IntervalTree_test()
{
	std::srand(unsigned(time(0)));

	IntervalTree<int, std::string> intervalTree;


	std::vector<IntervalTree<int, std::string>::IntervalNode *> ptr_vec(8);
	ptr_vec[0] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(0,3), "Cat");
	ptr_vec[1] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(5,8), "Razor");
	ptr_vec[2] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(6,10), "Grass");
	ptr_vec[3] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(8,9), "Sun");
	ptr_vec[4] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(15,23), "Apple");
	ptr_vec[5] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(16,21), "Dog");
	ptr_vec[6] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(17,19), "Knife");
	ptr_vec[7] = new IntervalTree<int, std::string>::IntervalNode(std::make_pair(25,30), "Shark");

	std::cout << "Initial nodes:" << std::endl;
	OutputVec(ptr_vec, std::cout, '\n');
	//RandomizeInPlace(ptr_vec);
	//std::cout << "After Randomized:" << std::endl;
	//OutputVec(ptr_vec, std::cout, ' ');

	for (auto &item : ptr_vec)
		intervalTree.insert(item);

	std::cout << "inorderTreeWalk:" << std::endl;
	intervalTree.inorderTreeWalk(std::cout);

	std::cout << "Tree: ";
	intervalTree.printTree(std::cout);
	std::cout << std::endl;

	std::cout << "deleteNodeHasKey 8" << std::endl;  // if there are many nodes have key 8, only delete the node inseted firstly.
	intervalTree.deleteNodeHasKey(8);
	std::cout << "inorderTreeWalk:" << std::endl;
	intervalTree.inorderTreeWalk(std::cout);
	std::cout << "Tree: ";
	intervalTree.printTree(std::cout);
	std::cout << std::endl;

	// test intervalSearch

	std::pair<int, int> interval_a(8, 9);
	IntervalTree<int, std::string>::IntervalNode * pInterval_a = intervalTree.intervalSearch(interval_a);
	std::cout << pInterval_a << std::endl;
	

	return;
}

/*

Initial nodes:
key: 0 interval: (0,3) value: Cat max:0
key: 5 interval: (5,8) value: Razor max:0
key: 6 interval: (6,10) value: Grass max:0
key: 8 interval: (8,9) value: Sun max:0
key: 15 interval: (15,23) value: Apple max:0
key: 16 interval: (16,21) value: Dog max:0
key: 17 interval: (17,19) value: Knife max:0
key: 25 interval: (25,30) value: Shark max:0
inorderTreeWalk:
key: 0 interval: (0,3) value:Cat max:3  BLACK
key: 5 interval: (5,8) value:Razor max:10  RED
key: 6 interval: (6,10) value:Grass max:10  BLACK
key: 8 interval: (8,9) value:Sun max:30  BLACK
key: 15 interval: (15,23) value:Apple max:23  BLACK
key: 16 interval: (16,21) value:Dog max:30  RED
key: 17 interval: (17,19) value:Knife max:30  BLACK
key: 25 interval: (25,30) value:Shark max:30  RED
Tree: 8(5(0,6),16(15,17(,25)))
deleteNodeHasKey 8
inorderTreeWalk:
key: 0 interval: (0,3) value:Cat max:3  BLACK
key: 5 interval: (5,8) value:Razor max:10  RED
key: 6 interval: (6,10) value:Grass max:10  BLACK
key: 15 interval: (15,23) value:Apple max:30  BLACK
key: 16 interval: (16,21) value:Dog max:21  BLACK
key: 17 interval: (17,19) value:Knife max:30  RED
key: 25 interval: (25,30) value:Shark max:30  BLACK
Tree: 15(5(0,6),17(16,25))
key: 5 interval: (5,8) value: Razor max:10
请按任意键继续. . .


*/