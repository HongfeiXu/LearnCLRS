# ��9�� ��λ����˳��ͳ����

## 9.1 ��Сֵ�����ֵ

### ͬʱ�ҵ���Сֵ�����ֵ

�� n ��Ԫ����ͬʱ�ҵ���Сֵ�����ֵ�ķ�������Ȼ�ģ�ֻҪ�ֱ�������ҳ���Сֵ�����ֵ�������Ҫ n-1 �αȽϣ����� 2n-2 �αȽϡ�

��ʵ�ϣ����ǿ���ͨ��������Ԫ�سɶԵĽ��д������������ǽ�һ������Ԫ���໥���бȽϣ�Ȼ��ѽ�С��Ԫ���뵱ǰ��Сֵ�Ƚϣ��ѽϴ��Ԫ���뵱ǰ����Ԫ�ؽ��бȽϡ�������ÿ����Ԫ�ع���3�αȽϡ��ܵıȽϴ��������� 3*floor(n/2)��

### C++ʵ��

```c++
#include <vector>using namespace std;

// ͬʱ����Сֵ�����ֵ
void findMinMax(const vector<int> &numbers, int &min, int &max)
{
	auto numbersSize = numbers.size();
	int minTemp, maxTemp;
	
	// ����Ԫ�ظ�������ż���з�������
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

## 9.2 ����Ϊ����ʱ���ѡ���㷨

RANDOMIZED-SELECT�㷨���Ե�7�µĿ��������㷨Ϊģ�͵ġ����������һ����������Ȼ������������еݹ黮�֡������������ͬ���ǣ����������ݹ鴦���ֵ����ߣ��� RANDOMIZED-SELECT ֻ�����ֵ�һ�ߡ�

����������붼�ǻ���ġ����У�������������ʱ���ڣ����ǿ����ҵ���һ˳��ͳ������������λ����

������ RANDOMIZED-SELECT ��α����

���룺���� A[p..r]������ i  
��������� A[p..r] �е� i С��Ԫ�ء�  

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
i = RANDOM(p,r)  // ���ѡ��һ����Ԫ
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

### C++ʵ��

[RandomizedSelect.cpp](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch9/RandomizedSelect.cpp)

## 9.3 ����Ϊ����ʱ���ѡ���㷨

### ˼��

�� RANDOMIZED-SELECTһ����SELECT �㷨ͨ������������ĵݹ黮�����ҳ�����Ԫ�أ����ǣ��ڸ��㷨���ܹ�**��֤**�õ��������һ���õĻ��֡�
SELECT ʹ�õ�Ҳ�����Կ��������ȷ���Ի����㷨 PARTITION ���������޸ģ��ѻ��ֵ���ԪҲ��Ϊ���������
ͨ��ִ�����в��裬�㷨 SELECT ����ȷ��һ���� n>1 ����ͬԪ�ص������е� i С��Ԫ�ء������ n=1 ���� SELECT ֻ��������Ψһ������ֵ��Ϊ�� i С��Ԫ�ء���  

1. ����������� n ��Ԫ�ػ���Ϊ floor(n/5) �飬ÿ�� 5 ��Ԫ�أ�������ֻ��һ����ʣ�µ� n mod 5 ��Ԫ����ɡ�
2. Ѱ���� ceil(n/5) ����ÿһ�����λ���������ȶ�ÿ��Ԫ�ؽ��в�������Ȼ��ȷ��ÿ������Ԫ���е���λ������
3. �Ե� 2 �����ҳ��� ceil(n/5) ����λ�����ݹ���� SELECT ���ҳ�����λ�� x�������ż������λ����Ϊ�˷��㣬Լ�� x �ǽ�С����λ������
4. �����޸Ĺ��� PARTITION �汾������λ������λ�� x ������������л��֡��� k �Ȼ��ֵĵ����е�Ԫ����Ŀ��1����� x �ǵ� k С��Ԫ�أ������� n - k ��Ԫ���ڻ��ֵĸ�����
5. ��� i == k���򷵻� x����� i < k�����ڵ����ݹ���� SELECT ���ҳ��� i С��Ԫ�ء���� i > k�����ڸ����ݹ���ҵ� i - k С��Ԫ�ء�

### C++ʵ��

