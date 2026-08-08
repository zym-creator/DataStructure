#include <iostream>
#include <stdexcept>
using namespace std;

class ArrayStack {
private:
    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int topIndex;

public:
    ArrayStack() : topIndex(-1) {}

    /* 作用：判断栈是否为空。空栈返回 true。 */
    bool empty() const {
        return topIndex == -1;
    }

    /* 作用：把 value 压入栈顶。栈满时给出错误。 */
    void push(int value) {
        if (topIndex + 1 == MAX_SIZE) {
            throw overflow_error("stack is full");
        }
        data[++topIndex] = value;
    }

    /* 作用：删除栈顶元素，无返回值。空栈时给出错误。 */
    void pop() {
        if (empty()) {
            throw underflow_error("stack is empty");
        }
        topIndex--;
    }

    /* 作用：返回栈顶元素，但不删除它。 */
    int top() const {
        if (empty()) {
            throw underflow_error("stack is empty");
        }
        return data[topIndex];
    }
};

/* 作用：判断字符串 s 中的圆括号是否匹配。匹配返回 true。 */
bool isValidParentheses(const string& s) {
    ArrayStack st;

    for (char ch : s) {
        if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            if (st.empty()) {
                return false;
            }
            st.pop();
        }
    }

    return st.empty();
}

int main() {
    cout << boolalpha;
    cout << isValidParentheses("(())") << '\n';
    cout << isValidParentheses("(()") << '\n';

    return 0;
}
