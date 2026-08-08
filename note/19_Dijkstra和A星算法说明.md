# 19. Dijkstra 和 A* 算法

> 对应源码：`code/19_Dijkstra和A星算法.cpp`

## 1. 题目

在一张无向带权图中，寻找从起点 `S` 到目标 `G` 的最短路径，并对比 Dijkstra 和 A* 的节点选择方式。

```text
S --2-- A --2-- C
|       |       | \
5       4       1  7
|       |       |   \
B --1-- D --2-- E --1-- G
 \      |
  \--5--E
         
D --4-- G
```

源码中的边以 `AddEdge` 调用为准，图示只用于帮助观察主要连接。最短路径为：

```text
S -> A -> C -> D -> E -> G
代价 = 2 + 2 + 1 + 2 + 1 = 8
```

## 2. 图的存储

图使用 C++ 标准容器形式的邻接表：

```cpp
struct Edge {
    Vertex to;
    WeightType weight;
};

std::vector<std::vector<Edge>> adjacency_;
```

`adjacency_[v]` 保存从顶点 `v` 出发的所有边。因为是无向图，每条边会分别写入两个顶点的邻接表。

## 3. 共用的搜索状态

优先队列中的状态为：

```cpp
struct State {
    Vertex vertex;
    WeightType g;
    WeightType f;
};
```

- `vertex`：当前顶点。
- `g`：从起点到当前顶点已知的实际代价。
- `f`：搜索优先级。Dijkstra 中 `f=g`，A* 中 `f=g+h`。

`std::priority_queue` 默认是最大堆，比较器使用 `>` 将其改为按较小 `f` 优先的最小堆。

## 4. Dijkstra

Dijkstra 只关心已经付出的代价：

```text
f(n) = g(n)
```

它每次取出当前 `g` 最小的顶点，然后尝试通过该顶点改善邻接顶点的距离。代码通过一个全零启发数组调用共用搜索函数：

```cpp
const std::vector<WeightType> zeroHeuristic(adjacency_.size(), 0);
return ShortestPath(start, goal, zeroHeuristic);
```

因为 `h=0`，所以 `f=g+h=g`。这也说明 Dijkstra 可以看作 A* 在启发函数恒为零时的特殊情况。

## 5. A*

A* 在已知代价之上加入对剩余代价的估计：

```text
f(n) = g(n) + h(n)
```

本例按顶点 `S、A、B、C、D、E、G` 给出：

```cpp
const std::vector<int> heuristic = {7, 5, 3, 3, 2, 1, 0};
```

目标节点必须满足 `h(G)=0`。为了保证最优性，启发值不应超过对应顶点到目标的真实最短距离。

在这个例子中，A* 能够使用 `h` 更集中地向 `G` 扩展，而 Dijkstra 会同时向所有低代价方向扩展。

## 6. 松弛操作

对当前顶点的每条出边，计算新路径：

```cpp
const WeightType candidate =
    distance[current.vertex] + edge.weight;
```

如果新路径更短：

```cpp
if (candidate < distance[edge.to]) {
    distance[edge.to] = candidate;
    parent[edge.to] = current.vertex;
    open.push(State{
        edge.to,
        candidate,
        candidate + heuristic[edge.to]
    });
}
```

这个更新距离和父节点的过程称为松弛（relaxation）。

## 7. 为什么同一顶点会多次入队

`std::priority_queue` 不提供直接修改队列中某个元素优先级的操作。发现更短路径时，代码会将新状态再次入队，老状态仍然留在队列中。

例如某顶点先以 `g=10` 入队，之后又发现 `g=7` 的路径。当 `g=10` 的旧状态出队时，通过：

```cpp
if (current.g != distance[current.vertex]) {
    continue;
}
```

可以判断它已过期并忽略。

## 8. 路径还原

每次松弛成功时记录：

```cpp
parent[edge.to] = current.vertex;
```

找到目标后，从 `G` 沿 `parent` 反向追踪：

```text
G <- E <- D <- C <- A <- S
```

然后使用 `std::reverse` 得到：

```text
S -> A -> C -> D -> E -> G
```

## 9. 为什么不能有负权边

Dijkstra 和本实现的 A* 都依赖“路径只会在继续前进时变得更长”。如果存在负权边，已经取出的顶点仍可能被后来的路径大幅改善，算法的结束条件就不再成立。

`AddEdge` 因此拒绝负权边。含负权边的最短路径问题应使用 Bellman-Ford 等算法。

## 10. 复杂度

使用邻接表和二叉堆时：

| 算法 | 最坏时间复杂度 | 辅助空间 |
| --- | --- | --- |
| Dijkstra | `O((V+E) log V)` | `O(V+E)` |
| A* | `O((V+E) log V)` 的常见图实现上界 | `O(V+E)` |

A* 的最坏情况不一定比 Dijkstra 更好，但好的启发函数能减少实际展开的顶点数。

## 11. 两种算法的关系

| 特点 | Dijkstra | A* |
| --- | --- | --- |
| 优先级 | `g(n)` | `g(n)+h(n)` |
| 需要启发函数 | 否 | 是 |
| 搜索倾向 | 从起点向四周扩张 | 被引导向目标 |
| 最优条件 | 边权非负 | 边权非负且启发函数可采纳 |

可以记住：

```text
Dijkstra = h(n) 恒为 0 的 A*
```
