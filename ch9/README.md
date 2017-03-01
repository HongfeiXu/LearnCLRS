# 第9章 中位数和顺序统计量

## 9.1 最小值和最大值

### 同时找到最小值和最大值

在 n 个元素中同时找到最小值和最大值的方法是显然的：只要分别独立的找出最小值和最大值，这各需要 n-1 次比较，共需 2n-2 次比较。

事实上，我们可以通过对输入元素成对的进行处理，即首先我们将一对输入元素相互进行比较，然后把较小的元素与当前最小值比较，把较大的元素与当前最大的元素进行比较。这样，每两个元素共需3次比较。总的比较次数至多是 3*floor(n/2)。

### C++实现

```c++
#include <vector>using namespace std;

// 同时找最小值和最大值
void findMinMax(const vector<int> &numbers, int &min, int &max)
{
	auto numbersSize = numbers.size();
	int minTemp, maxTemp;
	
	// 依照元素个数的奇偶进行分类讨论
	if(numbersSize % 2 == 0)
	{
		numbers[0] <= numbers[1] ? min = numbers[0], max = numbers[1] : min = numbers[1], max = numbers[0];
		for(int i = 2; i != numbersSize - 2; i += 2)
		{
			numbers[i] <= numbers[i + 1] ? minTemp = numbers[i], maxTemp = numbers[i + 1] : minTemp = numbers[i + 1], maxTemp = numbers[i];
			if(minTemp < min)
				min = minTemp;
			if(maxTemp > max)
				max = maxTemp;
		}
	}
	else
	{
		min = max = numbers[0];
		for(int i = 1; i != numbersSize - 2; i += 2)
		{
			numbers[i] < numbers[i + 1] ? minTemp = numbers[i], maxTemp = numbers[i + 1] : minTemp = numbers[i + 1], maxTemp = numbers[i];
			if(minTemp < min)
				min = minTemp;
			if(maxTemp > max)
				max = maxTemp;
		}
	}
}
```

## 9.2 期望为线性时间的选择算法

RANDOMIZED-SELECT算法是以第7章的快速排序算法为模型的。与快速排序一样，我们仍然将输入数组进行递归划分。但与快速排序不同的是，快速排序会递归处理划分的两边，而 RANDOMIZED-SELECT 只处理划分的一边。

这里假设输入都是互异的。则有，在期望的线性时间内，我们可以找到任一顺序统计量，包括中位数。

以下是 RANDOMIZED-SELECT 的伪代码

输入：数组 A[p..r]，整数 i  
输出：数组 A[p..r] 中第 i 小的元素。  

```
PARTITION(A,p,r)
x = A[r]
i = p-1
for j = p to r-1
    if A[j] <= x
        i = i+1
        exchange A[i] with A[j]
exchange A[i+1] with A[r]
return i+1
```

```
RANDOMIZED-PARTITION(A,p,r)
i = RANDOM(p,r)  // 随机选择一个主元
exchange A[r] with A[i]
return PARTITOIN(A,p,r)
```

```
RANDOMIZED-SELECT(A,p,r,i)
if p == r
    return A[p]
q = RANDOMIZED-PARTITION(A,p,r)
k = q-p+1
if i == k
    return A[q]
else if i < k
    return RANDOMIZED-SELECT(A,p,q-1,i)
else
    return RANDOMIZED-SELECT(A,q+1,r,i-k)
```

### C++实现

[RandomizedSelect.cpp]()