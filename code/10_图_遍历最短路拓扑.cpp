#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

struct Edge { std::size_t to; int weight; };

class Graph {
private:
    std::vector<std::vector<Edge>> adjacency_;
public:
    explicit Graph(std::size_t vertices) : adjacency_(vertices) {}
    std::size_t size() const noexcept { return adjacency_.size(); }

    void addDirectedEdge(std::size_t from, std::size_t to, int weight = 1) {
        if (from >= size() || to >= size()) throw std::out_of_range("invalid vertex");
        adjacency_[from].push_back({to, weight});
    }
    void addUndirectedEdge(std::size_t a, std::size_t b, int weight = 1) {
        addDirectedEdge(a, b, weight);
        addDirectedEdge(b, a, weight);
    }
    const std::vector<Edge>& neighbors(std::size_t vertex) const { return adjacency_.at(vertex); }
};

std::vector<std::size_t> bfs(const Graph& graph, std::size_t start) {
    if (start >= graph.size()) throw std::out_of_range("invalid start");
    std::vector<bool> visited(graph.size(), false);
    std::queue<std::size_t> pending;
    std::vector<std::size_t> order;
    visited[start] = true;
    pending.push(start);
    while (!pending.empty()) {
        const auto vertex = pending.front(); pending.pop();
        order.push_back(vertex);
        for (const auto& edge : graph.neighbors(vertex)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                pending.push(edge.to);
            }
        }
    }
    return order;
}

std::vector<long long> dijkstra(const Graph& graph, std::size_t source) {
    const auto infinity = std::numeric_limits<long long>::max();
    std::vector<long long> distance(graph.size(), infinity);
    using State = std::pair<long long, std::size_t>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> heap;
    distance.at(source) = 0;
    heap.push({0, source});
    while (!heap.empty()) {
        const auto [currentDistance, vertex] = heap.top(); heap.pop();
        if (currentDistance != distance[vertex]) continue; // 丢弃过期堆项
        for (const auto& edge : graph.neighbors(vertex)) {
            if (edge.weight < 0) throw std::invalid_argument("Dijkstra requires nonnegative edges");
            const auto candidate = currentDistance + edge.weight;
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                heap.push({candidate, edge.to});
            }
        }
    }
    return distance;
}

std::optional<std::vector<std::size_t>> topologicalSort(const Graph& graph) {
    std::vector<std::size_t> indegree(graph.size(), 0);
    for (std::size_t u = 0; u < graph.size(); ++u)
        for (const auto& edge : graph.neighbors(u)) ++indegree[edge.to];
    std::queue<std::size_t> ready;
    for (std::size_t i = 0; i < graph.size(); ++i) if (indegree[i] == 0) ready.push(i);
    std::vector<std::size_t> order;
    while (!ready.empty()) {
        const auto u = ready.front(); ready.pop();
        order.push_back(u);
        for (const auto& edge : graph.neighbors(u)) if (--indegree[edge.to] == 0) ready.push(edge.to);
    }
    if (order.size() != graph.size()) return std::nullopt;
    return order;
}

template <typename T>
void print(const std::vector<T>& values) {
    for (const auto& value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    Graph graph(5);
    graph.addDirectedEdge(0, 1, 2);
    graph.addDirectedEdge(0, 2, 5);
    graph.addDirectedEdge(1, 2, 1);
    graph.addDirectedEdge(1, 3, 2);
    graph.addDirectedEdge(2, 4, 3);
    graph.addDirectedEdge(3, 4, 1);
    std::cout << "BFS: "; print(bfs(graph, 0));
    std::cout << "最短距离: "; print(dijkstra(graph, 0));
    std::cout << "拓扑序: ";
    if (const auto order = topologicalSort(graph)) print(*order);
    else std::cout << "图中有环\n";
}
