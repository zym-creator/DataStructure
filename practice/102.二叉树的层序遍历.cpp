#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) {
            return tree;
        }
        queue.push(root);
        while(!queue.empty()) {
            int num = queue.size();
            vector<int> lev;
            for(int i = 0; i < num; ++i) {
                TreeNode* current = queue.front();
                queue.pop();
                lev.push_back(current -> val);
                if(current -> left)
                    queue.push(current -> left);
                if(current -> right)
                    queue.push(current -> right);
            }

            tree.push_back(lev);
        }

        return tree;
    }

private:
    vector<vector<int>> tree;
    queue<TreeNode*> queue;
};