#include <iostream>
#include <vector>

#define hashnum 769

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int value) : val(value), next(nullptr) {}
};

class MyHashSet {
public:
    MyHashSet() {
        for(int i = 0; i < hashnum; i++) {
            hash[i] = nullptr;
        }
    }
    
    void add(int key) {
        int i = key % hashnum;

        if(hash[i] == nullptr) {
            hash[i] = new Node(key);
        }

        Node* cur = hash[i];
        Node* nex = nullptr;

        while(cur != nullptr) {
            if(cur -> val == key) {
                return;
            }

            nex = cur;
            cur = cur -> next;
        }
        nex -> next = new Node(key);
    }
    
    void remove(int key) {
        int i = key % hashnum;

        Node* cur = hash[i];
        Node* nex = nullptr;

        while(cur != nullptr) {
            if (cur->val == key) {
                if (nex == nullptr) {
                    hash[i] = cur->next;
                } else {
                    nex->next = cur->next;
                }
                delete cur;
                return;
            }
            nex = cur;
            cur = cur -> next;
        }
    }
    
    bool contains(int key) {
        int i = key % hashnum;

        if(hash[i] == nullptr) {
            return false;
        }

        Node* cur = hash[i];

        while(cur != nullptr) {
            if(cur -> val == key) {
                return true;
            }

            cur = cur -> next;
        }
        return false;
    }

private:
    Node* hash[hashnum];
};
