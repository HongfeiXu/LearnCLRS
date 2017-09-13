# ��22�� ������ͼ�㷨 

>Elementary Graph Algorithms

## 22.1 ͼ�ı�ʾ

ͼ `G = (V, E)`�������ֱ�׼��ʾ������ʾ���ڽ�����adjacency-list�� & �ڽӾ���adjacency-matrix����

![Graph](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/Graph.png?raw=true)

## 22.2 �����������

����ͼ `G = (V, E)` ��һ������ʶ���Դ��� `s`���������������ͼ `G` �еı߽���ϵͳ�Ե�����������**���Դ�Դ��� `s` ��������н��**��  
���㷨�ܹ������Դ��� `s` ��ÿ���ɴ���ľ��루���ٵı�������ͬʱ����һ�á������������������  
**���㷨�ȿ�����������ͼ��Ҳ������������ͼ��**  

Ϊ�˸����㷨�Ľ�չ��������������ڸ����Ͻ�ÿ�����Ϳ�ϰ�ɫ����ɫ���ɫ��  
��ɫ��δ������  
��ɫ�����ڽӽ���п��ܴ���δ�����ֵİ�ɫ���  
��ɫ���������ڽӽ�㶼�Ѿ�������  

��ͼ��������BFS��һ������ͼ�ϵ��ƽ�����  
![BFS](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/BFS.png?raw=true)


### Pseudocode

�ٶ� G = (V, E) ���ڽ������ʾ  
���Ķ������ԣ�   
`u.color` �����洢��ɫ��  
`u.parent` �洢��ǰ����㣬  
`u.d` �洢��Դ�� `s` �� `u` �ľ��루���ٵı�������

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
            v.d = u.d +��
            v.parent = u
            ENQUEUE(Q, v)
    u.color = BLACK
```

**Time = O(V + E)**

### ���������

��������һ�����������ͼ `G = (V, E)` ��ʱ��BFS ��������������� parent ����ʹ��ǰ����ͼ��Ϊһ�ù����������

��������ӡ����Դ��� `s` ����� `v` ��һ�����·���ϵ����н�㡣

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

## 22.3 �����������

### ����

���Ѳ��ԣ������ѹ����У��������·��ֵĶ��㣬����������Դ�Ϊ���Ķ�δ̽�⵽�ıߣ����ش˱߼���̽����ȥ��������v�����б߶��ѱ�̽��������������ݵ����ֶ���v����ʼ�����Щ�ߡ�

ʱ�����������v��һ�α�����ʱ��¼�µ�һ��ʱ���`d[v]`�����������v���ڽӱ�ʱ����¼�µڶ���ʱ���`f[v]`��`v`��`d[v]`ʱ��ǰ�ǰ�ɫ�ģ���ʱ��`d[v]`��`f[v]`֮���ǻ�ɫ�ģ���ʱ��`f[v]`֮���Ǻ�ɫ�ġ�



### Pseudocode

����ͼ`G`�ȿ���������ͼ��Ҳ����������ͼ������`time`��һ��ȫ�ֱ�������������ʱ�����

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

��ͼ��������DFS��һ������ͼ�ϵ��ƽ�����  
![DFS](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch22%20Elementary%20Graph%20Algorithms/images/DFS.png?raw=true)


### �����������������

���Ŷ�����������Ƕ�ף���ɫ·������

�ߵķ��ࣺ��1�����ߣ�2������ߣ�3������ߣ�4�������

������ͼ`G`�����������ʱ��ÿһ���ߣ�Ҫô�����ߣ�Ҫô�Ǻ���ߡ�

## 22.4 ��������

����һ��**�����޻�ͼ** `G=(V, E)`��˵����**��������**��`G`�����н���һ�����Դ��򣬸ô��������������������ͼ`G`������`(u, v)`������`u`�����������д��ڽ��`v`��ǰ�棨���ͼ`G`������·���򲻿����ų�һ�����Դ��򣩡�

_���Խ�ͼ�������������ǽ�ͼ�����н����һ��ˮƽ�����ſ���ͼ����������߶�����ָ���ҡ�_

![Topological sort](https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png)

### Pseudocode

```
TOPOLOGICAL-SORT(G)
call DFS(G) to compute finishing times v.f for each vertex v
as each vertex is finished, insert it onto the front of a linked list
return the linked list of vertices
```

**Time = BigTheta(V + E)**

����: һ������ͼ���޻��ģ����ҽ����������������������������ߡ�


### ��ϰ

��ϰ 22.4-3 ����һ���㷨��������ȷ��һ������������ͼ`G=(V,E)`���Ƿ����һ����·��
���������㷨������ʱ��ΪO(V)����һʱ�������|E|��

���  
����������ͼ���������˼·��  
����ͼ��������ڻ�·����ش���һ����ͼ����һ��������˸���ͼ�����ж������>=1��  
����ͼ��������ڻ�·����ش���һ����ͼ����һ����·����˻�·�����ж���Ķ�>=2��  
��һ����ɾ�����ж�<=1�Ķ��㼰��صıߣ�������������Щ����ص���������Ķȼ�һ��  
�ڶ�������������Ϊ1�Ķ���������У����Ӹö�����ȡ��һ�������ظ�����һ��  
��������δɾ�����㣬����ڻ�������û�л���  

��ϰ 22.4-5 �������廷ͼ `G=(V, E)`��ִ������������һ�ְ취�������ظ������Ϊ 0 �Ľ�㣬����ý�㣬���ý�㼰�䷢���ıߴ�ͼ��ɾ��������������`O(V+E)`��ʱ��ʵ������˼�롣���`G`������·�����ᷢ��ʲô�����

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

���������·����·�����ᱻ���ʡ�ͼ�н��ʼ�ղ��ᱻ��ȫɾ��������ͼ�н�����������Ľ����𽥼���ֱ��Ϊ�ա�

## 22.5 ǿ��ͨ����




