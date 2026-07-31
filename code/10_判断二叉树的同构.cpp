#include <iostream>

struct TreeNode {
    using ElementType = int;

    ElementType data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(ElementType value)
        : data(value), left(nullptr), right(nullptr) {
    }
};

class BinaryTree {
public:
    using ElementType = int;

    BinaryTree() = default;
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    ~BinaryTree() {
        Destroy(root_);
    }

    TreeNode* CreateRoot(ElementType value) {
        if (root_ != nullptr) {
            return nullptr;
        }
        root_ = new TreeNode(value);
        return root_;
    }

    TreeNode* AddLeft(TreeNode* parent, ElementType value) {
        if (parent == nullptr || parent->left != nullptr) {
            return nullptr;
        }
        parent->left = new TreeNode(value);
        return parent->left;
    }

    TreeNode* AddRight(TreeNode* parent, ElementType value) {
        if (parent == nullptr || parent->right != nullptr) {
            return nullptr;
        }
        parent->right = new TreeNode(value);
        return parent->right;
    }

    const TreeNode* Root() const {
        return root_;
    }

private:
    static void Destroy(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }

    TreeNode* root_ = nullptr;
};

bool AreIsomorphic(const TreeNode* first, const TreeNode* second) {
    if (first == nullptr && second == nullptr) {
        return true;
    }
    if (first == nullptr || second == nullptr) {
        return false;
    }
    if (first->data != second->data) {
        return false;
    }

    bool noSwap = AreIsomorphic(first->left, second->left)
               && AreIsomorphic(first->right, second->right);

    bool withSwap = AreIsomorphic(first->left, second->right)
                 && AreIsomorphic(first->right, second->left);

    return noSwap || withSwap;
}

int main() {
    BinaryTree firstTree;
    TreeNode* firstRoot = firstTree.CreateRoot(1);
    TreeNode* firstNode2 = firstTree.AddLeft(firstRoot, 2);
    TreeNode* firstNode3 = firstTree.AddRight(firstRoot, 3);
    firstTree.AddLeft(firstNode2, 4);
    firstTree.AddRight(firstNode3, 5);

    BinaryTree secondTree;
    TreeNode* secondRoot = secondTree.CreateRoot(1);
    TreeNode* secondNode3 = secondTree.AddLeft(secondRoot, 3);
    TreeNode* secondNode2 = secondTree.AddRight(secondRoot, 2);
    secondTree.AddLeft(secondNode3, 5);
    secondTree.AddRight(secondNode2, 4);

    if (AreIsomorphic(firstTree.Root(), secondTree.Root())) {
        std::cout << "两棵二叉树同构\n";
    } else {
        std::cout << "两棵二叉树不同构\n";
    }

    return 0;
}
