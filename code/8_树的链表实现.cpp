#include <iostream>

class BinaryTree {
public:
    using ElementType = int;

    BinaryTree() {
        root_ = CreateExampleTree();
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    ~BinaryTree() {
        Destroy(root_);
    }

    bool IsEmpty() const {
        return root_ == nullptr;
    }

    void PrintPreOrder() const {
        PreOrder(root_);
        std::cout << '\n';
    }

    void PrintInOrder() const {
        InOrder(root_);
        std::cout << '\n';
    }

    void PrintPostOrder() const {
        PostOrder(root_);
        std::cout << '\n';
    }

    void PrintLevelOrder() const {
        if (root_ == nullptr) {
            std::cout << '\n';
            return;
        }

        NodeQueue queue;
        queue.Enqueue(root_);

        Node* current = nullptr;
        while (queue.Dequeue(current)) {
            std::cout << current->data << ' ';
            if (current->left != nullptr) {
                queue.Enqueue(current->left);
            }
            if (current->right != nullptr) {
                queue.Enqueue(current->right);
            }
        }
        std::cout << '\n';
    }

    void PrintLeaves() const {
        PrintLeafNodes(root_);
        std::cout << '\n';
    }

    int Height() const {
        return GetHeight(root_);
    }

private:
    struct Node {
        ElementType data;
        Node* left;
        Node* right;
    };

    class NodeQueue {
    public:
        ~NodeQueue() {
            Node* unused = nullptr;
            while (Dequeue(unused)) {
            }
        }

        void Enqueue(Node* treeNode) {
            QueueNode* newNode = new QueueNode{treeNode, nullptr};
            if (rear_ == nullptr) {
                front_ = newNode;
                rear_ = newNode;
            } else {
                rear_->next = newNode;
                rear_ = newNode;
            }
        }

        bool Dequeue(Node*& treeNode) {
            if (front_ == nullptr) {
                return false;
            }

            QueueNode* nodeToDelete = front_;
            treeNode = nodeToDelete->treeNode;
            front_ = front_->next;
            if (front_ == nullptr) {
                rear_ = nullptr;
            }
            delete nodeToDelete;
            return true;
        }

    private:
        struct QueueNode {
            Node* treeNode;
            QueueNode* next;
        };

        QueueNode* front_ = nullptr;
        QueueNode* rear_ = nullptr;
    };

    static Node* CreateNode(ElementType value) {
        return new Node{value, nullptr, nullptr};
    }

    static Node* CreateExampleTree() {
        Node* root = CreateNode(1);
        root->left = CreateNode(2);
        root->right = CreateNode(3);
        root->left->left = CreateNode(4);
        root->left->right = CreateNode(6);
        root->left->right->left = CreateNode(5);
        root->right->left = CreateNode(7);
        root->right->right = CreateNode(9);
        root->right->left->right = CreateNode(8);
        return root;
    }

    static void PreOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << ' ';
        PreOrder(node->left);
        PreOrder(node->right);
    }

    static void InOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }
        InOrder(node->left);
        std::cout << node->data << ' ';
        InOrder(node->right);
    }

    static void PostOrder(const Node* node) {
        if (node == nullptr) {
            return;
        }
        PostOrder(node->left);
        PostOrder(node->right);
        std::cout << node->data << ' ';
    }

    static void PrintLeafNodes(const Node* node) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            std::cout << node->data << ' ';
        }
        PrintLeafNodes(node->left);
        PrintLeafNodes(node->right);
    }

    static int GetHeight(const Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = GetHeight(node->left);
        int rightHeight = GetHeight(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
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
    BinaryTree tree;

    std::cout << "先序遍历：";
    tree.PrintPreOrder();
    std::cout << "中序遍历：";
    tree.PrintInOrder();
    std::cout << "后序遍历：";
    tree.PrintPostOrder();
    std::cout << "层序遍历：";
    tree.PrintLevelOrder();
    std::cout << "叶子节点：";
    tree.PrintLeaves();
    std::cout << "树的高度：" << tree.Height() << '\n';
    return 0;
}
