#include <limits.h>
#include <vector>
#include <iostream>
#include <queue>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<int> prev_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<int> prev(this->data_.size());
        this->prev_ = prev;
    }

    int size() {
        return this->data_.size();
    }

    int prev(int a) {
        return this->prev_[a];
    }

    std::vector<int> prevVector() {
        return this->prev_;
    }

    int bfs(int source, int target) {
        if (source == target) {
            return 0;
        }
        std::vector<int> dis(this->data_.size(), -1);
        dis[source] = 0;
        std::queue<int> q;
        q.push(source);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            for (auto i = 0; i != this->data_.size(); i++) {
                if (this->data_[curr][i] == 1) {
                    if (dis[i] == -1) {
                        q.push(i);
                        dis[i] = dis[curr] + 1;
                        this->prev_[i] = curr;
                    }
                    if (i == target) {
                        return dis[i];
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
    Graph graph(data);
    src--;
    trg--;

    int pathLength = graph.bfs(src, trg);
    std::cout << pathLength << "\n";

    std::vector<int> reverse;

    /*  for (auto i = 0; i != graph.prevVector().size(); i++) {
            std::cout << graph.prevVector()[i] << " ";
        }
        std::cout << "\n";
    */
    if ((pathLength != -1) && (pathLength != 0)) {
        reverse.push_back(trg);
        while (graph.prev(trg) != src) {
            trg = graph.prev(trg);
            reverse.push_back(trg);
        }
        reverse.push_back(src);
        for (auto i = reverse.size() - 1; i != -1; i--) {
            std::cout << reverse[i] + 1;
            if (i != 0) {
                std::cout << " ";
            } else {
                std::cout << "\n";
            }
        }
    }
}


/*
    std::pair<int, int> superBFS(int a) {
        std::vector<int> dis(this->data_.size(), -1);
        dis[a] = 0;
        std::queue<int> q;
        q.push(a);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            for (auto i : this->data_[curr]) {
                if (dis[i] == -1) {
                    q.push(i);
                    dis[i] = dis[curr] + 1;
                }
            }
        }

        int max = 0;
        int index;

        for (auto i = 0; i != this->data_.size(); i++) {
            if (dis[i] > max) {
                max = dis[i];
                index = i;
            }
        }

        return std::make_pair(index, max);
    }
*/
