/*
��һ������ S[1..n] ��ʵ��һ��������� n ��Ԫ�ص�ջ

```
STACK-EMPTY(S)
if S.top == 0
return TRUE
else return FALSE
```

```
PUSH(S, x)
S.top = S.top + 1
S[S.top] = x
```

```
POP(S)
if STACK-EMPTY(S)
error "underflow"
else
S.top = S.top - 1
return S[S.top + 1]
```

Q[1..n] ��ʵ��һ��������� n-1 ��Ԫ�صĶ��С��ö�����һ������ Q.head ָ���ͷԪ�ء������� Q.tail ��ָ����һ����Ԫ��Ҫ�����λ�á�
�����е�Ԫ�ش����λ�� Q.head��Q.head+1��...��Q.tail-1����������λ���γɡ����ơ���

```
ENQUEUE(Q, x)
Q[Q.tail] = x
if Q.tail == Q.length
Q.tail = 1
else
Q.tail = Q.tail + 1
```

```
DEQUEUE(Q)
x = Q[Q.head]
if Q.head == Q.length
Q.head = 1
else
Q.head = Q.head + 1
return x
```
*/

#include <iostream>

const int STACKSIZE = 20;
class MyStack
{
public:
	bool empty()
	{
		if(top == 0)
			return true;
		else
			return false;
	}
	void push(int x)
	{
		if(top == STACKSIZE)
		{
			std::cerr << "stack overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			buffer[++top] = x;
		}
	}
	int pop()
	{
		if(empty())
		{
			std::cerr << "stack underflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			--top;
			return buffer[top + 1];
		}
	}

private:
	int buffer[STACKSIZE + 1];  // buffer[1..STACKSIZE] �洢��ЧԪ��
	int top = 0;
};

const int QUEUESIZE = 20;
class MyQueue
{
public:
	bool empty()
	{
		if(head == tail)
			return true;
		else
			return false;
	}
	void enqueue(int x)
	{
		if(tail == QUEUESIZE && 1 == head || tail + 1 == head)
		{
			std::cerr << "queue overflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			buffer[tail] = x;
			if(tail == QUEUESIZE)
				tail = 1;
			else
				tail++;
		}
	}
	int dequeue()
	{
		if(empty())
		{
			std::cerr << "queue undeflow" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			int x = buffer[head];
			if(head == QUEUESIZE)
				head = 1;
			else
				head++;
			return x;
		}
	}

private:
	int buffer[QUEUESIZE + 1];
	int head = 1;
	int tail = 1;
};

/*
// test
int main()
{
	// test MyStack
	MyStack ms1;

	ms1.push(1);
	ms1.push(2);
	ms1.push(3);
	ms1.pop();
	ms1.push(4);

	std::cout << "MyStack ms1:\n";
	while(!ms1.empty())
	{
		std::cout << ms1.pop() << " ";
	}
	std::cout << std::endl;

	// test MyQueue
	MyQueue mq1;

	mq1.enqueue(1);
	mq1.enqueue(2);
	mq1.enqueue(3);
	mq1.dequeue();
	mq1.enqueue(4);
	
	std::cout << "MyQueue mq1:\n";
	while(!mq1.empty())
	{
		std::cout << mq1.dequeue() << " ";
	}
	std::cout << std::endl;

	return 0;
}
*/

/*

MyStack ms1:
4 2 1
MyQueue mq1:
2 3 4
Press any key to continue . . .

*/