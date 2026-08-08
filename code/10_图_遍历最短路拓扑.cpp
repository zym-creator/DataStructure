#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge { int to; int weight; };

class Graph {
private:
    vector<vector<Edge> > adjacency;
public:
    Graph(int vertexCount) : adjacency(vertexCount) {}
    /* 作用：返回图的顶点数。 */
    int size() const { return (int)adjacency.size(); }
    /* 作用：添加 from 到 to 的有向边。成功返回 true。 */
    bool addDirectedEdge(int from, int to, int weight = 1) {
        if (from < 0 || from >= size() || to < 0 || to >= size()) return false;
        Edge edge = {to, weight}; adjacency[from].push_back(edge); return true;
    }
    /* 作用：返回 vertex 的邻接边表。 */
    const vector<Edge>& neighbors(int vertex) const { return adjacency[vertex]; }
};

/* 作用：从 start 开始广度优先遍历，返回访问顺序。 */
vector<int> bfs(const Graph& graph, int start) {
    vector<int> order;
    if (start < 0 || start >= graph.size()) return order;
    vector<bool> visited(graph.size(), false);
    queue<int> pending;
    visited[start] = true; pending.push(start);
    while (!pending.empty()) {
        int vertex = pending.front(); pending.pop(); order.push_back(vertex);
        const vector<Edge>& edges = graph.neighbors(vertex);
        for (int i = 0; i < (int)edges.size(); i++) {
            int next = edges[i].to;
            if (!visited[next]) { visited[next] = true; pending.push(next); }
        }
    }
    return order;
}

/* 作用：求 source 到各点的非负权最短距离。不可达位置为 INT_MAX。 */
vector<int> dijkstra(const Graph& graph, int source) {
    vector<int> distance(graph.size(), INT_MAX);
    vector<bool> used(graph.size(), false);
    if (source < 0 || source >= graph.size()) return distance;
    distance[source] = 0;
    // 基础版本每轮在线性表中寻找未确定的最近顶点。
    for (int round = 0; round < graph.size(); round++) {
        int vertex = -1;
        for (int i = 0; i < graph.size(); i++)
            if (!used[i] && distance[i] != INT_MAX && (vertex == -1 || distance[i] < distance[vertex])) vertex = i;
        if (vertex == -1) break;
        used[vertex] = true;
        const vector<Edge>& edges = graph.neighbors(vertex);
        for (int i = 0; i < (int)edges.size(); i++) {
            int next = edges[i].to;
            int candidate = distance[vertex] + edges[i].weight;
            if (edges[i].weight >= 0 && candidate < distance[next]) distance[next] = candidate;
        }
    }
    return distance;
}

/* 作用：对有向图做拓扑排序。无环返回 true，order 保存拓扑序。 */
bool topologicalSort(const Graph& graph, vector<int>& order) {
    vector<int> indegree(graph.size(), 0);
    for (int u = 0; u < graph.size(); u++) {
        const vector<Edge>& edges = graph.neighbors(u);
        for (int i = 0; i < (int)edges.size(); i++) indegree[edges[i].to]++;
    }
    queue<int> ready;
    for (int i = 0; i < graph.size(); i++) if (indegree[i] == 0) ready.push(i);
    order.clear();
    while (!ready.empty()) {
        int u = ready.front(); ready.pop(); order.push_back(u);
        const vector<Edge>& edges = graph.neighbors(u);
        for (int i = 0; i < (int)edges.size(); i++) if (--indegree[edges[i].to] == 0) ready.push(edges[i].to);
    }
    return (int)order.size() == graph.size();
}

/* 作用：输出整数 vector；INT_MAX 输出为 INF。 */
void printVector(const vector<int>& values) {
    for (int i = 0; i < (int)values.size(); i++) {
        if (values[i] == INT_MAX) cout << "INF "; else cout << values[i] << ' ';
    }
    cout << endl;
}

int main() {
    Graph graph(5);
    graph.addDirectedEdge(0, 1, 2); graph.addDirectedEdge(0, 2, 5);
    graph.addDirectedEdge(1, 2, 1); graph.addDirectedEdge(1, 3, 2);
    graph.addDirectedEdge(2, 4, 3); graph.addDirectedEdge(3, 4, 1);
    cout << "BFS: "; printVector(bfs(graph, 0));
    cout << "最短距离: "; printVector(dijkstra(graph, 0));
    vector<int> order;
    cout << "拓扑序: "; if (topologicalSort(graph, order)) printVector(order); else cout << "图中有环" << endl;
    return 0;
}
