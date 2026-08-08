#include <iostream>
#include <vector>
using namespace std;

/* 作用：直接插入排序。values 是待排序数组，排序后递增。 */
void insertionSort(vector<int>& values) {
    for (int i = 1; i < (int)values.size(); i++) {
        int current = values[i]; // 暂存准备插入的元素
        int j = i - 1;
        while (j >= 0 && values[j] > current) { values[j + 1] = values[j]; j--; }
        values[j + 1] = current;
    }
}

/* 作用：快速排序。left、right 是当前处理的闭区间下标。 */
void quickSort(vector<int>& values, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int pivot = values[(left + right) / 2];
    while (i <= j) {
        while (values[i] < pivot) i++;
        while (values[j] > pivot) j--;
        if (i <= j) { int temp = values[i]; values[i] = values[j]; values[j] = temp; i++; j--; }
    }
    quickSort(values, left, j); quickSort(values, i, right);
}

/* 作用：合并两个相邻有序区间 [left,mid] 和 [mid+1,right]。 */
void merge(vector<int>& values, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (values[i] <= values[j]) temp[k++] = values[i++]; else temp[k++] = values[j++];
    }
    while (i <= mid) temp[k++] = values[i++];
    while (j <= right) temp[k++] = values[j++];
    for (int p = left; p <= right; p++) values[p] = temp[p];
}

/* 作用：递归归并排序当前闭区间。 */
void mergeSortPart(vector<int>& values, vector<int>& temp, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSortPart(values, temp, left, mid); mergeSortPart(values, temp, mid + 1, right);
    merge(values, temp, left, mid, right);
}

/* 作用：归并排序整个数组。 */
void mergeSort(vector<int>& values) { if (!values.empty()) { vector<int> temp(values.size()); mergeSortPart(values, temp, 0, values.size() - 1); } }
/* 作用：输出数组。 */
void printVector(const vector<int>& values) { for (int i = 0; i < (int)values.size(); i++) cout << values[i] << ' '; cout << endl; }

int main() {
    int raw[] = {5, 1, 4, 2, 8, 2, -1}; vector<int> input(raw, raw + 7);
    vector<int> a = input, b = input, c = input;
    insertionSort(a); quickSort(b, 0, b.size() - 1); mergeSort(c);
    cout << "插入: "; printVector(a); cout << "快排: "; printVector(b); cout << "归并: "; printVector(c);
    return 0;
}
