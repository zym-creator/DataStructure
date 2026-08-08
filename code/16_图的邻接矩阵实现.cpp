#include <iostream>

class MatrixGraph {
public:
    using Vertex = int;
    using WeightType = int;

    explicit MatrixGraph(int vertexCount)
        : matrix_(vertexCount > 0
                      ? new WeightType[vertexCount * vertexCount]
                      : nullptr),
          vertexCount_(vertexCount > 0 ? vertexCount : 0),
          edgeCount_(0) {
        for (int row = 0; row < vertexCount_; ++row) {
            for (int column = 0; column < vertexCount_; ++column) {
                matrix_[Index(row, column)] =
                    row == column ? 0 : NoEdge;
            }
        }
    }

    MatrixGraph(const MatrixGraph&) = delete;
    MatrixGraph& operator=(const MatrixGraph&) = delete;

    ~MatrixGraph() {
        delete[] matrix_;
    }

    bool AddEdge(Vertex first, Vertex second, WeightType weight) {
        if (!IsValidVertex(first) || !IsValidVertex(second) ||
            first == second || weight < 0) {
            return false;
        }

        if (!HasEdge(first, second)) {
            ++edgeCount_;
        }

        matrix_[Index(first, second)] = weight;
        matrix_[Index(second, first)] = weight;
        return true;
    }

    bool RemoveEdge(Vertex first, Vertex second) {
        if (!HasEdge(first, second)) {
            return false;
        }

        matrix_[Index(first, second)] = NoEdge;
        matrix_[Index(second, first)] = NoEdge;
        --edgeCount_;
        return true;
    }

    bool HasEdge(Vertex first, Vertex second) const {
        return IsValidVertex(first) && IsValidVertex(second) &&
               first != second && matrix_[Index(first, second)] != NoEdge;
    }

    bool GetWeight(Vertex first, Vertex second, WeightType& weight) const {
        if (!HasEdge(first, second)) {
            return false;
        }

        weight = matrix_[Index(first, second)];
        return true;
    }

    int Degree(Vertex vertex) const {
        if (!IsValidVertex(vertex)) {
            return -1;
        }

        int degree = 0;
        for (int adjacent = 0; adjacent < vertexCount_; ++adjacent) {
            if (HasEdge(vertex, adjacent)) {
                ++degree;
            }
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
        std::cout << "    ";
        for (int vertex = 0; vertex < vertexCount_; ++vertex) {
            std::cout << vertex << ' ';
        }
        std::cout << '\n';

        for (int row = 0; row < vertexCount_; ++row) {
            std::cout << row << " : ";
            for (int column = 0; column < vertexCount_; ++column) {
                const WeightType weight = matrix_[Index(row, column)];
                if (weight == NoEdge) {
                    std::cout << "- ";
                } else {
                    std::cout << weight << ' ';
                }
            }
            std::cout << '\n';
        }
    }

private:
    static constexpr WeightType NoEdge = -1;

    bool IsValidVertex(Vertex vertex) const {
        return vertex >= 0 && vertex < vertexCount_;
    }

    int Index(Vertex row, Vertex column) const {
        return row * vertexCount_ + column;
    }

    WeightType* matrix_;
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

    MatrixGraph graph(vertexCount);
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

    std::cout << "邻接矩阵：\n";
    graph.Print();
    std::cout << "顶点数：" << graph.VertexCount() << '\n';
    std::cout << "边数：" << graph.EdgeCount() << '\n';
    return 0;
}
