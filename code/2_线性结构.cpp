#include <iostream>

class ArrayList {
public:
    using ElementType = int;
    static constexpr int MaxSize = 100;

    int Find(ElementType value) const {
        for (int i = 0; i < length_; ++i) {
            if (data_[i] == value) {
                return i;
            }
        }
        return -1;
    }

    bool Insert(ElementType value, int index) {
        if (length_ == MaxSize) {
            std::cout << "线性表已满\n";
            return false;
        }
        if (index < 0 || index > length_) {
            std::cout << "插入位置不合法\n";
            return false;
        }

        // 从后向前移动，为新元素留出位置。
        for (int i = length_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++length_;
        return true;
    }

    bool Delete(int index) {
        if (index < 0 || index >= length_) {
            std::cout << "删除位置不合法\n";
            return false;
        }

        // 将后面的元素依次向前移动。
        for (int i = index; i < length_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --length_;
        return true;
    }

    bool FindKth(int index, ElementType& value) const {
        if (index < 0 || index >= length_) {
            std::cout << "查找位置不合法\n";
            return false;
        }
        value = data_[index];
        return true;
    }

    int Length() const {
        return length_;
    }

    void Print() const {
        for (int i = 0; i < length_; ++i) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }

private:
    ElementType data_[MaxSize]{};
    int length_ = 0;
};

int main() {
    ArrayList list;

    list.Insert(11, 0);
    list.Insert(25, 1);
    list.Insert(33, 2);
    list.Insert(77, 1);

    std::cout << "插入后的数组线性表：";
    list.Print();

    std::cout << "值 33 的下标：" << list.Find(33) << '\n';

    int value = 0;
    if (list.FindKth(2, value)) {
        std::cout << "下标 2 的元素：" << value << '\n';
    }

    list.Delete(1);
    std::cout << "删除下标 1 后：";
    list.Print();

    return 0;
}
