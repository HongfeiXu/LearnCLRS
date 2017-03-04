#pragma once

/*
说明如何用两个栈实现一个队列，并分析相关队列操作的运行时间。
思路：stack1 stack2，用 stack1 来保存入队的元素，
每当要出队时，先将 stack1 的所有元素全部弹出压入到 stack2 中，
然后弹出 stack2 的栈顶元素完成出队，最后，再将 stack2 中的余下元素全部弹出压入到 stack1 中。
由此可见 stack2 在这里起到一个逆序保存的作用。

思路2（相比上面的思路更好）：stack1 stack2，用 stack1 保存入队的元素，
每当要出队时，先检查 stack2 是否为空，如果为空，则先将 stack1 中的元素全部弹出压入 stack2 中，然后 stack2 出栈一个元素完成出队操作。
如果 stack2 非空，则直接出栈一个元素完成出队操作即可。
思路2中，不需要将 stack2 中的元素在弹出压入 stack1，节省了很多次的操作。


说明如何用两个队列实现一个栈，并分析相关操作的运行时间。
思想：两个队列 queue1 queue2，入栈操作：向非空的那个队列（假设为 queue1）中入队该元素。
出栈操作：将非空队列（queue1）的除最后一个元素之外所有元素出队到空队列 queue2中，再将 queue1 的剩下那个元素出队作为出栈元素。
注：在此过程中，新 push 进来的元素总是插入到一个非空队列（除了最开始两个队列均为空），
空队列用来保存 pop 操作之后的那些元素，此时空队列不为空，原来的非空队列变空了，循环往复。
*/

#include "Stack_Queue.h"
class NewStack
{
public:
	bool empty()
	{
		if(count == 0)
			return true;
		else
			return false;
	}
	void push(int x)
	{
		if(!queue0.empty())
		{
			if(queue0.full())
			{
				std::cerr << "NewStack overflow" << std::endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				queue0.enqueue(x);
				count++;
			}
		}
		else
		{
			if(queue0.full())
			{
				std::cerr << "NewStack overflow" << std::endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				queue1.enqueue(x);
				count++;
			}
		}
	}
	int pop()
	{
		if(empty())
		{
			std::cerr << "NewStack underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			if(!queue0.empty())
			{
				while(queue0.size() != 1)
				{
					queue1.enqueue(queue0.dequeue());
				}
				count--;
				return queue0.dequeue();
			}
			else
			{
				while(queue1.size() != 1)
				{
					queue0.enqueue(queue1.dequeue());
				}
				count--;
				return queue1.dequeue();
			}
		}
	}
	int size()
	{
		return count;
	}
private:
	MyQueue queue0;
	MyQueue queue1;
	int count = 0;
};

class NewQueue
{
public:
	bool empty()
	{
		if(count == 0)
			return true;
		else
			return false;
	}
	void enqueue(int x)
	{
		if(stack0.full())
		{
			std::cerr << "NewQueue overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			stack0.push(x);
			count++;
		}
	}
	int dequeue()
	{
		if(stack0.empty())
		{
			std::cerr << "NewQueue underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			while(!stack0.empty())
			{
				stack1.push(stack0.pop());
			}
			int x = stack1.pop();
			while(!stack1.empty())
			{
				stack0.push(stack1.pop());
			}
			count--;
			return x;
		}
	}
	int size()
	{
		return count;
	}
private:
	MyStack stack0;  // enqueue
	MyStack stack1;  // dequeue
	int count = 0;
};

class NewQueue_v2
{
public:
	bool empty()
	{
		if(count == 0)
			return true;
		else
			return false;
	}
	void enqueue(int x)
	{
		if(stack0.full())
		{
			std::cerr << "NewQueue_v2 overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			stack0.push(x);
			count++;
		}
	}
	int dequeue()
	{
		if(empty())
		{
			std::cerr << "NewQueue_v2 underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			if(!stack1.empty())
			{
				count--;
				return stack1.pop();
			}
			else
			{
				while(!stack0.empty())
				{
					stack1.push(stack0.pop());
				}
				count--;
				return stack1.pop();
			}
		}
	}
	int size()
	{
		return count;
	}
private:
	MyStack stack0;
	MyStack stack1;
	int count = 0;
};