#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const int current = values[i];
        std::size_t j = i;
        while (j > 0 && current < values[j - 1]) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = current;
    }
}

void quickSort(std::vector<int>& values, std::size_t first, std::size_t last) {
    if (last - first <= 1) return;
    const int pivot = values[first + (last - first) / 2];
    std::size_t less = first;
    std::size_t scan = first;
    std::size_t greater = last;
    while (scan < greater) {
        if (values[scan] < pivot) std::swap(values[less++], values[scan++]);
        else if (values[scan] > pivot) std::swap(values[scan], values[--greater]);
        else ++scan;
    }
    quickSort(values, first, less);
    quickSort(values, greater, last);
}

void mergeSortImpl(std::vector<int>& values, std::vector<int>& buffer,
                   std::size_t first, std::size_t last) {
    if (last - first <= 1) return;
    const auto mid = first + (last - first) / 2;
    mergeSortImpl(values, buffer, first, mid);
    mergeSortImpl(values, buffer, mid, last);
    std::size_t left = first, right = mid, out = first;
    while (left < mid && right < last)
        buffer[out++] = values[left] <= values[right] ? values[left++] : values[right++];
    while (left < mid) buffer[out++] = values[left++];
    while (right < last) buffer[out++] = values[right++];
    std::copy(buffer.begin() + static_cast<std::ptrdiff_t>(first),
              buffer.begin() + static_cast<std::ptrdiff_t>(last),
              values.begin() + static_cast<std::ptrdiff_t>(first));
}

void mergeSort(std::vector<int>& values) {
    std::vector<int> buffer(values.size());
    mergeSortImpl(values, buffer, 0, values.size());
}

void print(const std::vector<int>& values) {
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    const std::vector<int> input{5, 1, 4, 2, 8, 2, -1};
    auto a = input, b = input, c = input;
    insertionSort(a);
    quickSort(b, 0, b.size());
    mergeSort(c);
    std::cout << "插入: "; print(a);
    std::cout << "快排: "; print(b);
    std::cout << "归并: "; print(c);
}
