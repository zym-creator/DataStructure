#include <iostream>

class LinkedList {
public:
    using ElementType = int;

    LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList() {
        Clear();
    }

    int Find(ElementType value) const {
        const Node* current = head_;
        int index = 0;

        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1;
    }

    bool Insert(ElementType value, int index) {
        if (index < 0 || index > length_) {
            std::cout << "插入位置不合法\n";
            return false;
        }

        if (index == 0) {
            head_ = new Node{value, head_};
        } else {
            Node* previous = GetNode(index - 1);
            previous->next = new Node{value, previous->next};
        }
        ++length_;
        return true;
    }

    bool Delete(int index) {
        if (index < 0 || index >= length_) {
            std::cout << "删除位置不合法\n";
            return false;
        }

        Node* nodeToDelete = nullptr;
        if (index == 0) {
            nodeToDelete = head_;
            head_ = head_->next;
        } else {
            Node* previous = GetNode(index - 1);
            nodeToDelete = previous->next;
            previous->next = nodeToDelete->next;
        }

        delete nodeToDelete;
        --length_;
        return true;
    }

    bool FindKth(int index, ElementType& value) const {
        if (index < 0 || index >= length_) {
            std::cout << "查找位置不合法\n";
            return false;
        }
        value = GetNode(index)->data;
        return true;
    }

    int Length() const {
        return length_;
    }

    void Print() const {
        const Node* current = head_;
        while (current != nullptr) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

private:
    struct Node {
        ElementType data;
        Node* next;
    };

    Node* GetNode(int index) {
        Node* current = head_;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    const Node* GetNode(int index) const {
        const Node* current = head_;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    void Clear() {
        while (head_ != nullptr) {
            Node* nodeToDelete = head_;
            head_ = head_->next;
            delete nodeToDelete;
        }
        length_ = 0;
    }

    Node* head_ = nullptr;
    int length_ = 0;
};

int main() {
    LinkedList list;

    list.Insert(11, 0);
    list.Insert(25, 1);
    list.Insert(33, 2);
    list.Insert(77, 1);

    std::cout << "插入后的链表线性表：";
    list.Print();

    std::cout << "值 33 的下标：" << list.Find(33) << '\n';

    int value = 0;
    if (list.FindKth(2, value)) {
        std::cout << "下标 2 的元素：" << value << '\n';
    }

    list.Delete(1);
    std::cout << "删除下标 1 后：";
    list.Print();

    return 0;
}
