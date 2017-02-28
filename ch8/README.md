# 第 8 章 线性时间排序

## 8.1 比较排序算法的下界

定理 8.1 在最坏情况下，任何比较算法都需要做Omega(nlgn)次比较。

## 8.2 计数排序

计数排序假设n个输入元素中的每一个都是在 0 到 k 区间内的一个整数，其中 k 为某个整数。当 k = BigO(n)时，排序的运行时间为 Theta(n)。

### 基本思想
对每一个输入元素 x ，确定小于 x 的元素个数，利用这一信息，就可以直接把 x 放到它在输入数组中的位置上了。当有几个元素相同时，这一方案需要略做修改，应为不能把它们放在同一个输出位置上。

### Pseudocode

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

### C++实现

[CountingSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/CountingSort.cpp)

## 8.3 基数排序

基数排序是先按最低有效位进行排序来解决卡片排序问题的。  
为了确保基数排序的正确性，一位数排序算法必须是稳定的。  

### Pseudocode

```
RADIX-SORT(A, d)
for i = 1 to d
	use a stable sort to sort array A on digit i
```

### C++实现

基于稳定的排序算法 CountingSort 实现。
[RadixSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/RadixSort.cpp)

## 8.5 桶排序

### 基本思想
桶排序（bucket sort）假设输入数据服从均匀分布，平均情况下它的时间代价 BigO(n)。与计数排序类似，具体来说，计数排序假设输入数据都属于一个小区间内的整数，而桶排序则假设输入是由一个随机过程产生，该过程将元素均匀、独立地分布在 [0,1) 区间上。
桶排序将 [0,1) 区间划分成 n 个大小相同的子区间，或称为桶。然后，将 n 个输入数分别放到各个桶中。因为输入数据是均匀、独立的分布在 [0,1) 区间上，所以一般不会产生很多落在同一个桶中的情况。为了得到输出结果，我们先对每个桶中的数进行排序，然后遍历每个桶按照次序把各个桶中的元素列出来即可。

输入：A[1..n], 0 <= A[i] < 1, i =1,2,..,n  
临时数组：B[0..n-1]，用来存放链表（即桶）

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

### C++实现

基于链表和插入排序的桶排序实现  
[BucketSort.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch8/BucketSort.cpp)




