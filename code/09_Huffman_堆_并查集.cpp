#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct HuffmanNode {
    int weight;
    char symbol;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(int w, char ch) : weight(w), symbol(ch), left(NULL), right(NULL) {}
};

struct CompareNode {
    /* 作用：让 priority_queue 变成最小堆，权值小的节点先出队。 */
    bool operator()(HuffmanNode* a, HuffmanNode* b) { return a->weight > b->weight; }
};

/* 作用：根据字符和频率建立 Huffman 树。返回根指针。 */
HuffmanNode* buildHuffman(const vector<char>& symbols, const vector<int>& weights) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> heap;
    for (int i = 0; i < (int)symbols.size(); i++) heap.push(new HuffmanNode(weights[i], symbols[i]));
    while (heap.size() > 1) {
        HuffmanNode* left = heap.top(); heap.pop();
        HuffmanNode* right = heap.top(); heap.pop();
        HuffmanNode* parent = new HuffmanNode(left->weight + right->weight, '\0');
        parent->left = left; parent->right = right;
        heap.push(parent);
    }
    return heap.empty() ? NULL : heap.top();
}

/* 作用：递归输出叶子字符的 Huffman 编码。code 是当前路径。 */
void printCodes(HuffmanNode* node, string code) {
    if (node == NULL) return;
    if (node->left == NULL && node->right == NULL) {
        cout << node->symbol << ": " << (code.empty() ? "0" : code) << endl;
        return;
    }
    printCodes(node->left, code + "0");
    printCodes(node->right, code + "1");
}

/* 作用：后序释放 Huffman 树的所有节点。 */
void destroyHuffman(HuffmanNode* node) {
    if (node == NULL) return;
    destroyHuffman(node->left); destroyHuffman(node->right); delete node;
}

class DisjointSet {
private:
    vector<int> parent;
    vector<int> setSize;
public:
    /* 作用：建立 n 个互不相交的集合。 */
    DisjointSet(int n) : parent(n), setSize(n, 1) { for (int i = 0; i < n; i++) parent[i] = i; }
    /* 作用：查找 x 所在集合的根，并进行路径压缩。 */
    int find(int x) { if (parent[x] != x) parent[x] = find(parent[x]); return parent[x]; }
    /* 作用：合并 a、b 所在集合。原本已连通返回 false。 */
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (setSize[a] < setSize[b]) { int temp = a; a = b; b = temp; }
        parent[b] = a; setSize[a] += setSize[b]; return true;
    }
};

int main() {
    vector<char> symbols; symbols.push_back('A'); symbols.push_back('B'); symbols.push_back('C'); symbols.push_back('D');
    vector<int> weights; weights.push_back(5); weights.push_back(9); weights.push_back(12); weights.push_back(13);
    HuffmanNode* root = buildHuffman(symbols, weights);
    printCodes(root, "");
    DisjointSet sets(5); sets.unite(0, 1); sets.unite(1, 2);
    cout << "0 和 2 连通: " << boolalpha << (sets.find(0) == sets.find(2)) << endl;
    destroyHuffman(root);
    return 0;
}
