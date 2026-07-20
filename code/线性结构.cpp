#include <array>
#include <iostream>

class LinearList {
public:
    using ElementType = int;
    static constexpr std::size_t MaxSize = 100;

    int Find(ElementType value) const {
        for (int i = 0; i < last_; ++i) {
            if (data_[i] == value) {
                return i;
            }
        }
        return -1;
    }

    bool Insert(ElementType value, int index) {
        if (last_ == static_cast<int>(MaxSize)) {
            std::cout << "表满\n";
            return false;
        }
        if (index < 0 || index > last_) {
            std::cout << "位置不合法\n";
            return false;
        }

        for (int i = last_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++last_;
        return true;
    }

    bool Delete(int index) {
        if (index < 0 || index >= last_) {
            std::cout << "L->Data[" << index << "]不存在元素\n";
            return false;
        }

        for (int i = index; i + 1 < last_; ++i) {
            data_[i] = data_[i + 1];
        }
        --last_;
        return true;
    }

    bool FindKth(int index, ElementType& value) const {
        if (index < 0 || index >= last_) {
            std::cout << "L->Data[" << index << "]不存在元素\n";
            return false;
        }
        value = data_[index];
        return true;
    }

    int Length() const {
        return last_;
    }

    ElementType operator[](int index) const {
        return data_[index];
    }

private:
    std::array<ElementType, MaxSize> data_{};
    int last_ = 0;
};

int main() {
    LinearList list;
    list.Insert(11, 0);
    std::cout << "在线性表L-Data[0]插入11\n";
    list.Insert(25, 0);
    std::cout << "在线性表L-Data[0]插入25\n";
    list.Insert(33, 0);
    std::cout << "在线性表L-Data[0]插入33\n";
    list.Insert(77, 0);
    std::cout << "在线性表L-Data[0]插入77\n";

    std::cout << "此时的线性表为：";
    for (int i = 0; i < list.Length(); ++i) {
        std::cout << list[i] << ' ';
    }
    std::cout << '\n';

    std::cout << "查找值为12的下标是：" << list.Find(12) << '\n';

    int value = 0;
    if (list.FindKth(3, value)) {
        std::cout << "下标为3的线性表的值是：" << value << '\n';
    }

    list.Delete(2);
    std::cout << "删除线性表中下标为2的元素\n";
    list.Delete(2);
    std::cout << "删除线性表中下标为2的元素\n";

    std::cout << "此时的线性表为：";
    for (int i = 0; i < list.Length(); ++i) {
        std::cout << list[i] << ' ';
    }
    std::cout << '\n';
}
