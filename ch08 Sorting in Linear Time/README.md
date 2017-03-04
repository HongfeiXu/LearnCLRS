# �� 8 �� ����ʱ������

## 8.1 �Ƚ������㷨���½�

���� 8.1 �������£��καȽ��㷨����Ҫ��Omega(nlgn)�αȽϡ�

## 8.2 ��������

�����������n������Ԫ���е�ÿһ�������� 0 �� k �����ڵ�һ������������ k Ϊĳ���������� k = BigO(n)ʱ�����������ʱ��Ϊ Theta(n)��

### ����˼��
��ÿһ������Ԫ�� x ��ȷ��С�� x ��Ԫ�ظ�����������һ��Ϣ���Ϳ���ֱ�Ӱ� x �ŵ��������������е�λ�����ˡ����м���Ԫ����ͬʱ����һ������Ҫ�����޸ģ�ӦΪ���ܰ����Ƿ���ͬһ�����λ���ϡ�

### Pseudocode

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

### C++ʵ��

[CountingSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/CountingSort.cpp)

## 8.3 ��������

�����������Ȱ������Чλ���������������Ƭ��������ġ�  
Ϊ��ȷ�������������ȷ�ԣ�һλ�������㷨�������ȶ��ġ�  

### Pseudocode

```
RADIX-SORT(A, d)
for i = 1 to d
	use a stable sort to sort array A on digit i
```

### C++ʵ��

�����ȶ��������㷨 CountingSort ʵ�֡�
[RadixSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/RadixSort.cpp)

## 8.5 Ͱ����

### ����˼��
Ͱ����bucket sort�������������ݷ��Ӿ��ȷֲ���ƽ�����������ʱ����� BigO(n)��������������ƣ�������˵��������������������ݶ�����һ��С�����ڵ���������Ͱ�����������������һ��������̲������ù��̽�Ԫ�ؾ��ȡ������طֲ��� [0,1) �����ϡ�
Ͱ���� [0,1) ���仮�ֳ� n ����С��ͬ�������䣬���ΪͰ��Ȼ�󣬽� n ���������ֱ�ŵ�����Ͱ�С���Ϊ���������Ǿ��ȡ������ķֲ��� [0,1) �����ϣ�����һ�㲻������ܶ�����ͬһ��Ͱ�е������Ϊ�˵õ��������������ȶ�ÿ��Ͱ�е�����������Ȼ�����ÿ��Ͱ���մ���Ѹ���Ͱ�е�Ԫ���г������ɡ�

���룺A[1..n], 0 <= A[i] < 1, i =1,2,..,n  
��ʱ���飺B[0..n-1]���������������Ͱ��

```
BUCKET-SORT(A)
n = A.length
let B[0..n-1] be a new array
for i = 0 to n-1
    make B[i] an empty list
for i = 1 to n
    insert A[i] into list B[floor(n*A[i])]
for i = 0 to n-1
    sort list B[i] with insertion sort
```

### C++ʵ��

��������Ͳ��������Ͱ����ʵ��  
[BucketSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/BucketSort.cpp)




