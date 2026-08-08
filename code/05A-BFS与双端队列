#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/*
    求每个滑动窗口中的最大值。

    例如：

    values = {1, 3, -1, -3, 5, 3, 6, 7}
    windowSize = 3

    窗口变化：

    {1, 3, -1} -> 3
    {3, -1, -3} -> 3
    {-1, -3, 5} -> 5
    {-3, 5, 3} -> 5
    {5, 3, 6} -> 6
    {3, 6, 7} -> 7

    结果：

    {3, 3, 5, 5, 6, 7}
*/
vector<int> slidingWindowMaximum(
    const vector<int>& values,
    size_t windowSize) {

    // 窗口大小不能为 0，
    // 也不能大于数组长度。
    if (windowSize == 0 || windowSize > values.size()) {
        throw invalid_argument("invalid window size");
    }

    /*
        candidates 保存的是“可能成为最大值”的元素下标。

        例如：

        candidates = {4, 5, 6}

        表示当前窗口中，下标 4、5、6 的元素仍然有可能成为最大值。

        注意：队列中存储的是下标，不是元素值。
        因为我们需要通过下标判断元素是否已经离开窗口。
    */
    deque<size_t> candidates;

    /*
        一共有：

        values.size() - windowSize + 1

        个窗口，因此提前分配这部分空间，
        可以减少 vector 扩容次数。
    */
    vector<int> answer;
    answer.reserve(values.size() - windowSize + 1);

    /*
        i 表示当前正在加入窗口的元素下标。

        当 i = 0、1、2 时，第一个窗口形成；
        当 i = 3 时，窗口向右移动一步；
        依此类推。
    */
    for (size_t i = 0; i < values.size(); ++i) {

        /*
            第一步：移除已经离开窗口的下标。

            当前窗口的左边界是：

                i - windowSize + 1

            如果某个下标 index 满足：

                index < i - windowSize + 1

            它就已经不在窗口中。

            原代码使用：

                candidates.front() + windowSize <= i

            两种写法含义相同，并且可以避免 i - windowSize + 1
            在无符号数下发生下溢。
        */
        while (!candidates.empty()
               && candidates.front() + windowSize <= i) {
            candidates.pop_front();
        }

        /*
            第二步：维护队列的单调递减性。

            如果队尾元素小于或等于当前元素，
            那么队尾元素以后不可能成为最大值。

            原因是：

            1. 当前元素比它大或一样大；
            2. 当前元素比它更晚离开窗口；
            3. 因此当前元素更有优势。

            所以可以把队尾元素删除。
        */
        while (!candidates.empty()
               && values[candidates.back()] <= values[i]) {
            candidates.pop_back();
        }

        /*
            第三步：把当前下标加入队尾。

            经过前面的删除后，队列中的值保持从大到小排列。
        */
        candidates.push_back(i);

        /*
            当 i + 1 >= windowSize 时，
            说明至少已经形成了一个完整窗口。

            单调队列的队头始终保存当前窗口最大值的下标，
            因此直接取它对应的值即可。
        */
        if (i + 1 >= windowSize) {
            answer.push_back(values[candidates.front()]);
        }
    }

    return answer;
}

int main() {
    const vector<int> values{1, 3, -1, -3, 5, 3, 6, 7};
    const size_t windowSize = 3;

    try {
        const vector<int> result =
            slidingWindowMaximum(values, windowSize);

        for (int maximum : result) {
            cout << maximum << ' ';
        }

        cout << '\n';
    } catch (const invalid_argument& error) {
        cerr << "输入错误: " << error.what() << '\n';
    }

    return 0;
}
