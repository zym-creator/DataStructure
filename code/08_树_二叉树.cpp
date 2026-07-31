#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

struct TreeNode {
    int value;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    explicit TreeNode(int value) : value(value) {}
};

void preorder(const TreeNode* node, std::vector<int>& output) {
    if (node == nullptr) return;
    output.push_back(node->value);
    preorder(node->left.get(), output);
    preorder(node->right.get(), output);
}

void inorderIterative(const TreeNode* root, std::vector<int>& output) {
    std::stack<const TreeNode*> pending;
    const TreeNode* current = root;
    while (current != nullptr || !pending.empty()) {
        while (current != nullptr) {
            pending.push(current);
            current = current->left.get();
        }
        current = pending.top();
        pending.pop();
        output.push_back(current->value);
        current = current->right.get();
    }
}

std::vector<int> levelOrder(const TreeNode* root) {
    std::vector<int> output;
    if (root == nullptr) return output;
    std::queue<const TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        const TreeNode* node = nodes.front();
        nodes.pop();
        output.push_back(node->value);
        if (node->left) nodes.push(node->left.get());
        if (node->right) nodes.push(node->right.get());
    }
    return output;
}

std::size_t height(const TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + std::max(height(node->left.get()), height(node->right.get()));
}

std::size_t countLeaves(const TreeNode* node) {
    if (node == nullptr) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left.get()) + countLeaves(node->right.get());
}

void print(const std::vector<int>& values) {
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    auto root = std::make_unique<TreeNode>(1);
    root->left = std::make_unique<TreeNode>(2);
    root->right = std::make_unique<TreeNode>(3);
    root->left->left = std::make_unique<TreeNode>(4);
    root->left->right = std::make_unique<TreeNode>(5);

    std::vector<int> values;
    preorder(root.get(), values);
    std::cout << "先序: "; print(values);
    values.clear();
    inorderIterative(root.get(), values);
    std::cout << "中序(非递归): "; print(values);
    std::cout << "层序: "; print(levelOrder(root.get()));
    std::cout << "高度: " << height(root.get()) << ", 叶子数: " << countLeaves(root.get()) << '\n';
}
