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

    bool empty() const {
        return topIndex == -1;
    }

    void push(int value) {
        if (topIndex + 1 == MAX_SIZE) {
            throw overflow_error("stack is full");
        }
        data[++topIndex] = value;
    }

    void pop() {
        if (empty()) {
            throw underflow_error("stack is empty");
        }
        topIndex--;
    }

    int top() const {
        if (empty()) {
            throw underflow_error("stack is empty");
        }
        return data[topIndex];
    }
};

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
