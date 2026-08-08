#include <iostream>
#include <vector>
using namespace std;

/* 作用：把多个已有序的小数组合并成一个有序数组。runs 是归并段集合。 */
vector<int> kWayMerge(const vector<vector<int> >& runs) {
    vector<int> position(runs.size(), 0); // position[i] 是第 i 段下一个未取元素的位置
    vector<int> result;
    while (true) {
        int chosenRun = -1; // 当前最小元素来自哪一段
        for (int i = 0; i < (int)runs.size(); i++) {
            if (position[i] < (int)runs[i].size()) {
                if (chosenRun == -1 || runs[i][position[i]] < runs[chosenRun][position[chosenRun]]) chosenRun = i;
            }
        }
        if (chosenRun == -1) break; // 所有归并段都已经取完
        result.push_back(runs[chosenRun][position[chosenRun]]);
        position[chosenRun]++;
    }
    return result;
}

int main() {
    vector<vector<int> > runs(3);
    int a[] = {1, 7, 12}, b[] = {2, 5, 9}, c[] = {0, 6, 10};
    runs[0] = vector<int>(a, a + 3); runs[1] = vector<int>(b, b + 3); runs[2] = vector<int>(c, c + 3);
    vector<int> result = kWayMerge(runs);
    for (int i = 0; i < (int)result.size(); i++) cout << result[i] << ' ';
    cout << endl; return 0;
}
