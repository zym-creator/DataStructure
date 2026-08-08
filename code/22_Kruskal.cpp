#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSet {
public:
    explicit DisjointSet(int size) : parents_(size, -1) {}

    int Find(int element) {
        if (parents_[element] < 0) {
            return element;
        }

        parents_[element] = Find(parents_[element]);
        return parents_[element];
    }

    bool Union(int first, int second) {
        int firstRoot = Find(first);
        int secondRoot = Find(second);
        if (firstRoot == secondRoot) {
            return false;
        }

        if (parents_[firstRoot] > parents_[secondRoot]) {
            std::swap(firstRoot, secondRoot);
        }

        parents_[firstRoot] += parents_[secondRoot];
        parents_[secondRoot] = firstRoot;
        return true;
    }

private:
    std::vector<int> parents_;
};

class KruskalGraph {
public:
    using Vertex = int;
    using WeightType = long long;

    struct Edge {
        Vertex first;
        Vertex second;
        WeightType weight;
    };

    struct MSTResult {
        bool connected;
        WeightType totalWeight;
        std::vector<Edge> edges;
    };

    explicit KruskalGraph(int vertexCount)
        : vertexCount_(vertexCount > 0 ? vertexCount : 0) {}

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) || first == second) {
            return false;
        }

        edges_.push_back(Edge{first, second, weight});
        return true;
    }

    MSTResult Kruskal() const {
        std::vector<Edge> sortedEdges = edges_;
        std::sort(sortedEdges.begin(), sortedEdges.end(),
                  [](const Edge& first, const Edge& second) {
                      return first.weight < second.weight;
                  });

        DisjointSet sets(vertexCount_);
        MSTResult result{true, 0, {}};

        for (const Edge& edge : sortedEdges) {
            if (sets.Union(edge.first, edge.second)) {
                result.edges.push_back(edge);
                result.totalWeight += edge.weight;

                if (result.edges.size() + 1 ==
                    static_cast<std::size_t>(vertexCount_)) {
                    break;
                }
            }
        }

        result.connected = vertexCount_ > 0 &&
                           result.edges.size() + 1 ==
                               static_cast<std::size_t>(vertexCount_);
        return result;
    }

private:
    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 && vertex < vertexCount_;
    }

    int vertexCount_;
    std::vector<Edge> edges_;
};

int main() {
    int vertexCount;
    int edgeCount;
    std::cout << "请输入顶点数和边数：";
    if (!(std::cin >> vertexCount >> edgeCount) ||
        vertexCount < 0 || edgeCount < 0) {
        std::cout << "输入无效\n";
        return 1;
    }

    KruskalGraph graph(vertexCount);
    std::cout << "请输入每条无向边的两个顶点和权重：\n";
    for (int i = 0; i < edgeCount; ++i) {
        int first;
        int second;
        long long weight;
        if (!(std::cin >> first >> second >> weight) ||
            !graph.AddEdge(first, second, weight)) {
            std::cout << "边数据无效\n";
            return 1;
        }
    }

    const KruskalGraph::MSTResult result = graph.Kruskal();
    if (!result.connected) {
        std::cout << "图不连通，不存在最小生成树\n";
        return 0;
    }

    std::cout << "Kruskal 选中的边：\n";
    for (const KruskalGraph::Edge& edge : result.edges) {
        std::cout << edge.first << " - " << edge.second
                  << "，权重=" << edge.weight << '\n';
    }
    std::cout << "总权重：" << result.totalWeight << '\n';
    return 0;
}
