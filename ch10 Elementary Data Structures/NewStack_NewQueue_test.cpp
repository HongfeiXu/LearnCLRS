#include "NewStack_NewQueue.h"

int main()
{
	// test NewQueue
	NewQueue nq1;
	nq1.enqueue(1);
	nq1.enqueue(2);
	nq1.enqueue(3);
	nq1.dequeue();
	nq1.enqueue(4);

	while(!nq1.empty())
	{	
		std::cout << nq1.dequeue() << " ";
	}
	std::cout << std::endl;

	// test NewQueue_v2
	NewQueue_v2 nq_v2;
	nq_v2.enqueue(1);
	nq_v2.enqueue(2);
	nq_v2.enqueue(3);
	nq_v2.dequeue();
	nq_v2.enqueue(4);

	while(!nq_v2.empty())
	{
		std::cout << nq_v2.dequeue() << " ";
	}
	std::cout << std::endl;


	// test NewStack
	NewStack ns1;
	ns1.push(1);
	ns1.push(2);
	ns1.push(3);
	ns1.pop();
	ns1.push(4);

	while(!ns1.empty())
	{
		std::cout << ns1.pop() << " ";
	}
	std::cout << std::endl;

	return 0;
}

/*

2 3 4
2 3 4
4 2 1
Press any key to continue . . .

*/