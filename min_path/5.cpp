#include <vector>
#include <iostream>
#include <queue>

class Robot {
 public:
    std::vector<std::vector<int>> data;
    explicit Robot(std::vector<std::vector<int>>& data) {
        this->data = data;
    }

    int bfs(int source, int target, bool flag) {
        if (source == target) {
            return 0;
        }
        std::vector<int> disEven(this->data.size(), -1);
        std::vector<int> disOdd(this->data.size(), -1);
        disEven[source] = 0;
        std::queue<int> q;
        q.push(source);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            for (auto i = 0; i != this->data.size(); i++) {
                if (this->data[curr][i] == 1) {
                    if (disEven[i] == -1) {
                        q.push(i);
                        disEven[i] = disOdd[curr] + 2;
                    }

                    if (disOdd[i] == -1) {
                        q.push(i);
                        disOdd[i] = disEven[curr] + 2;
                    }
                    if (i == target) {
                        if (flag) {
                            return disOdd[i];
                        } else {
                            return disEven[i];
                        }
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    int matrixSize;
    std::cin >> matrixSize;
    std::vector<std::vector<int>> data(matrixSize,
        std::vector<int>(matrixSize));
    for (auto i = 0; i != matrixSize; i++) {
        for (auto j = 0; j != matrixSize; j++) {
            std::cin >> data[i][j];
        }
    }
    int src, trg;
    std::cin >> src >> trg;
    Robot graph(data);
    src--;
    trg--;

    int pathLength = graph.bfs(src, trg, false);
    std::cout << pathLength << "\n";
}