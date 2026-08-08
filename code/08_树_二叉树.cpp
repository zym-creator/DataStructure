#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : value(value), left(NULL), right(NULL) {}
};

/*
 * 函数作用：递归完成二叉树的先序遍历，顺序是“根、左、右”。
 * 参数 node：当前正在访问的节点；为 NULL 时表示走到了空子树。
 * 参数 output：引用参数，用来依次保存访问到的节点值。
 * 返回值：无。
 * 执行过程：先记录当前节点，再递归遍历左子树，最后遍历右子树。
 */
void preorder(TreeNode* node, vector<int>& output) {
    if (node == NULL) return;
    output.push_back(node->value);
    preorder(node->left, output);
    preorder(node->right, output);
}

/*
 * 函数作用：使用栈完成非递归中序遍历，顺序是“左、根、右”。
 * 参数 root：二叉树根节点。
 * 参数 output：引用参数，保存遍历结果。
 * 返回值：无。
 * 关键变量 current：当前准备处理的节点。
 * 关键变量 pending：保存已经经过、但还没有访问的节点。
 * 执行过程：先不断向左并压栈；走到空节点后弹出栈顶访问，再转向右子树。
 */
void inorderIterative(TreeNode* root, vector<int>& output) {
    stack<TreeNode*> pending;
    TreeNode* current = root;

    while (current != NULL || !pending.empty()) {
        while (current != NULL) {
            pending.push(current);
            current = current->left;
        }

        current = pending.top();
        pending.pop();
        output.push_back(current->value);
        current = current->right;
    }
}

/*
 * 函数作用：从上到下、从左到右进行层序遍历。
 * 参数 root：整棵二叉树的根节点。
 * 返回值：按层序保存的节点值；空树返回空 vector。
 * 关键变量 nodes：队列，保存已经发现但还没有访问的节点。
 * 执行过程：根入队；反复取队头，并把它的左右孩子依次入队。
 */
vector<int> levelOrder(TreeNode* root) {
    vector<int> output;
    if (root == NULL) return output;
    queue<TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        TreeNode* current = nodes.front();
        nodes.pop();
        output.push_back(current->value);
        if (current->left != NULL) nodes.push(current->left);
        if (current->right != NULL) nodes.push(current->right);
    }
    return output;
}

/*
 * 函数作用：计算以 node 为根的二叉树高度。
 * 参数 node：当前子树的根。
 * 返回值：空树为 0，非空树为左右子树最大高度加 1。
 * 执行过程：递归计算左右高度，取较大值，再加上当前这一层。
 */
int height(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + max(height(node->left), height(node->right));
}

/*
 * 函数作用：统计以 node 为根的树中有多少个叶子节点。
 * 参数 node：当前子树的根。
 * 返回值：叶子节点总数。
 * 执行过程：空树返回 0；当前节点没有孩子返回 1；否则累加左右子树。
 */
int countLeaves(TreeNode* node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

/*
 * 函数作用：释放整棵二叉树，避免 new 出来的节点发生内存泄漏。
 * 参数 node：当前准备释放的子树根节点。
 * 返回值：无。
 * 执行过程：先释放左子树，再释放右子树，最后 delete 当前节点。
 * 注意：不能先删除当前节点，否则将无法通过它找到左右孩子。
 */
void destroyTree(TreeNode* node) {
    if (node == NULL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

/*
 * 函数作用：按保存顺序输出 vector 中的全部整数。
 * 参数 values：需要输出的数组，使用常量引用避免复制和误修改。
 * 返回值：无。
 * 关键变量 i：当前输出元素的下标。
 */
void printVector(const vector<int>& values) {
    for (int i = 0; i < (int)values.size(); i++) cout << values[i] << ' ';
    cout << endl;
}

int main() {
    // 使用普通指针建立下面的二叉树：
    //         1
    //       /   \
    //      2     3
    //     / \
    //    4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> values;

    preorder(root, values);
    cout << "先序: ";
    printVector(values);

    values.clear();
    inorderIterative(root, values);
    cout << "中序（非递归）: ";
    printVector(values);

    cout << "层序: ";
    printVector(levelOrder(root));
    cout << "高度: " << height(root) << " 叶子数: " << countLeaves(root) << endl;

    // 所有节点都是 new 创建的，程序结束前必须逐个 delete。
    destroyTree(root);
    root = NULL;
    return 0;
}
