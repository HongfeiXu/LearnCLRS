/*
说明如何在一个数组 A[1..n] 中实现两个栈，是的当两个栈的元素之和不为 n 时，两者都不会发生上溢。
要求 PUSH 和 POP 操作的运行时间为 BigO(1)

思想：将数组的两头，分别作为两个栈的栈底。左边的栈压栈操作向右边前进，右边的栈压栈操作向左边前进。出栈操作同理。
*/

#include <iostream>

const int STACKBUFFERSIZE = 10;
class TwoStacks
{
public:
	bool emptyS0()
	{
		if(count0 == 0)
			return true;
		else
			return false;
	}
	bool emptyS1()
	{
		if(count1 == 0)
			return true;
		else
			return false;
	}
	void pushS0(int x)
	{
		if(top0 + 1 == top1)
		{
			std::cerr << "TwoStacks S0 overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			top0++;
			buffer[top0] = x;
			count0++;
		}
	}
	int popS0()
	{
		if(count0 == 0)
		{
			std::cerr << "TwoStacks S0 underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			top0--;
			count0--;
			return buffer[top0 + 1];
		}
	}
	void pushS1(int x)
	{
		if(top1 - 1 == top0)
		{
			std::cerr << "TwoStacks S1 overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			top1--;
			buffer[top1] = x;
			count1++;
		}
	}
	int popS1()
	{
		if(count1 == 0)
		{
			std::cerr << "TwoStacks S1 underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			top1++;
			count1--;
			return buffer[top1 - 1];
		}
	}
	int sizeS0()
	{
		return count0;
	}
	int sizeS1()
	{
		return count1;
	}
private:
	int buffer[STACKBUFFERSIZE + 1];
	int count0 = 0;
	int top0 = 0;
	int count1 = 0;
	int top1 = STACKBUFFERSIZE + 1;
};

int main()
{
	TwoStacks twoS;
	twoS.pushS0(1);
	twoS.pushS0(2);
	twoS.pushS0(3);
	twoS.pushS0(4);

	twoS.pushS1(5);
	twoS.pushS1(6);
	twoS.pushS1(7);

	twoS.pushS0(8);
	twoS.pushS0(9);
	
	twoS.pushS1(10);

	twoS.popS0();

	twoS.popS1();
	twoS.popS1();

	std::cout << "S0:" << std::endl;
	while(!twoS.emptyS0())
	{
		std::cout << twoS.popS0() << " ";
	}
	std::cout << std::endl;

	std::cout << "S1:" << std::endl;
	while(!twoS.emptyS1())
	{
		std::cout << twoS.popS1() << " ";
	}
	std::cout << std::endl;

	return 0;
}

/*

S0:
8 4 3 2 1
S1:
6 5
Press any key to continue . . .

*/