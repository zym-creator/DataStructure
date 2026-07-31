#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) newData[i] = std::move_if_noexcept(data_[i]);
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    DynamicArray() : data_(new T[2]), size_(0), capacity_(2) {}
    ~DynamicArray() { delete[] data_; }

    DynamicArray(const DynamicArray& other)
        : data_(other.capacity_ == 0 ? nullptr : new T[other.capacity_]),
          size_(other.size_), capacity_(other.capacity_) {
        if (size_ > 0) std::copy(other.data_, other.data_ + size_, data_);
    }

    DynamicArray& operator=(DynamicArray other) {
        swap(other);
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    void swap(DynamicArray& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void pushBack(const T& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 2 : capacity_ * 2);
        data_[size_++] = value;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) throw std::out_of_range("index out of range");
        if (size_ == capacity_) reserve(capacity_ == 0 ? 2 : capacity_ * 2);
        for (std::size_t i = size_; i > index; --i) data_[i] = std::move(data_[i - 1]);
        data_[index] = value;
        ++size_;
    }

    void removeAt(std::size_t index) {
        if (index >= size_) throw std::out_of_range("index out of range");
        for (std::size_t i = index; i + 1 < size_; ++i) data_[i] = std::move(data_[i + 1]);
        --size_;
    }

    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("index out of range");
        return data_[index];
    }
    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("index out of range");
        return data_[index];
    }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
};

int main() {
    DynamicArray<int> array;
    array.pushBack(10); array.pushBack(20); array.pushBack(30);
    array.insert(1, 15);
    array.removeAt(2);
    DynamicArray<int> copy = array; // 深拷贝
    copy.at(0) = 99;
    std::cout << "原数组/副本首元素: " << array.at(0) << ' ' << copy.at(0) << '\n';
    for (std::size_t i = 0; i < array.size(); ++i) std::cout << array.at(i) << ' ';
    std::cout << "(容量 " << array.capacity() << ")\n";
}
