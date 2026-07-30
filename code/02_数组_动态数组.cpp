#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicArray {
private:
    int* data;
    int length;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        int* newData = new int[newCapacity];

        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(new int[2]), length(0), capacity(2) {}

    ~DynamicArray() {
        delete[] data;
    }

    void pushBack(int value) {
        if (length == capacity) {
            resize();
        }
        data[length++] = value;
    }

    void insert(int index, int value) {
        if (index < 0 || index > length) {
            throw out_of_range("index out of range");
        }
        if (length == capacity) {
            resize();
        }
        for (int i = length; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        length++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("index out of range");
        }
        for (int i = index; i < length - 1; i++) {
            data[i] = data[i + 1];
        }
        length--;
    }

    int get(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("index out of range");
        }
        return data[index];
    }

    int size() const {
        return length;
    }
};

int main() {
    DynamicArray arr;
    arr.pushBack(10);
    arr.pushBack(20);
    arr.pushBack(30);
    arr.insert(1, 15);
    arr.removeAt(2);

    for (int i = 0; i < arr.size(); i++) {
        cout << arr.get(i) << ' ';
    }
    cout << '\n';

    return 0;
}
