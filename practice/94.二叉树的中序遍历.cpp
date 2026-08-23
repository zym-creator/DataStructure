#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value)
        : val(value), left(nullptr), right(nullptr) {
    }
};

class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        InOrder(root, result);
        return result;
    }

private:
    void InOrder(const TreeNode* node, std::vector<int>& result) {
        if (node == nullptr) {
            return;
        }

        InOrder(node->left, result);
        result.push_back(node->val);
        InOrder(node->right, result);
    }
};
