#include <iostream>

class AdjacencyListGraph {
public:
    using Vertex = int;
    using WeightType = int;

    explicit AdjacencyListGraph(int vertexCount)
        : heads_(vertexCount > 0 ? new EdgeNode*[vertexCount] : nullptr),
          vertexCount_(vertexCount > 0 ? vertexCount : 0),
          edgeCount_(0) {
        for (int i = 0; i < vertexCount_; ++i) {
            heads_[i] = nullptr;
        }
    }

    AdjacencyListGraph(const AdjacencyListGraph&) = delete;
    AdjacencyListGraph& operator=(const AdjacencyListGraph&) = delete;

    ~AdjacencyListGraph() {
        Clear();
        delete[] heads_;
    }

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) ||
            first == second || weight < 0) {
            return false;
        }

        EdgeNode* firstEdge = FindEdge(first, second);
        if (firstEdge != nullptr) {
            firstEdge->weight = weight;
            FindEdge(second, first)->weight = weight;
            return true;
        }

        heads_[first] = new EdgeNode{second, weight, heads_[first]};
        heads_[second] = new EdgeNode{first, weight, heads_[second]};
        ++edgeCount_;
        return true;
    }

    bool RemoveEdge(Vertex first, Vertex second) {
        if (!HasEdge(first, second)) {
            return false;
        }

        RemoveDirectedEdge(first, second);
        RemoveDirectedEdge(second, first);
        --edgeCount_;
        return true;
    }

    bool HasEdge(Vertex first, Vertex second) const {
        return IsValidVertex(first) && IsValidVertex(second) &&
               FindEdge(first, second) != nullptr;
    }

    bool GetWeight(Vertex first, Vertex second, WeightType& weight) const {
        if (!IsValidVertex(first) || !IsValidVertex(second)) {
            return false;
        }

        const EdgeNode* edge = FindEdge(first, second);
        if (edge == nullptr) {
            return false;
        }

        weight = edge->weight;
        return true;
    }

    int Degree(Vertex vertex) const {
        if (!IsValidVertex(vertex)) {
            return -1;
        }

        int degree = 0;
        for (const EdgeNode* edge = heads_[vertex];
             edge != nullptr;
             edge = edge->next) {
            ++degree;
        }
        return degree;
    }

    int VertexCount() const {
        return vertexCount_;
    }

    int EdgeCount() const {
        return edgeCount_;
    }

    void Print() const {
        for (int vertex = 0; vertex < vertexCount_; ++vertex) {
            std::cout << vertex << " : ";
            for (const EdgeNode* edge = heads_[vertex];
                 edge != nullptr;
                 edge = edge->next) {
                std::cout << "(" << edge->adjacent
                          << ", 权重=" << edge->weight << ") ";
            }
            std::cout << '\n';
        }
    }

private:
    struct EdgeNode {
        Vertex adjacent;
        WeightType weight;
        EdgeNode* next;
    };

    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 && vertex < vertexCount_;
    }

    EdgeNode* FindEdge(Vertex from, Vertex to) const {
        EdgeNode* current = heads_[from];
        while (current != nullptr && current->adjacent != to) {
            current = current->next;
        }
        return current;
    }

    void RemoveDirectedEdge(Vertex from, Vertex to) {
        EdgeNode* current = heads_[from];
        EdgeNode* previous = nullptr;

        while (current->adjacent != to) {
            previous = current;
            current = current->next;
        }

        if (previous == nullptr) {
            heads_[from] = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }

    void Clear() {
        for (int vertex = 0; vertex < vertexCount_; ++vertex) {
            EdgeNode* current = heads_[vertex];
            while (current != nullptr) {
                EdgeNode* nodeToDelete = current;
                current = current->next;
                delete nodeToDelete;
            }
            heads_[vertex] = nullptr;
        }
        edgeCount_ = 0;
    }

    EdgeNode** heads_;
    int vertexCount_;
    int edgeCount_;
};

int main() {
    int vertexCount;
    int edgeCount;

    std::cout << "请输入顶点数和边数：";
    if (!(std::cin >> vertexCount >> edgeCount) ||
        vertexCount < 0 || edgeCount < 0) {
        std::cout << "顶点数和边数必须是非负整数\n";
        return 1;
    }

    AdjacencyListGraph graph(vertexCount);
    std::cout << "请依次输入每条边的两个顶点和权重：\n";
    for (int i = 0; i < edgeCount; ++i) {
        int first;
        int second;
        int weight;
        if (!(std::cin >> first >> second >> weight)) {
            std::cout << "边数据输入无效\n";
            return 1;
        }
        if (!graph.AddEdge(first, second, weight)) {
            std::cout << "无法插入边 " << first << " - " << second << '\n';
            return 1;
        }
    }

    std::cout << "邻接表：\n";
    graph.Print();
    std::cout << "顶点数：" << graph.VertexCount() << '\n';
    std::cout << "边数：" << graph.EdgeCount() << '\n';
    return 0;
}
