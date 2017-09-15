# 第23章 最小生成树

aka Minimum Spanning Tree

>最小生成树是一副连通加权无向图中一棵权值最小的生成树。  
>本章主要讨论解决最小生成树问题的两种算法：Kruskal 算法和 Prim 算法。（均使用贪心策略）

## 23.1 最小生成树的形成

```
GENERIC-MST(G,w)
A = EmptySet
while A dose not form a spanning tree 
    find an edge (u, v) that is safe for A
    A = A + {(u, v)}
return A
```

## 23.2 Kruskal 算法和 Prim 算法

在 **Kruskal** 算法中，集合 A 是一个森林，其结点就是给定图的结点。每次加入到集合 A 中的安全边永远是权重最小的连接两个不同分量的边。

![Kruskal](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Kruskal.png?raw=true)
![Kruskal_part2](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Kruskal_part2.png?raw=true)

### Pseudocode

用到了一些**并查集**操作：
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

_对于图 G = (V, E)，Kruskal 算法的运行时间依赖于不相交集合数据结构（即并查集）的实现方式。_


在 **Prim** 算法中，集合 A 则是一棵树。每次加入到集合 A 中的安全边永远是连接 A 和 A 之外某个结点的边中权重最小的边。

![](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Prim.png?raw=true)
![](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch23%20Minimum%20Spanning%20Trees/images/Prim_part2.png?raw=true)

### Pseudocode

- 对于每个结点v，属性 v.key 保存的是连接 v 和树中结点的所有边中最小边的权重。如果不存在这样的边，则 v.key = INF。
- 对于每个结点v，属性 v.parent给出的是结点　ｖ　在树中的父节点。
- r 为最小生成树的根节点。  
- 所有不在树 A 中的结点都存放在一个基于 key 属性的**最小优先队列 Q** 中。  

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

_Prim 算法的运行时间取决于最小优先队列 Q 的实现方式。_