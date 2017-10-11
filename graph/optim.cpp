#include <iostream>  //  std::cout, std::cin
#include <algorithm>  //  std::max
#include <utility>  //  std::pair, std::make_pair
#include <vector>  //  std::vector
#include <queue>  //  std::queue

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<bool> isDiscovered_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<bool> defaultBool(data.size(), false);
        this->isDiscovered_ = defaultBool;
    }

    int size() const {
        return this->data_.size();
    }

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

    int longestPath() {
        std::pair<int, int> pair1, pair2;
        pair1 = this->superBFS(0);
        pair2 = this->superBFS(pair1.first);
        return pair2.second;
    }
};


int main() {
    int numOfVerts;

    std::cin >> numOfVerts;

    std::vector<std::vector<int>> data(numOfVerts);

    for (auto i = 0; i != numOfVerts - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        data[a - 1].push_back(b - 1);
        data[b - 1].push_back(a - 1);
    }

    Graph graph(data);
    std::cout << graph.longestPath() << "\n";
}
