#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        return Invert(root);
    }

private:
    TreeNode* Invert(TreeNode* node) {
        if(node == nullptr) {
            return node;
        }

        Invert(node -> left);
        Invert(node -> right);

        TreeNode* tmp = node -> left;
        node -> left = node -> right;
        node -> right = tmp;

        return node;
    }
};