#include <iostream>
#include <queue>
#include <string>
#include <vector>

class Maze {
public:
    struct Point {
        int row;
        int column;
    };

    explicit Maze(const std::vector<std::string>& layout)
        : grid_(layout),
          distance_(layout.size(),
                   std::vector<int>(layout.empty() ? 0 : layout[0].size(), -1)) {}

    bool BFS(Point start) {
        if (!IsOpen(start)) {
            return false;
        }

        for (std::vector<int>& row : distance_) {
            for (int& value : row) {
                value = -1;
            }
        }

        std::queue<Point> pending;
        distance_[start.row][start.column] = 0;
        pending.push(start);

        // 八个方向：左上、上、右上、右、右下、下、左下、左。
        const int rowOffset[] = {-1, -1, -1, 0, 1, 1, 1, 0};
        const int columnOffset[] = {-1, 0, 1, 1, 1, 0, -1, -1};

        while (!pending.empty()) {
            const Point current = pending.front();
            pending.pop();

            for (int direction = 0; direction < 8; ++direction) {
                const Point next{
                    current.row + rowOffset[direction],
                    current.column + columnOffset[direction]
                };

                if (IsOpen(next) &&
                    distance_[next.row][next.column] == -1) {
                    distance_[next.row][next.column] =
                        distance_[current.row][current.column] + 1;
                    pending.push(next);
                }
            }
        }

        return true;
    }

    int DistanceTo(Point point) const {
        if (!IsInside(point)) {
            return -1;
        }
        return distance_[point.row][point.column];
    }

    void PrintDistances() const {
        for (int row = 0; row < static_cast<int>(distance_.size()); ++row) {
            for (int column = 0;
                 column < static_cast<int>(distance_[row].size());
                 ++column) {
                const int distance = distance_[row][column];
                if (distance == -1) {
                    std::cout << "  -";
                } else if (distance < 10) {
                    std::cout << "  " << distance;
                } else {
                    std::cout << ' ' << distance;
                }
            }
            std::cout << '\n';
        }
    }

private:
    bool IsInside(Point point) const {
        return point.row >= 0 &&
               point.row < static_cast<int>(grid_.size()) &&
               point.column >= 0 &&
               !grid_.empty() &&
               point.column < static_cast<int>(grid_[point.row].size());
    }

    bool IsOpen(Point point) const {
        return IsInside(point) && grid_[point.row][point.column] == '1';
    }

    std::vector<std::string> grid_;
    std::vector<std::vector<int>> distance_;
};

int main() {
    const std::vector<std::string> layout = {
        "111011101110",
        "101100101000",
        "100010001011",
        "101111111001",
        "001001011110",
        "111011000111",
        "110111100100",
        "000100101011",
        "011011101010",
        "000001101011"
    };

    Maze maze(layout);
    const Maze::Point start{0, 0};

    if (!maze.BFS(start)) {
        std::cout << "起点不可达，无法遍历迷宫\n";
        return 1;
    }

    std::cout << "从 (" << start.row << ", " << start.column
              << ") 出发的最少步数（- 表示不可达）：\n";
    maze.PrintDistances();
    return 0;
}
