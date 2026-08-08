#include <iostream>
#include <vector>
using namespace std;

struct Triple {
    int row;
    int col;
    int value;
};

class SparseMatrix {
private:
    int rows;
    int cols;
    vector<Triple> terms;

public:
    /* 作用：建立 rows 行、cols 列的空稀疏矩阵。 */
    SparseMatrix(int rowCount, int colCount) {
        rows = rowCount;
        cols = colCount;
    }

    /* 作用：加入一个非零元素。下标合法返回 true。 */
    bool add(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) return false;
        if (value != 0) {
            Triple item = {row, col, value};
            terms.push_back(item);
        }
        return true;
    }

    /* 作用：按三元组逐项转置。返回新的转置矩阵。 */
    SparseMatrix transpose() const {
        SparseMatrix result(cols, rows);
        // 为了让结果按行排列，先按原矩阵的列号扫描。
        for (int col = 0; col < cols; col++) {
            for (int i = 0; i < (int)terms.size(); i++) {
                if (terms[i].col == col) {
                    result.add(terms[i].col, terms[i].row, terms[i].value);
                }
            }
        }
        return result;
    }

    /* 作用：输出全部非零元素的行、列和值。 */
    void printTriples() const {
        for (int i = 0; i < (int)terms.size(); i++) {
            cout << '(' << terms[i].row << ", " << terms[i].col
                 << ", " << terms[i].value << ")" << endl;
        }
    }
};

int main() {
    SparseMatrix matrix(3, 4);
    matrix.add(0, 1, 5); matrix.add(1, 3, 8); matrix.add(2, 0, -2);
    SparseMatrix result = matrix.transpose();
    cout << "转置后的三元组:" << endl;
    result.printTriples();
    return 0;
}
