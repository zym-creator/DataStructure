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

// 计算用空格分隔的后缀表达式，例如 "2 3 + 4 *"。
bool EvaluatePostfix(const char* expression, int& result) {
    ArrayStack values;
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == ' ') {
            ++i;
            continue;
        }

        // 读取整数，支持多位数和负数。
        bool negative = false;
        if (expression[i] == '-' && expression[i + 1] >= '0' && expression[i + 1] <= '9') {
            negative = true;
            ++i;
        }

        if (expression[i] >= '0' && expression[i] <= '9') {
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                ++i;
            }

            if (negative) {
                number = -number;
            }
            if (!values.Push(number)) {
                return false;
            }
            continue;
        }

        // 遇到运算符时，先取出右操作数，再取出左操作数。
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

        int value = 0;
        if (operation == '+') {
            value = left + right;
        } else if (operation == '-') {
            value = left - right;
        } else if (operation == '*') {
            value = left * right;
        } else {
            if (right == 0) {
                std::cout << "不能除以零\n";
                return false;
            }
            value = left / right;
        }

        if (!values.Push(value)) {
            return false;
        }
        ++i;
    }

    if (!values.Pop(result) || !values.IsEmpty()) {
        std::cout << "后缀表达式格式不正确\n";
        return false;
    }
    return true;
}

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

    const char* expression = "2 3 + 4 * 5 -";
    int answer = 0;
    if (EvaluatePostfix(expression, answer)) {
        std::cout << "后缀表达式 " << expression << " = " << answer << '\n';
    }

    return 0;
}
