#�� 8 �� ����ʱ������

##8.1 �Ƚ������㷨���½�

���� 8.1 �������£��καȽ��㷨����Ҫ��Omega(nlgn)�αȽϡ�

##8.2 ��������

�����������n������Ԫ���е�ÿһ�������� 0 �� k �����ڵ�һ������������ k Ϊĳ���������� k = BigO(n)ʱ�����������ʱ��Ϊ Theta(n)��

###����˼��
��ÿһ������Ԫ�� x ��ȷ��С�� x ��Ԫ�ظ�����������һ��Ϣ���Ϳ���ֱ�Ӱ� x �ŵ��������������е�λ�����ˡ����м���Ԫ����ͬʱ����һ������Ҫ�����޸ģ�ӦΪ���ܰ����Ƿ���ͬһ�����λ���ϡ�

###Pseudocode

���룺A[1..n]��A.length = n
�����B[1..n]
��ʱ��C[0..k]
```
COUNTING - SORT(A, B, K)
let C[0..k] be a new array
for i = 0 to k
	C[i] = 0
for j = 1 to A.length
	C[A[j]] = C[A[j]] + 1
for i = 1 to k
	C[i] = C[i] + C[i-1]
for j = A.length downto 1
	B[C[A[j]]] = A[j]
	C[A[j]] = C[A[j]] - 1
```

###C++ʵ��

[CountingSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/CountingSort.cpp)