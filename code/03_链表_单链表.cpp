#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int value) : value(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* dummyHead;

public:
    LinkedList() : dummyHead(new Node(0)) {}

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList() {
        Node* cur = dummyHead;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = dummyHead->next;
        dummyHead->next = node;
    }

    void pushBack(int value) {
        Node* cur = dummyHead;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = new Node(value);
    }

    bool remove(int value) {
        Node* prev = dummyHead;
        while (prev->next != nullptr && prev->next->value != value) {
            prev = prev->next;
        }
        if (prev->next == nullptr) {
            return false;
        }

        Node* target = prev->next;
        prev->next = target->next;
        delete target;
        return true;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* cur = dummyHead->next;

        while (cur != nullptr) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        dummyHead->next = prev;
    }

    void print() const {
        Node* cur = dummyHead->next;
        while (cur != nullptr) {
            cout << cur->value << ' ';
            cur = cur->next;
        }
        cout << '\n';
    }
};

int main() {
    LinkedList list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(0);
    list.remove(2);
    list.print();

    list.reverse();
    list.print();

    return 0;
}
