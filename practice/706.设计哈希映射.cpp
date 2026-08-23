#include <iostream>
#include <vector>

#define hashnum 769

using namespace std;

struct Node {
    int key;
    int val;
    Node* next;
    Node(int key, int value) : key(key), val(value), next(nullptr) {}
};

class MyHashMap {
public:
    MyHashMap() {
        for(int i = 0; i < hashnum; i++) {
            hash[i] = nullptr;
        }
    }
    
    void put(int key, int value) {
        int i = key % hashnum;

        if(hash[i] == nullptr) {
            hash[i] = new Node(key, value);
        }

        Node* cur = hash[i];
        Node* nex = nullptr;

        while(cur != nullptr) {
            if(cur -> key == key) {
                cur -> val = value;
                return;
            }

            nex = cur;
            cur = cur -> next;
        }
        nex -> next = new Node(key, value);
    }
    
    void remove(int key) {
        int i = key % hashnum;

        Node* cur = hash[i];
        Node* nex = nullptr;

        while(cur != nullptr) {
            if (cur->key == key) {
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
    
    int get(int key) {
        int i = key % hashnum;

        if(hash[i] == nullptr) {
            return -1;
        }

        Node* cur = hash[i];

        while(cur != nullptr) {
            if(cur -> key == key) {
                return cur -> val;
            }

            cur = cur -> next;
        }
        return -1;
    }

private:
    Node* hash[hashnum];
};
