#include <iostream>
#include <vector>

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
    std::vector<TreeNode*> generateTrees(int n) {
        if(!n) {
            return {nullptr};
        }
        std::vector<TreeNode*> trees = Generate(1, n);
        return trees;
    }
private:
    std::vector<TreeNode*> Generate(int start, int end) {
        if(start > end) {
            return {nullptr};
        }

        std::vector<TreeNode*> trees;
        for(int root = start; root <= end; ++root) {
            std::vector<TreeNode*> leftTree = Generate(start, root - 1);
            std::vector<TreeNode*> rightTree = Generate(root + 1, end);

            for(auto& left : leftTree) {
                for(auto& right :rightTree) {
                    TreeNode* root_ = new TreeNode(root);
                    root_ -> left = left;
                    root_ -> right = right;
                    trees.emplace_back(root_);
                }
            }
        }

        return trees;
    }
};

