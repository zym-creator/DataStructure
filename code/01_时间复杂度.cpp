#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 示例 1：顺序查找，时间复杂度 O(n)
int linearSearch(const vector<int>& nums, int target) {
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        if (nums[i] == target) {
            return i;
        }
    }
    return -1;
}

// 示例 2：二分查找，时间复杂度 O(log n)，前提是数组有序
int binarySearch(const vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// 方法一：枚举子列头尾，再累加，时间复杂度 O(n^3)
int maxSubseqSum1(const vector<int>& nums) {
    int best = 0;
    int n = static_cast<int>(nums.size());

    for (int left = 0; left < n; left++) {
        for (int right = left; right < n; right++) {
            int current = 0;
            for (int i = left; i <= right; i++) {
                current += nums[i];
            }
            best = max(best, current);
        }
    }

    return best;
}

// 方法二：固定起点，逐个向右累加，时间复杂度 O(n^2)
int maxSubseqSum2(const vector<int>& nums) {
    int best = 0;
    int n = static_cast<int>(nums.size());

    for (int left = 0; left < n; left++) {
        int current = 0;
        for (int right = left; right < n; right++) {
            current += nums[right];
            best = max(best, current);
        }
    }

    return best;
}

// 方法三：前缀和优化区间求和，时间复杂度 O(n^2)
int maxSubseqSum3(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    vector<int> prefix(n + 1, 0);

    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    int best = 0;
    for (int left = 0; left < n; left++) {
        for (int right = left; right < n; right++) {
            int current = prefix[right + 1] - prefix[left];
            best = max(best, current);
        }
    }

    return best;
}

int maxCrossingSum(const vector<int>& nums, int left, int mid, int right) {
    int leftBest = 0;
    int current = 0;
    for (int i = mid; i >= left; i--) {
        current += nums[i];
        leftBest = max(leftBest, current);
    }

    int rightBest = 0;
    current = 0;
    for (int i = mid + 1; i <= right; i++) {
        current += nums[i];
        rightBest = max(rightBest, current);
    }

    return leftBest + rightBest;
}

// 方法四：分治，时间复杂度 O(n log n)
int divideAndConquer(const vector<int>& nums, int left, int right) {
    if (left == right) {
        return max(0, nums[left]);
    }

    int mid = left + (right - left) / 2;
    int leftBest = divideAndConquer(nums, left, mid);
    int rightBest = divideAndConquer(nums, mid + 1, right);
    int crossBest = maxCrossingSum(nums, left, mid, right);

    return max({leftBest, rightBest, crossBest});
}

int maxSubseqSum4(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    return divideAndConquer(nums, 0, static_cast<int>(nums.size()) - 1);
}

// 方法五：在线处理，也叫 Kadane 算法，时间复杂度 O(n)
int maxSubseqSum5(const vector<int>& nums) {
    int best = 0;
    int current = 0;

    for (int value : nums) {
        current += value;
        if (current < 0) {
            current = 0;
        } else {
            best = max(best, current);
        }
    }

    return best;
}

int main() {
    vector<int> nums{4, -3, 5, -2, -1, 2, 6, -2};
    vector<int> sortedNums{1, 3, 5, 7, 9, 11};

    cout << "顺序查找 7 的下标: " << linearSearch(sortedNums, 7) << '\n';
    cout << "二分查找 7 的下标: " << binarySearch(sortedNums, 7) << '\n';

    cout << "最大子列和 O(n^3): " << maxSubseqSum1(nums) << '\n';
    cout << "最大子列和 O(n^2): " << maxSubseqSum2(nums) << '\n';
    cout << "最大子列和 O(n^2) 前缀和: " << maxSubseqSum3(nums) << '\n';
    cout << "最大子列和 O(n log n): " << maxSubseqSum4(nums) << '\n';
    cout << "最大子列和 O(n): " << maxSubseqSum5(nums) << '\n';

    return 0;
}
