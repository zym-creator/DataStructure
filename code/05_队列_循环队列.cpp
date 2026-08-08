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
    explicit CircularQueue(int capacity)
        : data(nullptr), capacity(capacity), frontIndex(0), rearIndex(0), count(0) {
        if (capacity <= 0) {
            throw invalid_argument("capacity must be positive");
        }
        data = new int[static_cast<size_t>(capacity)];
    }

    /* 作用：释放循环队列使用的动态数组。 */
    ~CircularQueue() {
        delete[] data;
    }

    /* 作用：判断队列是否为空。 */
    bool empty() const {
        return count == 0;
    }

    /* 作用：判断队列是否已满。 */
    bool full() const {
        return count == capacity;
    }

    /* 作用：把 value 放入队尾。rearIndex 是下一次写入位置。 */
    void push(int value) {
        if (full()) {
            throw overflow_error("queue is full");
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    /* 作用：删除队头元素。frontIndex 循环向后移动。 */
    void pop() {
        if (empty()) {
            throw underflow_error("queue is empty");
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    /* 作用：读取队头元素但不删除。 */
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
