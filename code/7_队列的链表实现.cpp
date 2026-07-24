#include <iostream>

class LinkedQueue {
public:
    using ElementType = int;

    LinkedQueue() = default;
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    ~LinkedQueue() {
        Clear();
    }

    bool IsEmpty() const {
        return front_ == nullptr;
    }

    bool Enqueue(ElementType value) {
        Node* newNode = new Node{value, nullptr};

        if (rear_ == nullptr) {
            front_ = newNode;
            rear_ = newNode;
        } else {
            rear_->next = newNode;
            rear_ = newNode;
        }
        ++size_;
        return true;
    }

    bool Dequeue(ElementType& value) {
        if (IsEmpty()) {
            std::cout << "队列为空\n";
            return false;
        }

        Node* nodeToDelete = front_;
        value = nodeToDelete->data;
        front_ = front_->next;

        if (front_ == nullptr) {
            rear_ = nullptr;
        }

        delete nodeToDelete;
        --size_;
        return true;
    }

    int Size() const {
        return size_;
    }

private:
    struct Node {
        ElementType data;
        Node* next;
    };

    void Clear() {
        while (front_ != nullptr) {
            Node* nodeToDelete = front_;
            front_ = front_->next;
            delete nodeToDelete;
        }
        rear_ = nullptr;
        size_ = 0;
    }

    Node* front_ = nullptr;
    Node* rear_ = nullptr;
    int size_ = 0;
};

int main() {
    LinkedQueue queue;

    std::cout << "5 入队\n";
    queue.Enqueue(5);
    std::cout << "4 入队\n";
    queue.Enqueue(4);
    std::cout << "3 入队\n";
    queue.Enqueue(3);

    int value = 0;
    while (queue.Dequeue(value)) {
        std::cout << value << " 出队\n";
    }
    return 0;
}
