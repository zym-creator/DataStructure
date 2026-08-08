#include <iostream>
#include <limits>
#include <vector>

class FloydGraph {
public:
    using Vertex = int;
    using WeightType = long long;

    explicit FloydGraph(int vertexCount)
        : vertexCount_(vertexCount > 0 ? vertexCount : 0),
          distance_(vertexCount_, std::vector<WeightType>(vertexCount_, Infinity)),
          next_(vertexCount_, std::vector<Vertex>(vertexCount_, -1)) {
        for (Vertex vertex = 0; vertex < vertexCount_; ++vertex) {
            distance_[vertex][vertex] = 0;
            next_[vertex][vertex] = vertex;
        }
    }

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) ||
            first == second || weight < 0) {
            return false;
        }

        if (weight < distance_[first][second]) {
            distance_[first][second] = weight;
            distance_[second][first] = weight;
            next_[first][second] = second;
            next_[second][first] = first;
        }
        return true;
    }

    void FloydWarshall() {
        for (Vertex middle = 0; middle < vertexCount_; ++middle) {
            for (Vertex from = 0; from < vertexCount_; ++from) {
                if (distance_[from][middle] == Infinity) {
                    continue;
                }

                for (Vertex to = 0; to < vertexCount_; ++to) {
                    if (distance_[middle][to] == Infinity) {
                        continue;
                    }

                    const WeightType throughMiddle =
                        distance_[from][middle] + distance_[middle][to];
                    if (throughMiddle < distance_[from][to]) {
                        distance_[from][to] = throughMiddle;
                        next_[from][to] = next_[from][middle];
                    }
                }
            }
        }
    }

    bool Distance(Vertex from, Vertex to, WeightType& result) const {
        if (!IsValidVertex(from) || !IsValidVertex(to) ||
            distance_[from][to] == Infinity) {
            return false;
        }

        result = distance_[from][to];
        return true;
    }

    std::vector<Vertex> BuildPath(Vertex from, Vertex to) const {
        if (!IsValidVertex(from) || !IsValidVertex(to) || next_[from][to] == -1) {
            return {};
        }

        std::vector<Vertex> path{from};
        while (from != to) {
            from = next_[from][to];
            path.push_back(from);
        }
        return path;
    }

    void PrintDistances() const {
        for (Vertex from = 0; from < vertexCount_; ++from) {
            for (Vertex to = 0; to < vertexCount_; ++to) {
                if (distance_[from][to] == Infinity) {
                    std::cout << "- ";
                } else {
                    std::cout << distance_[from][to] << ' ';
                }
            }
            std::cout << '\n';
        }
    }

private:
    static constexpr WeightType Infinity =
        std::numeric_limits<WeightType>::max() / 4;

    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 && vertex < vertexCount_;
    }

    int vertexCount_;
    std::vector<std::vector<WeightType>> distance_;
    std::vector<std::vector<Vertex>> next_;
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

    FloydGraph graph(vertexCount);
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

    graph.FloydWarshall();
    std::cout << "最短距离矩阵：\n";
    graph.PrintDistances();

    if (vertexCount > 1) {
        const int start = 0;
        const int goal = vertexCount - 1;
        const std::vector<int> path = graph.BuildPath(start, goal);
        std::cout << start << " 到 " << goal << " 的路径：";
        if (path.empty()) {
            std::cout << "不可达\n";
        } else {
            for (int i = 0; i < static_cast<int>(path.size()); ++i) {
                if (i > 0) {
                    std::cout << " -> ";
                }
                std::cout << path[i];
            }
            long long distance;
            graph.Distance(start, goal, distance);
            std::cout << "，距离：" << distance << '\n';
        }
    }
    return 0;
}
