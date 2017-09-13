# 第22章 基本的图算法 

>Elementary Graph Algorithms

## 22.1 图的表示

图 `G = (V, E)`，有两种标准表示方法表示。邻接链表（adjacency-list） & 邻接矩阵（adjacency-matrix）。

![Graph](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/Graph.png?raw=true)

## 22.2 广度优先搜索

给定图 `G = (V, E)` 和一个可以识别的源结点 `s`，广度优先搜索对图 `G` 中的边进行系统性的搜索来发现**可以从源结点 `s` 到达的所有结点**。  
该算法能够计算从源结点 `s` 到每个可达结点的距离（最少的边数），同时生成一棵“广度优先搜索树”。  
**该算法既可以用于有向图，也可以用于无向图。**  

为了跟踪算法的进展，广度优先搜索在概念上将每个结点涂上白色、灰色或黑色。  
白色：未被发现  
灰色：其邻接结点中可能存在未被发现的白色结点  
黑色：其所有邻接结点都已经被发现  

下图描述的是BFS在一个样本图上的推进过程  
![BFS](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/BFS.png?raw=true)


### Pseudocode

假定 G = (V, E) 以邻接链表表示  
结点的额外属性：   
`u.color` 用来存储颜色，  
`u.parent` 存储其前驱结点，  
`u.d` 存储从源点 `s` 到 `u` 的距离（最少的边数）。

```c++
BFS(G, s)
for each vertex u in G.V - {s}
    u.color = WHITE
    u.d = INF
    u.parent = NIL
s.color = GRAY
s.d = 0
s.parent = NIL
Q = NULL
ENQUEUE(Q, s)
while(Q != NULL)
    u = DEQUEUE(Q)
    for each vertex v in G.Adj[u]
        if v.color == WHITE
            v.color = GRAY
            v.d = u.d +１
            v.parent = u
            ENQUEUE(Q, v)
    u.color = BLACK
```

**Time = O(V + E)**

### 广度优先树

当运行在一个有向或无向图 `G = (V, E)` 上时，BFS 过程所建造出来的 parent 属性使得前驱子图称为一棵广度优先树。

下面代码打印出从源结点 `s` 到结点 `v` 的一条最短路径上的所有结点。

```c++
PRINT-PATH(G, s, v)
if v == s
    print s
else if v == NIL
    print "no path from" s "to" v "exists"
else
    PRINT-PATH(G, s, v.parent)
    print v
```

## 22.3 深度优先搜索

### 策略

深搜策略：在深搜过程中，对于最新发现的顶点，如果它还有以此为起点的而未探测到的边，就沿此边继续探测下去。当顶点v的所有边都已被探测过后，搜索将回溯到发现顶点v有起始点的那些边。

时间戳：当顶点v第一次被发现时记录下第一个时间戳`d[v]`，当结束检查v的邻接表时，记录下第二个时间戳`f[v]`。`v`在`d[v]`时刻前是白色的，在时刻`d[v]`和`f[v]`之间是灰色的，在时刻`f[v]`之后是黑色的。



### Pseudocode

输入图`G`既可以是无向图，也可以是有向图。变量`time`是一个全局变量，用来计算时间戳。

```c++
DFS(G)
for each vertex u in G.V
    u.color = WHITE
    u.parent = NIL
time = 0
for each vertex u in G.V
    if u.color == WHITE
        DFS-VISIT(G, u)

DFS-VISIT(G, u)
time = time + 1  // white vertex u has just been discovered
u.d = time
u.color = GRAY
for each v in G.Adj[u]  // explore edge (u, v)
    if v.color == WHITE
        v.parent = u
        DFS-VISIT(G, v)
u.color = BLACK  // blacken u
time = time + 1
u.f = time
```

**Time = BigTheta(V + E)**

下图描述的是DFS在一个样本图上的推进过程  
![DFS](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/DFS.png?raw=true)


### 深度优先搜索的性质

括号定理，后代区间的嵌套，白色路径定理

边的分类：（1）树边（2）后向边（3）正向边（4）横向边

对无向图`G`进行深度搜索时，每一条边，要么是树边，要么是后向边。

## 22.4 拓扑排序

对于一个**有向无环图** `G=(V, E)`来说，其**拓扑排序**是`G`中所有结点的一种线性次序，该次序满足如下条件：如果图`G`包含边`(u, v)`，则结点`u`在拓扑排序中处于结点`v`的前面（如果图`G`包含环路，则不可能排除一个线性次序）。

_可以将图的拓扑排序看做是将图的所有结点在一条水平线上排开，图的所有有向边都从左指向右。_

![Topological sort](https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png)

### Pseudocode

```
TOPOLOGICAL-SORT(G)
call DFS(G) to compute finishing times v.f for each vertex v
as each vertex is finished, insert it onto the front of a linked list
return the linked list of vertices
```

**Time = BigTheta(V + E)**

定理: 一个有向图是无环的，当且仅当对其深度优先搜索不产生后向边。


### 练习

练习 22.4-3 给出一个算法，用它来确定一个给定的无向图`G=(V,E)`中是否包含一个回路。
所给出的算法的运行时间为O(V)，这一时间独立于|E|。

解答：  
类似于有向图拓扑排序的思路：  
有向图：如果存在回路，则必存在一个子图，是一个环。因此该子图中所有顶点入度>=1。  
无向图：如果存在回路，则必存在一个子图，是一个环路。因此环路中所有顶点的度>=2。  
第一步：删除所有度<=1的顶点及相关的边，并将另外与这些边相关的其它顶点的度减一。  
第二步：将度数变为1的顶点排入队列，并从该队列中取出一个顶点重复步骤一。  
如果最后还有未删除顶点，则存在环，否则没有环。  

练习 22.4-5 在有向五环图 `G=(V, E)`上执行拓扑排序还有一种办法，就是重复找入度为 0 的结点，输出该结点，将该结点及其发出的边从图中删除。请解释如何在`O(V+E)`的时间实现这种思想。如果`G`包含环路，将会发生什么情况？

```c++
TOPOLOGICAL-SORT-v2(G)
for each vertex u in G
    if u.indegree == 0
        Q.push(u)
while(!Q.empty())
    v = Q.front()
    print v
    Q.pop()
    delete vertex v
    for each w in G.Adj[v]
        delete edge (v,w)
        w.indegree--
        if w.indegree == 0
            Q.push(w)
```

如果包含环路，则环路将不会被访问。图中结点始终不会被完全删除。否则，图中结点会随着排序的进行逐渐减少直至为空。

## 22.5 强连通分量




