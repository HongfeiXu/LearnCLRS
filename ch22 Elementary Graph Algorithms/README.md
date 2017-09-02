# 第22章 基本的图算法 

>Elementary Graph Algorithms

## 22.1 图的表示

图 `G = (V, E)`，有两种标准表示方法表示。邻接链表（adjacency-list） & 邻接矩阵（adjacency-matrix）。

## 22.2 广度优先搜索

给定图 `G = (V, E)` 和一个可以识别的源结点 `s`，广度优先搜索对图 `G` 中的边进行系统性的搜索来发现**可以从源结点 `s` 到达的所有结点**。  
该算法能够计算从源结点 `s` 到每个可达结点的距离（最少的边数），同时生成一棵“广度优先搜索树”。  
**该算法既可以用于有向图，也可以用于无向图。**  

为了跟踪算法的进展，广度优先搜索在概念上将每个结点涂上白色、灰色或黑色。  
白色：未被发现  
灰色：其邻接结点中可能存在未被发现的白色结点  
黑色：其所有邻接结点都已经被发现  

下图描述的是BFS在一个样本图上的推进过程  
![BFS](https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png)


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

Time = O(V + E)

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


```

### 深度优先搜索的性质

括号定理，后代区间的嵌套，白色路径定理

边的分类：（1）树边（2）反向边（3）正向边（4）交叉边

对无向图G进行深度搜索时，G的每一条边，要么是树边，要么是反向边。



## 22.4 拓扑排序

## 22.5 强连通分量


