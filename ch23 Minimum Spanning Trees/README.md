# ��23�� ��С������

aka Minimum Spanning Tree

>��С��������һ����ͨ��Ȩ����ͼ��һ��Ȩֵ��С����������  
>������Ҫ���۽����С����������������㷨��Kruskal �㷨�� Prim �㷨������ʹ��̰�Ĳ��ԣ�

## 23.1 ��С���������γ�

```
GENERIC-MST(G,w)
A = EmptySet
while A dose not form a spanning tree 
    find an edge (u, v) that is safe for A
    A = A + {(u, v)}
return A
```

## 23.2 Kruskal �㷨�� Prim �㷨

�� **Kruskal** �㷨�У����� A ��һ��ɭ�֣�������Ǹ���ͼ�Ľ�㡣ÿ�μ��뵽���� A �еİ�ȫ����Զ��Ȩ����С������������ͬ�����ıߡ�

![Kruskal](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Kruskal.png?raw=true)
![Kruskal_part2](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Kruskal_part2.png?raw=true)

### Pseudocode

�õ���һЩ**���鼯**������
- FIND-SET(u)  
- MAKE-SET(u)  
- UNION(u, v)  

```
MST-KRUSKAL(G, w)
A = EmptySet
for each vertex v in G.V
    MAKE-SET(v)
sort the edges of G.E into nondecreasing order by weight w
for each edge (u, v) in G.E, taken in nondecreasing order by weight
    if FIND-SET(u) != FIND-SET(v)
        A = A + {(u, v)}
        UNION(u, v)
```

_����ͼ G = (V, E)��Kruskal �㷨������ʱ�������ڲ��ཻ�������ݽṹ�������鼯����ʵ�ַ�ʽ��_


�� **Prim** �㷨�У����� A ����һ������ÿ�μ��뵽���� A �еİ�ȫ����Զ������ A �� A ֮��ĳ�����ı���Ȩ����С�ıߡ�

![](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Prim.png?raw=true)
![](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Prim_part2.png?raw=true)

### Pseudocode

- ����ÿ�����v������ v.key ����������� v �����н������б�����С�ߵ�Ȩ�ء���������������ıߣ��� v.key = INF��
- ����ÿ�����v������ v.parent�������ǽ�㡡���������еĸ��ڵ㡣
- r Ϊ��С�������ĸ��ڵ㡣  
- ���в����� A �еĽ�㶼�����һ������ key ���Ե�**��С���ȶ��� Q** �С�  

```
MST-PRIM(G, w, r)
for each u in G.V
    u.key = INF
    u.parent = NIL
r.key = 0
Q = G.V
while Q != Empty
    u = EXTRACT-MIN(Q)
    for each v in G.Adj[u]
        if v in Q and w(u, v) < v.key
            v.parent = u
            v.key = w(u, v)
```

_Prim �㷨������ʱ��ȡ������С���ȶ��� Q ��ʵ�ַ�ʽ��_