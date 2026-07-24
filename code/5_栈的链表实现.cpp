#include <iostream>

class LinkedStack {
public:
    using ElementType = int;

    LinkedStack() = default;
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    ~LinkedStack() {
        Clear();
    }

    bool IsEmpty() const {
        return top_ == nullptr;
    }

    bool Push(ElementType value) {
        Node* newNode = new Node{value, top_};
        top_ = newNode;
        ++size_;
        return true;
    }

    bool Pop(ElementType& value) {
        if (IsEmpty()) {
            std::cout << "栈为空\n";
            return false;
        }

        Node* nodeToDelete = top_;
        value = nodeToDelete->data;
        top_ = nodeToDelete->next;
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
        while (top_ != nullptr) {
            Node* nodeToDelete = top_;
            top_ = top_->next;
            delete nodeToDelete;
        }
        size_ = 0;
    }

    Node* top_ = nullptr;
    int size_ = 0;
};

bool EvaluatePostfix(const char* expression, int& result) {
    LinkedStack values;
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == ' ') {
            ++i;
            continue;
        }

        bool negative = false;
        if (expression[i] == '-' && expression[i + 1] >= '0' && expression[i + 1] <= '9') {
            negative = true;
            ++i;
        }

        if (expression[i] >= '0' && expression[i] <= '9') {
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + expression[i] - '0';
                ++i;
            }
            if (negative) {
                number = -number;
            }
            values.Push(number);
            continue;
        }

        char operation = expression[i];
        if (operation != '+' && operation != '-' && operation != '*' && operation != '/') {
            std::cout << "表达式中存在无效字符\n";
            return false;
        }

        int right = 0;
        int left = 0;
        if (!values.Pop(right) || !values.Pop(left)) {
            std::cout << "运算符缺少操作数\n";
            return false;
        }

        if (operation == '/' && right == 0) {
            std::cout << "不能除以零\n";
            return false;
        }

        int value = 0;
        if (operation == '+') {
            value = left + right;
        } else if (operation == '-') {
            value = left - right;
        } else if (operation == '*') {
            value = left * right;
        } else {
            value = left / right;
        }
        values.Push(value);
        ++i;
    }

    if (!values.Pop(result) || !values.IsEmpty()) {
        std::cout << "后缀表达式格式不正确\n";
        return false;
    }
    return true;
}

int main() {
    LinkedStack stack;

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

    const char* expression = "2 3 + 4 * 5 -";
    int answer = 0;
    if (EvaluatePostfix(expression, answer)) {
        std::cout << "后缀表达式 " << expression << " = " << answer << '\n';
    }
    return 0;
}
