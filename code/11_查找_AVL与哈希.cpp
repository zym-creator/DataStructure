#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

std::size_t lowerBound(const std::vector<int>& values, int target) {
    std::size_t left = 0;
    std::size_t right = values.size();
    while (left < right) {
        const auto mid = left + (right - left) / 2;
        if (values[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}

struct AvlNode {
    int key;
    int height = 1;
    std::unique_ptr<AvlNode> left;
    std::unique_ptr<AvlNode> right;
    explicit AvlNode(int key) : key(key) {}
};

int height(const std::unique_ptr<AvlNode>& node) { return node ? node->height : 0; }
void update(AvlNode& node) { node.height = 1 + std::max(height(node.left), height(node.right)); }

std::unique_ptr<AvlNode> rotateRight(std::unique_ptr<AvlNode> root) {
    auto newRoot = std::move(root->left);
    root->left = std::move(newRoot->right);
    update(*root);
    newRoot->right = std::move(root);
    update(*newRoot);
    return newRoot;
}

std::unique_ptr<AvlNode> rotateLeft(std::unique_ptr<AvlNode> root) {
    auto newRoot = std::move(root->right);
    root->right = std::move(newRoot->left);
    update(*root);
    newRoot->left = std::move(root);
    update(*newRoot);
    return newRoot;
}

std::unique_ptr<AvlNode> insert(std::unique_ptr<AvlNode> root, int key) {
    if (!root) return std::make_unique<AvlNode>(key);
    if (key < root->key) root->left = insert(std::move(root->left), key);
    else if (key > root->key) root->right = insert(std::move(root->right), key);
    else return root; // 本示例忽略重复键
    update(*root);
    const int balance = height(root->left) - height(root->right);
    if (balance > 1) {
        if (key > root->left->key) root->left = rotateLeft(std::move(root->left));
        return rotateRight(std::move(root));
    }
    if (balance < -1) {
        if (key < root->right->key) root->right = rotateRight(std::move(root->right));
        return rotateLeft(std::move(root));
    }
    return root;
}

class ChainedHashSet {
private:
    std::vector<std::vector<int>> buckets_;
    std::size_t index(int key) const { return std::hash<int>{}(key) % buckets_.size(); }
public:
    explicit ChainedHashSet(std::size_t bucketCount) : buckets_(bucketCount) {
        if (bucketCount == 0) throw std::invalid_argument("bucket count must be positive");
    }
    bool contains(int key) const {
        const auto& bucket = buckets_[index(key)];
        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }
    bool insert(int key) {
        auto& bucket = buckets_[index(key)];
        if (std::find(bucket.begin(), bucket.end(), key) != bucket.end()) return false;
        bucket.push_back(key);
        return true;
    }
};

void inorder(const AvlNode* node) {
    if (!node) return;
    inorder(node->left.get());
    std::cout << node->key << ' ';
    inorder(node->right.get());
}

int main() {
    const std::vector<int> values{1, 3, 3, 5, 8};
    std::cout << "第一个 >= 3 的下标: " << lowerBound(values, 3) << '\n';
    std::unique_ptr<AvlNode> root;
    for (int key : {30, 20, 10, 25, 40, 50}) root = insert(std::move(root), key);
    std::cout << "AVL 中序: "; inorder(root.get()); std::cout << '\n';
    ChainedHashSet set(7);
    set.insert(10); set.insert(17);
    std::cout << "包含 17: " << std::boolalpha << set.contains(17) << '\n';
}
