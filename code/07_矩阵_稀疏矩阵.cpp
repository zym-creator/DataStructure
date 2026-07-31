#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

struct Triple {
    std::size_t row;
    std::size_t col;
    int value;
};

class SparseMatrix {
private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<Triple> terms_;

public:
    SparseMatrix(std::size_t rows, std::size_t cols)
        : rows_(rows), cols_(cols) {}

    void add(std::size_t row, std::size_t col, int value) {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("matrix index out of range");
        }
        if (value != 0) {
            terms_.push_back({row, col, value});
        }
    }

    SparseMatrix fastTranspose() const {
        SparseMatrix result(cols_, rows_);
        result.terms_.resize(terms_.size());
        std::vector<std::size_t> counts(cols_, 0);
        for (const auto& term : terms_) {
            ++counts[term.col];
        }

        std::vector<std::size_t> starts(cols_, 0);
        for (std::size_t col = 1; col < cols_; ++col) {
            starts[col] = starts[col - 1] + counts[col - 1];
        }
        for (const auto& term : terms_) {
            const auto position = starts[term.col]++;
            result.terms_[position] = {term.col, term.row, term.value};
        }
        return result;
    }

    void printTriples() const {
        for (const auto& term : terms_) {
            std::cout << '(' << term.row << ", " << term.col << ", " << term.value << ")\n";
        }
    }
};

int main() {
    SparseMatrix matrix(3, 4);
    matrix.add(0, 1, 5);
    matrix.add(1, 3, 8);
    matrix.add(2, 0, -2);
    std::cout << "转置后的三元组:\n";
    matrix.fastTranspose().printTriples();
}
