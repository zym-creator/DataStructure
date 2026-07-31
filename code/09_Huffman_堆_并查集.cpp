#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct HuffmanNode {
    int weight;
    char symbol;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
};

using HuffmanPtr = std::shared_ptr<HuffmanNode>;

HuffmanPtr buildHuffman(const std::vector<std::pair<char, int>>& frequencies) {
    auto heavier = [](const HuffmanPtr& a, const HuffmanPtr& b) {
        return a->weight > b->weight;
    };
    std::priority_queue<HuffmanPtr, std::vector<HuffmanPtr>, decltype(heavier)> heap(heavier);
    for (const auto& [symbol, weight] : frequencies) {
        heap.push(std::make_shared<HuffmanNode>(HuffmanNode{weight, symbol, nullptr, nullptr}));
    }
    while (heap.size() > 1) {
        auto left = heap.top(); heap.pop();
        auto right = heap.top(); heap.pop();
        heap.push(std::make_shared<HuffmanNode>(
            HuffmanNode{left->weight + right->weight, '\0', left, right}));
    }
    return heap.empty() ? nullptr : heap.top();
}

void printCodes(const HuffmanPtr& node, const std::string& prefix = "") {
    if (!node) return;
    if (!node->left && !node->right) {
        std::cout << node->symbol << ": " << (prefix.empty() ? "0" : prefix) << '\n';
        return;
    }
    printCodes(node->left, prefix + '0');
    printCodes(node->right, prefix + '1');
}

class DisjointSet {
private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> size_;
public:
    explicit DisjointSet(std::size_t n) : parent_(n), size_(n, 1) {
        for (std::size_t i = 0; i < n; ++i) parent_[i] = i;
    }
    std::size_t find(std::size_t x) {
        if (parent_.at(x) != x) parent_[x] = find(parent_[x]);
        return parent_[x];
    }
    bool unite(std::size_t a, std::size_t b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }
};

int main() {
    printCodes(buildHuffman({{'A', 5}, {'B', 9}, {'C', 12}, {'D', 13}, {'E', 16}, {'F', 45}}));
    DisjointSet sets(5);
    sets.unite(0, 1);
    sets.unite(1, 2);
    std::cout << "0 和 2 连通: " << std::boolalpha << (sets.find(0) == sets.find(2)) << '\n';
}
