#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/* 作用：在有序数组中找第一个大于等于 target 的下标。 */
int lowerBound(const vector<int>& values, int target) {
    int left = 0, right = (int)values.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (values[mid] < target) left = mid + 1; else right = mid;
    }
    return left;
}

struct AvlNode {
    int key, height;
    AvlNode* left;
    AvlNode* right;
    AvlNode(int value) : key(value), height(1), left(NULL), right(NULL) {}
};

/* 作用：返回节点高度，空节点高度为 0。 */
int nodeHeight(AvlNode* node) { return node == NULL ? 0 : node->height; }
/* 作用：根据左右子树重新计算 node 的高度。 */
void updateHeight(AvlNode* node) { node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right)); }

/* 作用：对 root 进行右旋，返回旋转后的新根。 */
AvlNode* rotateRight(AvlNode* root) {
    AvlNode* newRoot = root->left;
    AvlNode* middle = newRoot->right;
    newRoot->right = root; root->left = middle;
    updateHeight(root); updateHeight(newRoot); return newRoot;
}

/* 作用：对 root 进行左旋，返回旋转后的新根。 */
AvlNode* rotateLeft(AvlNode* root) {
    AvlNode* newRoot = root->right;
    AvlNode* middle = newRoot->left;
    newRoot->left = root; root->right = middle;
    updateHeight(root); updateHeight(newRoot); return newRoot;
}

/* 作用：把 key 插入 AVL 树，返回调整后的根。重复键不插入。 */
AvlNode* insertAvl(AvlNode* root, int key) {
    if (root == NULL) return new AvlNode(key);
    if (key < root->key) root->left = insertAvl(root->left, key);
    else if (key > root->key) root->right = insertAvl(root->right, key);
    else return root;
    updateHeight(root);
    int balance = nodeHeight(root->left) - nodeHeight(root->right);
    if (balance > 1 && key < root->left->key) return rotateRight(root); // LL
    if (balance < -1 && key > root->right->key) return rotateLeft(root); // RR
    if (balance > 1 && key > root->left->key) { root->left = rotateLeft(root->left); return rotateRight(root); }
    if (balance < -1 && key < root->right->key) { root->right = rotateRight(root->right); return rotateLeft(root); }
    return root;
}

/* 作用：中序输出 AVL 树，结果应递增。 */
void inorder(AvlNode* node) { if (node != NULL) { inorder(node->left); cout << node->key << ' '; inorder(node->right); } }
/* 作用：后序释放 AVL 树。 */
void destroyAvl(AvlNode* node) { if (node != NULL) { destroyAvl(node->left); destroyAvl(node->right); delete node; } }

class HashSet {
private:
    vector<vector<int> > buckets;
    /* 作用：把 key 转为合法桶下标，也能处理负数。 */
    int hashIndex(int key) const { int index = key % (int)buckets.size(); return index < 0 ? index + buckets.size() : index; }
public:
    HashSet(int bucketCount) : buckets(bucketCount > 0 ? bucketCount : 1) {}
    /* 作用：判断 key 是否存在。 */
    bool contains(int key) const {
        const vector<int>& bucket = buckets[hashIndex(key)];
        for (int i = 0; i < (int)bucket.size(); i++) if (bucket[i] == key) return true;
        return false;
    }
    /* 作用：插入 key。原来不存在返回 true。 */
    bool insert(int key) { if (contains(key)) return false; buckets[hashIndex(key)].push_back(key); return true; }
};

int main() {
    vector<int> values; values.push_back(1); values.push_back(3); values.push_back(3); values.push_back(5);
    cout << "第一个 >= 3 的下标: " << lowerBound(values, 3) << endl;
    AvlNode* root = NULL; int keys[] = {30, 20, 10, 25, 40, 50};
    for (int i = 0; i < 6; i++) root = insertAvl(root, keys[i]);
    cout << "AVL 中序: "; inorder(root); cout << endl;
    HashSet set(7); set.insert(10); set.insert(17);
    cout << "包含 17: " << boolalpha << set.contains(17) << endl;
    destroyAvl(root); return 0;
}
