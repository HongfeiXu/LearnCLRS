# �� 10 �� �������ݽṹ

## 10.1 ջ�Ͷ���

����������ü򵥵�����ʵ�����������ݽṹ��

### 10.1.1 ջ

������һ������ S[1..n] ��ʵ��һ��������� n ��Ԫ�ص�ջ����������һ������ S.top��ָ�����²����Ԫ�ء�ջ�а�����Ԫ��Ϊ S[1..S.top]������ S[1] ��ջ��Ԫ�أ��� S[S.top] ��ջ��Ԫ�ء�

α����

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

### 10.1.2 ����

�������� Q[1..n] ��ʵ��һ��������� n-1 ��Ԫ�صĶ��С��ö�����һ������ Q.head ָ���ͷԪ�ء������� Q.tail ��ָ����һ����Ԫ��Ҫ�����λ�á������е�Ԫ�ش����λ�� Q.head��Q.head+1��...��Q.tail-1����������λ���γɡ����ơ���  
�� Q.head == Q.tail ʱ������Ϊ�ա���ʼʱ�� Q.head = Q.tail = 1��  
�� Q.head == Q.tail + 1 (mod n) ʱ�����������ġ�

α����

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

### 10.1.3 ջ�Ͷ��е�C++ʵ��

[Stack_Queue](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch10/Stack_Queue.h)

### 10.1.4 ��ϰ

10.1-2 ˵�������һ������ A[1..n] ��ʵ������ջ���ǵĵ�����ջ��Ԫ��֮�Ͳ�Ϊ n ʱ�����߶����ᷢ�����硣
Ҫ�� PUSH �� POP ����������ʱ��Ϊ BigO(1)  

�㷨˼�뼰C++ʵ�֣�[OneArrayTwoStacks]()

10.1-6 ˵�����������ջʵ��һ�����У���������ض��в���������ʱ�䡣  
10.1-7 ˵���������������ʵ��һ��ջ����������ز���������ʱ�䡣

�㷨˼�뼰C++ʵ�֣�[NewStack_NewQueue.h]()

## 10.2 ����

