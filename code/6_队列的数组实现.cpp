#include <iostream>

class ArrayQueue {
public:
    using ElementType = int;
    static constexpr int MaxSize = 100;

    bool IsEmpty() const {
        return size_ == 0;
    }

    bool IsFull() const {
        return size_ == MaxSize;
    }

    bool Enqueue(ElementType value) {
        if (IsFull()) {
            std::cout << "队列已满\n";
            return false;
        }

        data_[rear_] = value;
        rear_ = (rear_ + 1) % MaxSize;
        ++size_;
        return true;
    }

    bool Dequeue(ElementType& value) {
        if (IsEmpty()) {
            std::cout << "队列为空\n";
            return false;
        }

        value = data_[front_];
        front_ = (front_ + 1) % MaxSize;
        --size_;
        return true;
    }

    int Size() const {
        return size_;
    }

private:
    ElementType data_[MaxSize]{};
    int front_ = 0; // 队头元素的下标
    int rear_ = 0;  // 下一个可插入位置
    int size_ = 0;
};

int main() {
    ArrayQueue queue;

    std::cout << "3 入队\n";
    queue.Enqueue(3);
    std::cout << "5 入队\n";
    queue.Enqueue(5);
    std::cout << "11 入队\n";
    queue.Enqueue(11);

    int value = 0;
    if (queue.Dequeue(value)) {
        std::cout << value << " 出队\n";
    }
    if (queue.Dequeue(value)) {
        std::cout << value << " 出队\n";
    }

    std::cout << "当前队列中有 " << queue.Size() << " 个元素\n";
    return 0;
}
