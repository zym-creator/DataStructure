#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int currentSize;
    int currentCapacity;

    /* 作用：扩大底层数组。参数 newCapacity 是新容量，无返回值。 */
    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < currentSize; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        currentCapacity = newCapacity;
    }

public:
    /* 作用：创建初始容量为 2 的空顺序表。 */
    DynamicArray() {
        currentSize = 0;
        currentCapacity = 2;
        data = new int[currentCapacity];
    }

    /* 作用：深拷贝另一个动态数组。 */
    DynamicArray(const DynamicArray& other) {
        currentSize = other.currentSize;
        currentCapacity = other.currentCapacity;
        data = new int[currentCapacity];
        for (int i = 0; i < currentSize; i++) data[i] = other.data[i];
    }

    /* 作用：深拷贝赋值，返回当前对象。 */
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        int* newData = new int[other.currentCapacity];
        for (int i = 0; i < other.currentSize; i++) newData[i] = other.data[i];
        delete[] data;
        data = newData;
        currentSize = other.currentSize;
        currentCapacity = other.currentCapacity;
        return *this;
    }

    /* 作用：释放动态数组。 */
    ~DynamicArray() { delete[] data; }

    /* 作用：在末尾加入 value，无返回值。容量不足时扩为两倍。 */
    void pushBack(int value) {
        if (currentSize == currentCapacity) resize(currentCapacity * 2);
        data[currentSize] = value;
        currentSize++;
    }

    /* 作用：在 index 位置插入 value。成功返回 true。 */
    bool insert(int index, int value) {
        if (index < 0 || index > currentSize) return false;
        if (currentSize == currentCapacity) resize(currentCapacity * 2);
        for (int i = currentSize; i > index; i--) data[i] = data[i - 1];
        data[index] = value;
        currentSize++;
        return true;
    }

    /* 作用：删除 index 位置。成功返回 true。 */
    bool removeAt(int index) {
        if (index < 0 || index >= currentSize) return false;
        for (int i = index; i < currentSize - 1; i++) data[i] = data[i + 1];
        currentSize--;
        return true;
    }

    /* 作用：读取 index 位置，ok 表示是否越界。 */
    int get(int index, bool& ok) const {
        ok = index >= 0 && index < currentSize;
        return ok ? data[index] : 0;
    }

    /* 作用：返回元素数量和容量。 */
    int size() const { return currentSize; }
    int capacity() const { return currentCapacity; }
};

int main() {
    DynamicArray array;
    array.pushBack(10); array.pushBack(20); array.pushBack(30);
    array.insert(1, 15); array.removeAt(2);
    bool ok = false;
    for (int i = 0; i < array.size(); i++) cout << array.get(i, ok) << ' ';
    cout << "容量=" << array.capacity() << endl;
    return 0;
}
