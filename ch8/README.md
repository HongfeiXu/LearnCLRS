#第 8 章 线性时间排序

##8.1 比较排序算法的下界

定理 8.1 在最坏情况下，任何比较算法都需要做Omega(nlgn)次比较。

##8.2 计数排序

计数排序假设n个输入元素中的每一个都是在 0 到 k 区间内的一个整数，其中 k 为某个整数。当 k = BigO(n)时，排序的运行时间为 Theta(n)。

###基本思想
对每一个输入元素 x ，确定小于 x 的元素个数，利用这一信息，就可以直接把 x 放到它在输入数组中的位置上了。当有几个元素相同时，这一方案需要略做修改，应为不能把它们放在同一个输出位置上。

###Pseudocode

输入：A[1..n]，A.length = n
输出：B[1..n]
临时：C[0..k]
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

###C++实现

[CountingSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/CountingSort.cpp)

##8.3 基数排序

基数排序是先按最低有效位进行排序来解决卡片排序问题的。
为了确保基数排序的正确性，一位数排序算法必须是稳定的。

###Pseudocode
```
RADIX-SORT(A, d)
for i = 1 to d
	use a stable sort to sort array A on digit i
```

###C++实现
基于稳定的排序算法 CountingSort 实现。
[RadixSort.cpp]()
