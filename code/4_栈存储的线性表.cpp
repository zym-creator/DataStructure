#include <iostream>

class ArrayStack {
public:
    using ElementType = int;
    static constexpr int MaxSize = 100;

    bool IsFull() const {
        return top_ == MaxSize - 1;
    }

    bool IsEmpty() const {
        return top_ == -1;
    }

    bool Push(ElementType value) {
        if (IsFull()) {
            std::cout << "栈已满\n";
            return false;
        }

        ++top_;
        data_[top_] = value;
        return true;
    }

    bool Pop(ElementType& value) {
        if (IsEmpty()) {
            std::cout << "栈为空\n";
            return false;
        }

        value = data_[top_];
        --top_;
        return true;
    }

    int Size() const {
        return top_ + 1;
    }

private:
    ElementType data_[MaxSize]{};
    int top_ = -1;
};

int main() {
    ArrayStack stack;

    std::cout << "5 入栈\n";
    stack.Push(5);
    std::cout << "7 入栈\n";
    stack.Push(7);
    std::cout << "66 入栈\n";
    stack.Push(66);

    int value = 0;
    if (stack.Pop(value)) {
        std::cout << value << " 出栈\n";
    }
    if (stack.Pop(value)) {
        std::cout << value << " 出栈\n";
    }

    std::cout << "当前栈中有 " << stack.Size() << " 个元素\n";
    return 0;
}
