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
    int numTrees(int n) {
        if(!n) {
            return 0;
        }

        int num = generate(1, n);
        return num;
    }

    int generate(int start, int end) {
        if(start >= end) {
            return 1;
        }
        
        int num = 0;
        for(int i = start; i <= end; ++i) {
            int left = generate(start, i - 1);
            int right = generate(i + 1, end);
            num += left * right;
        }
        return num;
    }
};

int main() {
    int n = 0;
    std::cin >> n;
    Solution s;
    int num = s.numTrees(n);
    std::cout << num << std::endl;
    return 0;
}