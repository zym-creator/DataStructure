#include <iostream>
#include <queue>
#include <vector>

class HuffmanTree {
public:
    using WeightType = int;

    HuffmanTree() = default;
    HuffmanTree(const HuffmanTree&) = delete;
    HuffmanTree& operator=(const HuffmanTree&) = delete;

    ~HuffmanTree() {
        Destroy(root_);
    }

    bool Build(const WeightType weights[], int count) {
        Destroy(root_);
        root_ = nullptr;

        if (weights == nullptr || count <= 0) {
            return false;
        }

        std::priority_queue<Node*, std::vector<Node*>, CompareNode> minHeap;
        int creationOrder = 0;

        for (int i = 0; i < count; ++i) {
            if (weights[i] < 0) {
                DestroyHeapTrees(minHeap);
                return false;
            }

            minHeap.push(new Node{weights[i], creationOrder++, nullptr, nullptr});
        }

        while (minHeap.size() > 1) {
            Node* left = minHeap.top();
            minHeap.pop();

            Node* right = minHeap.top();
            minHeap.pop();

            Node* parent = new Node{
                left->weight + right->weight,
                creationOrder++,
                left,
                right
            };
            minHeap.push(parent);
        }

        root_ = minHeap.top();
        return true;
    }

    bool IsEmpty() const {
        return root_ == nullptr;
    }

    WeightType TotalWeight() const {
        return IsEmpty() ? 0 : root_->weight;
    }

    long long WeightedPathLength() const {
        return CalculateWPL(root_, 0);
    }

    void PrintPreOrder() const {
        PrintPreOrder(root_);
        std::cout << '\n';
    }

private:
    struct Node {
        WeightType weight;
        int order;
        Node* left;
        Node* right;
    };

    struct CompareNode {
        bool operator()(const Node* first, const Node* second) const {
            if (first->weight != second->weight) {
                return first->weight > second->weight;
            }
            return first->order > second->order;
        }
    };

    using MinHeap = std::priority_queue<Node*, std::vector<Node*>, CompareNode>;

    static void DestroyHeapTrees(MinHeap& minHeap) {
        while (!minHeap.empty()) {
            Destroy(minHeap.top());
            minHeap.pop();
        }
    }

    static long long CalculateWPL(const Node* node, int depth) {
        if (node == nullptr) {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr) {
            return static_cast<long long>(node->weight) * depth;
        }

        return CalculateWPL(node->left, depth + 1) +
               CalculateWPL(node->right, depth + 1);
    }

    static void PrintPreOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }

        std::cout << node->weight << ' ';
        PrintPreOrder(node->left);
        PrintPreOrder(node->right);
    }

    static void Destroy(Node* node) {
        if (node == nullptr) {
            return;
        }

        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }

    Node* root_ = nullptr;
};

int main() {
    const int weights[] = {13, 1, 45, 7, 20, 4, 19, 13, 40, 33, 38};
    const int count = static_cast<int>(sizeof(weights) / sizeof(weights[0]));

    HuffmanTree tree;
    if (!tree.Build(weights, count)) {
        std::cout << "哈夫曼树建立失败\n";
        return 1;
    }

    std::cout << "先序遍历：";
    tree.PrintPreOrder();
    std::cout << "总权值：" << tree.TotalWeight() << '\n';
    std::cout << "带权路径长度：" << tree.WeightedPathLength() << '\n';
    return 0;
}
