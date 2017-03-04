# 第 10 章 基本数据结构

## 10.1 栈和队列

介绍如何利用简单的数组实现这两种数据结构。

### 10.1.1 栈

可以用一个数组 S[1..n] 来实现一个最多容纳 n 个元素的栈。该数组有一个属性 S.top，指向最新插入的元素。栈中包含的元素为 S[1..S.top]，其中 S[1] 是栈底元素，而 S[S.top] 是栈顶元素。

伪代码

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

### 10.1.2 队列

利用数组 Q[1..n] 来实现一个最多容纳 n-1 个元素的队列。该队列有一个属性 Q.head 指向队头元素。而属性 Q.tail 则指向下一个新元素要插入的位置。队列中的元素存放在位置 Q.head，Q.head+1，...，Q.tail-1，并在最后的位置形成“环绕”。  
当 Q.head == Q.tail 时，队列为空。初始时有 Q.head = Q.tail = 1。  
当 Q.head == Q.tail + 1 (mod n) 时，队列是满的。

伪代码

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

### 10.1.3 栈和队列的C++实现

[Stack_Queue](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch10/Stack_Queue.h)

### 10.1.4 练习

10.1-2 说明如何在一个数组 A[1..n] 中实现两个栈，是的当两个栈的元素之和不为 n 时，两者都不会发生上溢。
要求 PUSH 和 POP 操作的运行时间为 BigO(1)  

算法思想及C++实现：[OneArrayTwoStacks]()

10.1-6 说明如何用两个栈实现一个队列，并分析相关队列操作的运行时间。  
10.1-7 说明如何用两个队列实现一个栈，并分析相关操作的运行时间。

算法思想及C++实现：[NewStack_NewQueue.h]()

## 10.2 链表

