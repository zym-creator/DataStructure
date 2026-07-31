#include <iostream>

class MaxHeap {
public:
    using ElementType = int;

    explicit MaxHeap(int capacity)
        : elements_(capacity > 0 ? new ElementType[capacity] : nullptr),
          size_(0),
          capacity_(capacity > 0 ? capacity : 0) {}

    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    ~MaxHeap() {
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

    bool DeleteMax(ElementType& maximum) {
        if (IsEmpty()) {
            return false;
        }

        maximum = elements_[0];
        --size_;
        elements_[0] = elements_[size_];

        if (!IsEmpty()) {
            SiftDown(0);
        }
        return true;
    }

    bool GetMax(ElementType& maximum) const {
        if (IsEmpty()) {
            return false;
        }
        maximum = elements_[0];
        return true;
    }

    bool IsFull() const {
        return size_ == capacity_;
    }

    bool IsEmpty() const {
        return size_ == 0;
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
            if (elements_[parent] >= elements_[index]) {
                break;
            }
            const ElementType temporary = elements_[parent];
            elements_[parent] = elements_[index];
            elements_[index] = temporary;
            index = parent;
        }
    }

    void SiftDown(int index) {
        while (LeftChild(index) < size_) {
            int largerChild = LeftChild(index);
            const int rightChild = largerChild + 1;

            if (rightChild < size_ &&
                elements_[rightChild] > elements_[largerChild]) {
                largerChild = rightChild;
            }

            if (elements_[index] >= elements_[largerChild]) {
                break;
            }

            const ElementType temporary = elements_[index];
            elements_[index] = elements_[largerChild];
            elements_[largerChild] = temporary;
            index = largerChild;
        }
    }

    ElementType* elements_;
    int size_;
    int capacity_;
};

int main() {
    MaxHeap heap(8);
    const int values[] = {55, 66, 44, 33, 11, 22, 88, 99};

    for (int value : values) {
        if (!heap.Insert(value)) {
            std::cout << "堆已满，无法插入 " << value << '\n';
        }
    }

    std::cout << "层序遍历：";
    heap.PrintLevelOrder();

    int maximum;
    while (heap.DeleteMax(maximum)) {
        std::cout << "删除最大值 " << maximum << " 后：";
        heap.PrintLevelOrder();
    }

    if (!heap.DeleteMax(maximum)) {
        std::cout << "堆为空，无法继续删除\n";
    }
    return 0;
}
