#include <iostream>
#include <stdexcept>
using namespace std;

class CircularQueue {
private:
    int* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    CircularQueue(int capacity)
        : data(new int[capacity]), capacity(capacity), frontIndex(0), rearIndex(0), count(0) {}

    ~CircularQueue() {
        delete[] data;
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == capacity;
    }

    void push(int value) {
        if (full()) {
            throw overflow_error("queue is full");
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    void pop() {
        if (empty()) {
            throw underflow_error("queue is empty");
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    int front() const {
        if (empty()) {
            throw underflow_error("queue is empty");
        }
        return data[frontIndex];
    }
};

int main() {
    CircularQueue q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    q.pop();
    q.push(40);

    while (!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << '\n';

    return 0;
}
