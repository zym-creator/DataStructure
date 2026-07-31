#include <iostream>

class MinHeap {
public:
    using ElementType = int;

    explicit MinHeap(int capacity)
        : elements_(capacity > 0 ? new ElementType[capacity] : nullptr),
          size_(0),
          capacity_(capacity > 0 ? capacity : 0) {}

    MinHeap(const MinHeap&) = delete;
    MinHeap& operator=(const MinHeap&) = delete;

    ~MinHeap() {
        delete[] elements_;
    }

    bool Insert(ElementType value) {
        if (IsFull()) {
            return false;
        }

        elements_[size_] = value;
        SiftUp(size_);
        ++size_;
        return true;
    }

    bool BuildByInsertion(const ElementType values[], int count) {
        if (count < 0 || count > capacity_) {
            return false;
        }

        size_ = 0;
        for (int i = 0; i < count; ++i) {
            Insert(values[i]);
        }
        return true;
    }

    bool BuildBottomUp(const ElementType values[], int count) {
        if (count < 0 || count > capacity_) {
            return false;
        }

        for (int i = 0; i < count; ++i) {
            elements_[i] = values[i];
        }
        size_ = count;

        // 叶子本身已是堆，从最后一个非叶节点开始下滤。
        for (int i = size_ / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
        return true;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    bool IsFull() const {
        return size_ == capacity_;
    }

    int Size() const {
        return size_;
    }

    void PrintLevelOrder() const {
        for (int i = 0; i < size_; ++i) {
            std::cout << elements_[i] << ' ';
        }
        std::cout << '\n';
    }

private:
    static int Parent(int index) {
        return (index - 1) / 2;
    }

    static int LeftChild(int index) {
        return index * 2 + 1;
    }

    void SiftUp(int index) {
        while (index > 0) {
            const int parent = Parent(index);
            if (elements_[parent] <= elements_[index]) {
                break;
            }

            Swap(elements_[parent], elements_[index]);
            index = parent;
        }
    }

    void SiftDown(int index) {
        while (LeftChild(index) < size_) {
            int smallerChild = LeftChild(index);
            const int rightChild = smallerChild + 1;

            if (rightChild < size_ &&
                elements_[rightChild] < elements_[smallerChild]) {
                smallerChild = rightChild;
            }

            if (elements_[index] <= elements_[smallerChild]) {
                break;
            }

            Swap(elements_[index], elements_[smallerChild]);
            index = smallerChild;
        }
    }

    static void Swap(ElementType& first, ElementType& second) {
        const ElementType temporary = first;
        first = second;
        second = temporary;
    }

    ElementType* elements_;
    int size_;
    int capacity_;
};

int main() {
    int count;
    std::cout << "请输入元素个数：";
    std::cin >> count;

    if (!std::cin || count < 0) {
        std::cout << "元素个数必须是非负整数\n";
        return 1;
    }

    int* values = count > 0 ? new int[count] : nullptr;
    std::cout << "请输入 " << count << " 个整数：";
    for (int i = 0; i < count; ++i) {
        if (!(std::cin >> values[i])) {
            std::cout << "输入的元素无效\n";
            delete[] values;
            return 1;
        }
    }

    MinHeap insertionHeap(count);
    insertionHeap.BuildByInsertion(values, count);
    std::cout << "逐个插入建堆：";
    insertionHeap.PrintLevelOrder();

    MinHeap bottomUpHeap(count);
    bottomUpHeap.BuildBottomUp(values, count);
    std::cout << "自底向上建堆：";
    bottomUpHeap.PrintLevelOrder();

    delete[] values;
    return 0;
}
