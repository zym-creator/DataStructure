#include <iostream>

class BinarySearchTree {
public:
    using ElementType = int;

    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    ~BinarySearchTree() {
        Destroy(root_);
    }

    void Insert(ElementType value) {
        root_ = InsertNode(root_, value);
    }

    bool Contains(ElementType value) const {
        return FindNode(root_, value) != nullptr;
    }

    bool FindMin(ElementType& value) const {
        const Node* node = FindMinNode(root_);
        if (node == nullptr) {
            return false;
        }
        value = node->data;
        return true;
    }

    bool FindMax(ElementType& value) const {
        const Node* node = FindMaxNode(root_);
        if (node == nullptr) {
            return false;
        }
        value = node->data;
        return true;
    }

    bool Delete(ElementType value) {
        bool deleted = false;
        root_ = DeleteNode(root_, value, deleted);
        return deleted;
    }

    void PrintInOrder() const {
        InOrder(root_);
        std::cout << '\n';
    }

private:
    struct Node {
        ElementType data;
        Node* left;
        Node* right;
    };

    static Node* InsertNode(Node* node, ElementType value) {
        if (node == nullptr) {
            return new Node{value, nullptr, nullptr};
        }
        if (value < node->data) {
            node->left = InsertNode(node->left, value);
        } else if (value > node->data) {
            node->right = InsertNode(node->right, value);
        }
        return node;
    }

    static const Node* FindNode(const Node* node, ElementType value) {
        while (node != nullptr) {
            if (value < node->data) {
                node = node->left;
            } else if (value > node->data) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    static const Node* FindMinNode(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    static const Node* FindMaxNode(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    static Node* DeleteNode(Node* node, ElementType value, bool& deleted) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = DeleteNode(node->left, value, deleted);
        } else if (value > node->data) {
            node->right = DeleteNode(node->right, value, deleted);
        } else {
            deleted = true;

            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }

            const Node* successor = FindMinNode(node->right);
            node->data = successor->data;
            bool successorDeleted = false;
            node->right = DeleteNode(node->right, successor->data, successorDeleted);
        }
        return node;
    }

    static void InOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }
        InOrder(node->left);
        std::cout << node->data << ' ';
        InOrder(node->right);
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
    BinarySearchTree tree;
    int values[] = {5, 7, 3, 1, 2, 4, 6, 8, 9};

    for (int value : values) {
        tree.Insert(value);
    }

    std::cout << "中序遍历：";
    tree.PrintInOrder();

    int value = 0;
    if (tree.FindMin(value)) {
        std::cout << "最小值：" << value << '\n';
    }
    if (tree.FindMax(value)) {
        std::cout << "最大值：" << value << '\n';
    }

    std::cout << "是否包含 3：" << (tree.Contains(3) ? "是" : "否") << '\n';

    if (tree.Delete(5)) {
        std::cout << "已删除根节点 5\n";
    }
    std::cout << "删除后的中序遍历：";
    tree.PrintInOrder();
    return 0;
}
