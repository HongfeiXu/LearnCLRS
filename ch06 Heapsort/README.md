# �� 6 �� ������

## 6.1 ��

### һЩ����

#### a. ��  

**�ѵı�����һ��������������±��1��ʼ��**

�ѿ��Ա�����һ��**��ȫ������**���������Ĳ�α������������Ԫ�ص�˳���Ӧ������ΪA[1]��

���������е�i��Ԫ�أ����Ӧ�ڶ������еĸ�ĸ���ӽ��λ�õļ������£�

```c++
PARENT(i)
    return i/2
LEFT(i)
    return 2i
RIGHT(i)
    return 2i+1
```

#### b. ���/С��(max-heap/min-heap)  

�Ӷ������ĽǶȿ����������з�root��㣬����node->parent �� node/node->parent �� node

������ĽǶȿ������������±����1��Ԫ�أ����±�Ϊi��������A[PARENT( i)] �� A[i]/A[PARENT( i)] �� A[i]

#### c. �߶�height  

���ĸ߶ȣ��ӽ�㵽Ҷ���������ıߵ�������Ҷ�ӽ��ĸ߶�Ϊ0��
�������ĸ߶ȣ����и߶���ߵĽ��ĸ߶ȣ�ֻ��һ���������߶�Ϊ0��
�ѵĸ߶ȣ��Ѷѿ�����������ʱ�ĸ߶ȡ�

### ����

#### 1.�ѵĽṹ

A[N]��������

length[A]��������Ԫ�صĸ���

heap-size[A]�������A�еĶѵ�Ԫ�ظ���

#### 2.�ڶ��ϵĲ���
��1��MAX-HEAPIFY(A, i)

��2��BUILD-MAX-HEAP(A)

��3��HEAPSORT(A)

#### 3.�ѵ�Ӧ��

���ȼ�����

��1��HEAP-MAXIMUM(A)

��2��HEAP-INCREASE-KEY(A, i, key)

��3��HEAP-EXTRACT-KEY(A)

��4��MAX-HEAP-INSERT(A, key)



