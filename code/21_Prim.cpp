#include <iostream>
#include <queue>
#include <vector>

class PrimGraph {
public:
    using Vertex = int;
    using WeightType = long long;

    struct TreeEdge {
        Vertex from;
        Vertex to;
        WeightType weight;
    };

    struct MSTResult {
        bool connected;
        WeightType totalWeight;
        std::vector<TreeEdge> edges;
    };

    explicit PrimGraph(int vertexCount)
        : adjacency_(vertexCount > 0 ? vertexCount : 0) {}

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) || first == second) {
            return false;
        }

        adjacency_[first].push_back(Edge{second, weight});
        adjacency_[second].push_back(Edge{first, weight});
        return true;
    }

    MSTResult Prim(Vertex start) const {
        if (!IsValidVertex(start)) {
            return MSTResult{false, 0, {}};
        }

        std::vector<bool> collected(adjacency_.size(), false);
        std::priority_queue<Candidate, std::vector<Candidate>, CompareCandidate> open;
        MSTResult result{true, 0, {}};

        collected[start] = true;
        AddCandidates(start, collected, open);

        while (!open.empty() &&
               result.edges.size() + 1 < adjacency_.size()) {
            const Candidate candidate = open.top();
            open.pop();

            if (collected[candidate.to]) {
                continue;
            }

            collected[candidate.to] = true;
            result.edges.push_back(
                TreeEdge{candidate.from, candidate.to, candidate.weight});
            result.totalWeight += candidate.weight;
            AddCandidates(candidate.to, collected, open);
        }

        result.connected = adjacency_.empty() ||
                           result.edges.size() + 1 == adjacency_.size();
        return result;
    }

private:
    struct Edge {
        Vertex to;
        WeightType weight;
    };

    struct Candidate {
        Vertex from;
        Vertex to;
        WeightType weight;
    };

    struct CompareCandidate {
        bool operator()(const Candidate& first, const Candidate& second) const {
            return first.weight > second.weight;
        }
    };

    void AddCandidates(
        Vertex from,
        const std::vector<bool>& collected,
        std::priority_queue<Candidate,
                            std::vector<Candidate>,
                            CompareCandidate>& open) const {
        for (const Edge& edge : adjacency_[from]) {
            if (!collected[edge.to]) {
                open.push(Candidate{from, edge.to, edge.weight});
            }
        }
    }

    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 &&
               vertex < static_cast<Vertex>(adjacency_.size());
    }

    std::vector<std::vector<Edge>> adjacency_;
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

    PrimGraph graph(vertexCount);
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

    if (vertexCount == 0) {
        std::cout << "空图没有最小生成树\n";
        return 0;
    }

    const PrimGraph::MSTResult result = graph.Prim(0);
    if (!result.connected) {
        std::cout << "图不连通，不存在最小生成树\n";
        return 0;
    }

    std::cout << "Prim 选中的边：\n";
    for (const PrimGraph::TreeEdge& edge : result.edges) {
        std::cout << edge.from << " - " << edge.to
                  << "，权重=" << edge.weight << '\n';
    }
    std::cout << "总权重：" << result.totalWeight << '\n';
    return 0;
}
