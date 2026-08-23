#include <unordered_map>
#include <stack>
#include <vector>

struct Node {
    int val;
    std::vector<Node*> neighbors;

    Node() : val(0) {}
    explicit Node(int value) : val(value) {}
    Node(int value, std::vector<Node*> adjacent)
        : val(value), neighbors(std::move(adjacent)) {}
};

class Solution {
public:
    std::unordered_map<Node*, Node*> visited;
    Node* cloneGraph(Node* node) {
        if(node == nullptr) {
            return node;
        }
        
        if(visited.find(node) != visited.end()) {
            return visited[node];
        }
        
        Node* cloneNode = new Node(node->val);
        visited[node] = cloneNode;

        for(auto& neighbor: node->neighbors) {
            cloneNode -> neighbors.emplace_back(cloneGraph(neighbor));
        }

        return cloneNode;
    }

private:

};
