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

    /* 作用：逐个释放头节点和所有数据节点，防止内存泄漏。 */
    ~LinkedList() {
        Node* cur = dummyHead;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    /* 作用：把 value 插到表头。参数 value 是新数据，无返回值。 */
    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = dummyHead->next;
        dummyHead->next = node;
    }

    /* 作用：把 value 插到表尾。cur 用来寻找最后一个节点。 */
    void pushBack(int value) {
        Node* cur = dummyHead;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = new Node(value);
    }

    /* 作用：删除第一个等于 value 的节点。删除成功返回 true。 */
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

    /* 作用：原地反转链表。prev、cur、next 分别指向前驱、当前和后继。 */
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

    /* 作用：从头到尾输出链表，无参数、无返回值。 */
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
