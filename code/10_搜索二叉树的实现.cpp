#include <iostream>

struct Node {
    using ElementType = int;
    ElementType data;
    Node* left;
    Node* right;

    Node(ElementType value)
        : data(value), left(nullptr), right(nullptr) {
    }
};

class BinTree {
public:
    using ElementType = int;

    BinTree() = default;
    BinTree(const BinTree&) = delete;
    BinTree& operator=(const BinTree&) = delete;

    ~BinTree() {
        Destroy(root);
    }

    Node* PositionFind(ElementType value) const {
        Node* current = root;
        while(current != nullptr) {
            if(value < current->data) {
                current = current->left;
            } else if(value > current->data) {
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    Node* Insert(ElementType value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return newNode;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                delete newNode; 
                return nullptr;
            }
        }

        if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        return newNode;
    }

    Node* Findmin() const {
        Node* current = root;
        if (current == nullptr) {
            return nullptr;
        }
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* Findmax() const {
        Node* current = root;
        if (current == nullptr) {
            return nullptr;
        }
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    void Delete(ElementType value) {
        Node* current = nullptr;
        current = PositionFind(value);

        if (current == nullptr) {
            return;
        } else {
            if(current->left != nullptr && current->right != nullptr) {
                Node* successor = Findmin();
                current->data = successor->data;
                Delete(successor->data);
            } else {
                Node* child = (current->left != nullptr) ? current->left : current->right;

                if (current == root) {
                    root = child;
                } else {
                    Node* parent = root;
                    while (parent != nullptr) {
                        if (current->data < parent->data) {
                            if (parent->left == current) {
                                parent->left = child;
                                break;
                            }
                            parent = parent->left;
                        } else {
                            if (parent->right == current) {
                                parent->right = child;
                                break;
                            }
                            parent = parent->right;
                        }
                    }
                }
                delete current;
            }
        }
    }

private:
    Node* root = nullptr;

    void Destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }

};

int main() {
    BinTree tree;

    for(int i = 0; i < 10; ++i) {
        tree.Insert(i);
    }

    return 0;
}