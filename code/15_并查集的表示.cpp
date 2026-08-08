#include <iostream>

class DisjointSet {
public:
    using ElementType = int;

    explicit DisjointSet(int elementCount)
        : parents_(elementCount > 0 ? new int[elementCount] : nullptr),
          elementCount_(elementCount > 0 ? elementCount : 0),
          setCount_(elementCount_) {
        for (int i = 0; i < elementCount_; ++i) {
            parents_[i] = -1;
        }
    }

    DisjointSet(const DisjointSet&) = delete;
    DisjointSet& operator=(const DisjointSet&) = delete;

    ~DisjointSet() {
        delete[] parents_;
    }

    ElementType Find(ElementType element) {
        if (!IsValid(element)) {
            return -1;
        }

        const int rootIndex = FindRootIndex(ToIndex(element));
        return ToElement(rootIndex);
    }

    bool Union(ElementType first, ElementType second) {
        if (!IsValid(first) || !IsValid(second)) {
            return false;
        }

        int firstRoot = FindRootIndex(ToIndex(first));
        int secondRoot = FindRootIndex(ToIndex(second));
        if (firstRoot == secondRoot) {
            return false;
        }

        // 根节点保存集合大小的负数，值越小表示集合越大。
        if (parents_[firstRoot] > parents_[secondRoot]) {
            const int temporary = firstRoot;
            firstRoot = secondRoot;
            secondRoot = temporary;
        }

        parents_[firstRoot] += parents_[secondRoot];
        parents_[secondRoot] = firstRoot;
        --setCount_;
        return true;
    }

    bool IsConnected(ElementType first, ElementType second) {
        if (!IsValid(first) || !IsValid(second)) {
            return false;
        }

        return FindRootIndex(ToIndex(first)) == FindRootIndex(ToIndex(second));
    }

    int SetSize(ElementType element) {
        if (!IsValid(element)) {
            return 0;
        }

        const int root = FindRootIndex(ToIndex(element));
        return -parents_[root];
    }

    int SetCount() const {
        return setCount_;
    }

    void PrintRepresentation() const {
        std::cout << "元素：";
        for (int i = 0; i < elementCount_; ++i) {
            std::cout << ToElement(i) << ' ';
        }

        std::cout << "\n下标：";
        for (int i = 0; i < elementCount_; ++i) {
            std::cout << i << ' ';
        }

        std::cout << "\n数组：";
        for (int i = 0; i < elementCount_; ++i) {
            std::cout << parents_[i] << ' ';
        }
        std::cout << '\n';
    }

private:
    bool IsValid(ElementType element) const {
        return element >= 1 && element <= elementCount_;
    }

    static int ToIndex(ElementType element) {
        return element - 1;
    }

    static ElementType ToElement(int index) {
        return index + 1;
    }

    int FindRootIndex(int index) {
        if (parents_[index] < 0) {
            return index;
        }

        parents_[index] = FindRootIndex(parents_[index]);
        return parents_[index];
    }

    int* parents_;
    int elementCount_;
    int setCount_;
};

int main() {
    DisjointSet sets(8);

    sets.Union(3, 5);
    sets.Union(1, 3);
    sets.Union(2, 4);
    sets.Union(8, 6);

    std::cout << "5 所属集合的根：" << sets.Find(5) << '\n';
    std::cout << "1 和 5 是否连通："
              << (sets.IsConnected(1, 5) ? "是" : "否") << '\n';
    std::cout << "1 和 4 是否连通："
              << (sets.IsConnected(1, 4) ? "是" : "否") << '\n';

    sets.Union(4, 5);
    std::cout << "\n合并 4 和 5 后：\n";
    std::cout << "4 所在集合的大小：" << sets.SetSize(4) << '\n';
    std::cout << "当前集合数量：" << sets.SetCount() << '\n';
    sets.PrintRepresentation();
    return 0;
}
