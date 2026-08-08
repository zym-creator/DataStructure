#include <iostream>

struct TreeNode;

struct Edge {
    TreeNode* child;
    int cost;
};

struct TreeNode {
    static constexpr int MaxChildren = 2;

    char name;
    int heuristic;
    Edge children[MaxChildren];
    int childCount;

    TreeNode(char nodeName, int heuristicValue)
        : name(nodeName), heuristic(heuristicValue), childCount(0) {}

    bool AddChild(TreeNode* child, int cost) {
        if (child == nullptr || cost < 0 || childCount == MaxChildren) {
            return false;
        }

        children[childCount] = Edge{child, cost};
        ++childCount;
        return true;
    }
};

struct SearchRecord {
    TreeNode* node;
    int g;
    int f;
    SearchRecord* parent;
};

class RecordMinHeap {
public:
    explicit RecordMinHeap(int capacity)
        : elements_(capacity > 0 ? new SearchRecord*[capacity] : nullptr),
          size_(0),
          capacity_(capacity > 0 ? capacity : 0) {}

    RecordMinHeap(const RecordMinHeap&) = delete;
    RecordMinHeap& operator=(const RecordMinHeap&) = delete;

    ~RecordMinHeap() {
        delete[] elements_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    bool Insert(SearchRecord* record) {
        if (record == nullptr || size_ == capacity_) {
            return false;
        }

        elements_[size_] = record;
        SiftUp(size_);
        ++size_;
        return true;
    }

    bool DeleteMin(SearchRecord*& record) {
        if (IsEmpty()) {
            return false;
        }

        record = elements_[0];
        --size_;

        if (!IsEmpty()) {
            elements_[0] = elements_[size_];
            SiftDown(0);
        }
        return true;
    }

private:
    static bool HasHigherPriority(const SearchRecord* first,
                                  const SearchRecord* second) {
        if (first->f != second->f) {
            return first->f < second->f;
        }

        // f 相同时优先选择更接近目标的节点。
        return first->node->heuristic < second->node->heuristic;
    }

    static int Parent(int index) {
        return (index - 1) / 2;
    }

    static int LeftChild(int index) {
        return index * 2 + 1;
    }

    static void Swap(SearchRecord*& first, SearchRecord*& second) {
        SearchRecord* temporary = first;
        first = second;
        second = temporary;
    }

    void SiftUp(int index) {
        while (index > 0) {
            const int parent = Parent(index);
            if (HasHigherPriority(elements_[parent], elements_[index])) {
                break;
            }

            Swap(elements_[parent], elements_[index]);
            index = parent;
        }
    }

    void SiftDown(int index) {
        while (LeftChild(index) < size_) {
            int smallerChild = LeftChild(index);
            const int rightChild = smallerChild + 1;

            if (rightChild < size_ &&
                HasHigherPriority(elements_[rightChild], elements_[smallerChild])) {
                smallerChild = rightChild;
            }

            if (HasHigherPriority(elements_[index], elements_[smallerChild])) {
                break;
            }

            Swap(elements_[index], elements_[smallerChild]);
            index = smallerChild;
        }
    }

    SearchRecord** elements_;
    int size_;
    int capacity_;
};

class AStarTreeSearch {
public:
    explicit AStarTreeSearch(int maximumRecords)
        : open_(maximumRecords),
          records_(maximumRecords > 0 ? new SearchRecord*[maximumRecords] : nullptr),
          recordCount_(0),
          recordCapacity_(maximumRecords > 0 ? maximumRecords : 0) {}

    AStarTreeSearch(const AStarTreeSearch&) = delete;
    AStarTreeSearch& operator=(const AStarTreeSearch&) = delete;

    ~AStarTreeSearch() {
        for (int i = 0; i < recordCount_; ++i) {
            delete records_[i];
        }
        delete[] records_;
    }

    SearchRecord* Find(TreeNode* start, TreeNode* goal) {
        if (start == nullptr || goal == nullptr) {
            return nullptr;
        }

        SearchRecord* startRecord = CreateRecord(
            start, 0, start->heuristic, nullptr);
        if (startRecord == nullptr || !open_.Insert(startRecord)) {
            return nullptr;
        }

        while (!open_.IsEmpty()) {
            SearchRecord* current = nullptr;
            open_.DeleteMin(current);

            std::cout << "展开 " << current->node->name
                      << "：g=" << current->g
                      << ", h=" << current->node->heuristic
                      << ", f=" << current->f << '\n';

            if (current->node == goal) {
                return current;
            }

            for (int i = 0; i < current->node->childCount; ++i) {
                const Edge& edge = current->node->children[i];
                const int childG = current->g + edge.cost;
                SearchRecord* childRecord = CreateRecord(
                    edge.child,
                    childG,
                    childG + edge.child->heuristic,
                    current);

                if (childRecord == nullptr || !open_.Insert(childRecord)) {
                    return nullptr;
                }
            }
        }

        return nullptr;
    }

    static void PrintPath(const SearchRecord* goalRecord) {
        if (goalRecord == nullptr) {
            return;
        }

        PrintPath(goalRecord->parent);
        if (goalRecord->parent != nullptr) {
            std::cout << " -> ";
        }
        std::cout << goalRecord->node->name;
    }

private:
    SearchRecord* CreateRecord(TreeNode* node, int g, int f,
                               SearchRecord* parent) {
        if (recordCount_ == recordCapacity_) {
            return nullptr;
        }

        SearchRecord* record = new SearchRecord{node, g, f, parent};
        records_[recordCount_] = record;
        ++recordCount_;
        return record;
    }

    RecordMinHeap open_;
    SearchRecord** records_;
    int recordCount_;
    int recordCapacity_;
};

int main() {
    TreeNode s('S', 7);
    TreeNode a('A', 6);
    TreeNode b('B', 8);
    TreeNode c('C', 7);
    TreeNode d('D', 2);
    TreeNode e('E', 9);
    TreeNode f('F', 10);
    TreeNode g('G', 0);
    TreeNode h('H', 12);

    s.AddChild(&a, 2);
    s.AddChild(&b, 4);
    a.AddChild(&c, 2);
    a.AddChild(&d, 5);
    b.AddChild(&e, 1);
    c.AddChild(&f, 3);
    d.AddChild(&g, 2);
    e.AddChild(&h, 2);

    AStarTreeSearch search(9);
    SearchRecord* result = search.Find(&s, &g);

    if (result == nullptr) {
        std::cout << "未找到目标节点\n";
        return 0;
    }

    std::cout << "路径：";
    AStarTreeSearch::PrintPath(result);
    std::cout << "\n总代价：" << result->g << '\n';
    return 0;
}
