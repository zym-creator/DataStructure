#include <algorithm>
#include <iostream>

class AVLTree {
public:
    using ElementType = int;

    AVLTree() = default;
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    ~AVLTree() {
        Destroy(root_);
    }

    void Insert(ElementType value) {
        root_ = InsertNode(root_, value);
    }

    bool Delete(ElementType value) {
        bool deleted = false;
        root_ = DeleteNode(root_, value, deleted);
        return deleted;
    }

    bool Contains(ElementType value) const {
        const Node* current = root_;
        while (current != nullptr) {
            if (value < current->data) {
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                return true;
            }
        }
        return false;
    }

    int Height() const {
        return GetHeight(root_);
    }

    void PrintInOrder() const {
        InOrder(root_);
        std::cout << '\n';
    }

private:
    struct Node {
        ElementType data;
        int height;
        Node* left;
        Node* right;
    };

    static int GetHeight(const Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    static void UpdateHeight(Node* node) {
        node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    }

    static int GetBalanceFactor(const Node* node) {
        return node == nullptr ? 0 : GetHeight(node->left) - GetHeight(node->right);
    }

    static Node* RotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* transferredSubtree = newRoot->right;

        newRoot->right = node;
        node->left = transferredSubtree;

        UpdateHeight(node);
        UpdateHeight(newRoot);
        return newRoot;
    }

    static Node* RotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* transferredSubtree = newRoot->left;

        newRoot->left = node;
        node->right = transferredSubtree;

        UpdateHeight(node);
        UpdateHeight(newRoot);
        return newRoot;
    }

    static Node* Balance(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        UpdateHeight(node);
        const int balanceFactor = GetBalanceFactor(node);

        if (balanceFactor > 1) {
            if (GetBalanceFactor(node->left) < 0) {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        }

        if (balanceFactor < -1) {
            if (GetBalanceFactor(node->right) > 0) {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        }

        return node;
    }

    static Node* InsertNode(Node* node, ElementType value) {
        if (node == nullptr) {
            return new Node{value, 1, nullptr, nullptr};
        }

        if (value < node->data) {
            node->left = InsertNode(node->left, value);
        } else if (value > node->data) {
            node->right = InsertNode(node->right, value);
        } else {
            return node;
        }

        return Balance(node);
    }

    static Node* FindMinNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
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

            if (node->left == nullptr || node->right == nullptr) {
                Node* child = node->left != nullptr ? node->left : node->right;
                delete node;
                return child;
            }

            Node* successor = FindMinNode(node->right);
            node->data = successor->data;
            bool successorDeleted = false;
            node->right = DeleteNode(node->right, successor->data, successorDeleted);
        }

        return Balance(node);
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
    AVLTree tree;
    int values[] = {30, 20, 10, 25, 28, 40, 50, 45};

    for (int value : values) {
        tree.Insert(value);
    }

    std::cout << "中序遍历：";
    tree.PrintInOrder();
    std::cout << "树高：" << tree.Height() << '\n';
    std::cout << "是否包含 28：" << (tree.Contains(28) ? "是" : "否") << '\n';

    tree.Delete(30);
    std::cout << "删除 30 后的中序遍历：";
    tree.PrintInOrder();
    std::cout << "删除后的树高：" << tree.Height() << '\n';
    return 0;
}
