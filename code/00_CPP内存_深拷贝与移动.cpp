#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

class Buffer {
private:
    std::size_t size_ = 0;
    int* data_ = nullptr;

public:
    explicit Buffer(std::size_t size = 0)
        : size_(size), data_(size == 0 ? nullptr : new int[size]{}) {}

    ~Buffer() { delete[] data_; }

    // 深拷贝：为新对象创建独立数组。
    Buffer(const Buffer& other)
        : size_(other.size_), data_(size_ == 0 ? nullptr : new int[size_]) {
        if (size_ > 0) std::copy(other.data_, other.data_ + size_, data_);
    }

    // copy-and-swap 同时处理自赋值并提供强异常安全保证。
    Buffer& operator=(const Buffer& other) {
        Buffer copy(other);
        swap(copy);
        return *this;
    }

    // 移动：接管地址，并把源对象置为可安全析构的空状态。
    Buffer(Buffer&& other) noexcept
        : size_(std::exchange(other.size_, 0)),
          data_(std::exchange(other.data_, nullptr)) {}

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = std::exchange(other.size_, 0);
            data_ = std::exchange(other.data_, nullptr);
        }
        return *this;
    }

    void swap(Buffer& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    int& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Buffer index out of range");
        }
        return data_[index];
    }

    const int& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Buffer index out of range");
        }
        return data_[index];
    }

    std::size_t size() const noexcept { return size_; }
};

int main() {
    Buffer original(3);
    original.at(0) = 10;

    Buffer copied = original;
    copied.at(0) = 99;
    std::cout << "深拷贝后互不影响: " << original.at(0) << ' ' << copied.at(0) << '\n';

    Buffer moved = std::move(copied);
    std::cout << "移动后大小: " << copied.size() << " -> " << moved.size() << '\n';
}
