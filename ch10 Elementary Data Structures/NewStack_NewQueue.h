#pragma once

/*
˵�����������ջʵ��һ�����У���������ض��в���������ʱ�䡣
˼·��stack1 stack2���� stack1 ��������ӵ�Ԫ�أ�
ÿ��Ҫ����ʱ���Ƚ� stack1 ������Ԫ��ȫ������ѹ�뵽 stack2 �У�
Ȼ�󵯳� stack2 ��ջ��Ԫ����ɳ��ӣ�����ٽ� stack2 �е�����Ԫ��ȫ������ѹ�뵽 stack1 �С�
�ɴ˿ɼ� stack2 ��������һ�����򱣴�����á�

˼·2����������˼·���ã���stack1 stack2���� stack1 ������ӵ�Ԫ�أ�
ÿ��Ҫ����ʱ���ȼ�� stack2 �Ƿ�Ϊ�գ����Ϊ�գ����Ƚ� stack1 �е�Ԫ��ȫ������ѹ�� stack2 �У�Ȼ�� stack2 ��ջһ��Ԫ����ɳ��Ӳ�����
��� stack2 �ǿգ���ֱ�ӳ�ջһ��Ԫ����ɳ��Ӳ������ɡ�
˼·2�У�����Ҫ�� stack2 �е�Ԫ���ڵ���ѹ�� stack1����ʡ�˺ܶ�εĲ�����


˵���������������ʵ��һ��ջ����������ز���������ʱ�䡣
˼�룺�������� queue1 queue2����ջ��������ǿյ��Ǹ����У�����Ϊ queue1������Ӹ�Ԫ�ء�
��ջ���������ǿն��У�queue1���ĳ����һ��Ԫ��֮������Ԫ�س��ӵ��ն��� queue2�У��ٽ� queue1 ��ʣ���Ǹ�Ԫ�س�����Ϊ��ջԪ�ء�
ע���ڴ˹����У��� push ������Ԫ�����ǲ��뵽һ���ǿն��У������ʼ�������о�Ϊ�գ���
�ն����������� pop ����֮�����ЩԪ�أ���ʱ�ն��в�Ϊ�գ�ԭ���ķǿն��б���ˣ�ѭ��������
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