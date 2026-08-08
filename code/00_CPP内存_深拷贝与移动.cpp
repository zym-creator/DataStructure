#include <iostream>
using namespace std;

class Buffer {
private:
    int* data;
    int length;

public:
    /* 作用：创建指定长度的动态数组。参数 size 是元素个数。 */
    Buffer(int size = 0) {
        length = size < 0 ? 0 : size;
        data = length == 0 ? NULL : new int[length];
        for (int i = 0; i < length; i++) data[i] = 0;
    }

    /* 作用：深拷贝另一个 Buffer。参数 other 是被复制对象。 */
    Buffer(const Buffer& other) {
        length = other.length;
        data = length == 0 ? NULL : new int[length];
        for (int i = 0; i < length; i++) data[i] = other.data[i];
    }

    /* 作用：深拷贝赋值。返回当前对象，便于连续赋值。 */
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this; // 防止自己赋值给自己
        int* newData = other.length == 0 ? NULL : new int[other.length];
        for (int i = 0; i < other.length; i++) newData[i] = other.data[i];
        delete[] data;
        data = newData;
        length = other.length;
        return *this;
    }

    /* 作用：释放构造函数申请的动态数组。 */
    ~Buffer() {
        delete[] data;
        data = NULL;
    }

    /* 作用：修改指定位置。成功返回 true，越界返回 false。 */
    bool set(int index, int value) {
        if (index < 0 || index >= length) return false;
        data[index] = value;
        return true;
    }

    /* 作用：读取指定位置。参数 ok 用来带回是否成功。 */
    int get(int index, bool& ok) const {
        ok = index >= 0 && index < length;
        return ok ? data[index] : 0;
    }

    /* 作用：返回数组中的元素个数。 */
    int size() const { return length; }
};

int main() {
    Buffer original(3);
    original.set(0, 10);
    Buffer copied = original;
    copied.set(0, 99);
    bool ok = false;
    cout << "原对象: " << original.get(0, ok) << endl;
    cout << "副本: " << copied.get(0, ok) << endl;
    return 0;
}
