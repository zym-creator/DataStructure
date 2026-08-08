#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

class WeightedGraph {
public:
    using Vertex = int;
    using WeightType = int;

    struct SearchResult {
        bool found;
        WeightType distance;
        std::vector<Vertex> path;
        int expandedCount;
    };

    explicit WeightedGraph(int vertexCount)
        : adjacency_(vertexCount > 0 ? vertexCount : 0) {}

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) ||
            first == second || weight < 0) {
            return false;
        }

        adjacency_[first].push_back(Edge{second, weight});
        adjacency_[second].push_back(Edge{first, weight});
        return true;
    }

    SearchResult Dijkstra(Vertex start, Vertex goal) const {
        const std::vector<WeightType> zeroHeuristic(adjacency_.size(), 0);
        return ShortestPath(start, goal, zeroHeuristic);
    }

    SearchResult AStar(Vertex start, Vertex goal,
                       const std::vector<WeightType>& heuristic) const {
        if (heuristic.size() != adjacency_.size()) {
            return FailureResult();
        }

        for (WeightType value : heuristic) {
            if (value < 0) {
                return FailureResult();
            }
        }
        return ShortestPath(start, goal, heuristic);
    }

private:
    struct Edge {
        Vertex to;
        WeightType weight;
    };

    struct State {
        Vertex vertex;
        WeightType g;
        WeightType f;
    };

    struct CompareState {
        bool operator()(const State& first, const State& second) const {
            if (first.f != second.f) {
                return first.f > second.f;
            }

            // f 相同时，优先选择 h=f-g 更小的状态。
            return first.f - first.g > second.f - second.g;
        }
    };

    SearchResult ShortestPath(
        Vertex start,
        Vertex goal,
        const std::vector<WeightType>& heuristic) const {
        if (!IsValidVertex(start) || !IsValidVertex(goal)) {
            return FailureResult();
        }

        const WeightType infinity = std::numeric_limits<WeightType>::max();
        std::vector<WeightType> distance(adjacency_.size(), infinity);
        std::vector<Vertex> parent(adjacency_.size(), -1);
        std::priority_queue<State, std::vector<State>, CompareState> open;

        distance[start] = 0;
        open.push(State{start, 0, heuristic[start]});
        int expandedCount = 0;

        while (!open.empty()) {
            const State current = open.top();
            open.pop();

            // 同一顶点可能多次入队，忽略已经过期的较长路径。
            if (current.g != distance[current.vertex]) {
                continue;
            }

            ++expandedCount;
            if (current.vertex == goal) {
                return SearchResult{
                    true,
                    distance[goal],
                    BuildPath(parent, start, goal),
                    expandedCount
                };
            }

            for (const Edge& edge : adjacency_[current.vertex]) {
                if (distance[current.vertex] > infinity - edge.weight) {
                    continue;
                }

                const WeightType candidate =
                    distance[current.vertex] + edge.weight;
                if (candidate < distance[edge.to]) {
                    distance[edge.to] = candidate;
                    parent[edge.to] = current.vertex;
                    open.push(State{
                        edge.to,
                        candidate,
                        candidate + heuristic[edge.to]
                    });
                }
            }
        }

        return FailureResult(expandedCount);
    }

    static std::vector<Vertex> BuildPath(
        const std::vector<Vertex>& parent,
        Vertex start,
        Vertex goal) {
        std::vector<Vertex> path;

        for (Vertex current = goal; current != -1; current = parent[current]) {
            path.push_back(current);
            if (current == start) {
                break;
            }
        }

        if (path.empty() || path.back() != start) {
            return {};
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    static SearchResult FailureResult(int expandedCount = 0) {
        return SearchResult{false, -1, {}, expandedCount};
    }

    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 &&
               vertex < static_cast<Vertex>(adjacency_.size());
    }

    std::vector<std::vector<Edge>> adjacency_;
};

void PrintResult(const std::string& algorithm,
                 const WeightedGraph::SearchResult& result,
                 const std::vector<std::string>& names) {
    std::cout << algorithm << "\n";
    if (!result.found) {
        std::cout << "  未找到路径\n";
        return;
    }

    std::cout << "  路径：";
    for (int i = 0; i < static_cast<int>(result.path.size()); ++i) {
        if (i > 0) {
            std::cout << " -> ";
        }
        std::cout << names[result.path[i]];
    }
    std::cout << "\n  总代价：" << result.distance
              << "\n  展开节点数：" << result.expandedCount << '\n';
}

int main() {
    // 顶点顺序：S、A、B、C、D、E、G。
    const std::vector<std::string> names = {"S", "A", "B", "C", "D", "E", "G"};
    WeightedGraph graph(static_cast<int>(names.size()));

    graph.AddEdge(0, 1, 2);  // S-A
    graph.AddEdge(0, 2, 5);  // S-B
    graph.AddEdge(1, 3, 2);  // A-C
    graph.AddEdge(1, 4, 4);  // A-D
    graph.AddEdge(2, 4, 1);  // B-D
    graph.AddEdge(2, 5, 5);  // B-E
    graph.AddEdge(3, 4, 1);  // C-D
    graph.AddEdge(3, 6, 7);  // C-G
    graph.AddEdge(4, 5, 2);  // D-E
    graph.AddEdge(4, 6, 4);  // D-G
    graph.AddEdge(5, 6, 1);  // E-G

    const WeightedGraph::Vertex start = 0;
    const WeightedGraph::Vertex goal = 6;

    // 每个值都不超过该顶点到 G 的真实最短距离。
    const std::vector<int> heuristic = {7, 5, 3, 3, 2, 1, 0};

    PrintResult("Dijkstra：", graph.Dijkstra(start, goal), names);
    PrintResult("A*：", graph.AStar(start, goal, heuristic), names);
    return 0;
}
