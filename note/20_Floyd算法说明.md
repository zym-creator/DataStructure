# 20. Floyd 算法

> 对应源码：`code/20_Floyd.cpp`

## 1. 全源最短路径

Floyd-Warshall 算法用于计算图中任意两个顶点之间的最短距离。Dijkstra 通常从一个起点出发，而 Floyd 一次得到整张最短距离矩阵。

源码使用：

```cpp
std::vector<std::vector<WeightType>> distance_;
std::vector<std::vector<Vertex>> next_;
```

- `distance_[i][j]`：从 `i` 到 `j` 的当前最短距离。
- `next_[i][j]`：从 `i` 前往 `j` 时应该先走向哪个顶点。

## 2. 初始化

顶点到自身的距离为 `0`：

```cpp
distance_[vertex][vertex] = 0;
next_[vertex][vertex] = vertex;
```

直接相连的顶点使用边权，没有边时使用 `Infinity`。如果输入包含两个顶点之间的多条边，只保留权重最小的一条。

## 3. 动态规划转移

对任意顶点 `from`、`to` 和中间顶点 `middle`，比较：

```text
当前路径：distance[from][to]
经过 middle：distance[from][middle] + distance[middle][to]
```

如果经过 `middle` 更短：

```cpp
distance_[from][to] = throughMiddle;
next_[from][to] = next_[from][middle];
```

三层循环的顺序必须是：

```cpp
for (middle)
    for (from)
        for (to)
```

完成第 `k` 轮后，`distance[i][j]` 表示只允许前 `k` 个顶点作为中间点时的最短距离。

## 4. 避免对无穷大相加

如果 `from-middle` 或 `middle-to` 不可达，就不能计算两者之和：

```cpp
if (distance_[from][middle] == Infinity) {
    continue;
}
```

这既避免把不存在的路径当成候选路径，也降低整数溢出风险。

## 5. 路径还原

假设：

```text
next[0][4] = 1
next[1][4] = 4
```

从 `0` 出发反复查询 `next[current][4]`：

```text
0 -> 1 -> 4
```

`next` 矩阵比只记录“最后一个中间点”更适合直接迭代输出路径。

## 6. 复杂度

| 资源 | 复杂度 |
| --- | --- |
| 时间 | `O(V³)` |
| 距离矩阵 | `O(V²)` |
| 路径矩阵 | `O(V²)` |

Floyd 适合顶点数不太大，但需要频繁查询任意两点最短路径的场景。

## 7. 与原实现的区别

重构版使用动态矩阵，正确将对角线设为 `0`，在转移前检查两段路径是否可达，并使用 `next_` 还原完整路径。示例是无向非负权图，顶点编号为 `0 ~ V-1`。
