#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<int> colors_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<int> colors(data.size(), -1);
        this->colors_ = colors;
    }

    bool isBipartile(int a) {
        std::queue<int> q;
        q.push(a);
        this->colors_[a] = 1;
        while (!q.empty()) {
            int a = q.front();
            q.pop();
            for (auto i : this->data_[a]) {
                if (this->colors_[i] == -1) {
                    this->colors_[i] = 1 - this->colors_[a];
                    q.push(i);
                } else if (this->colors_[a] == this->colors_[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartileStrong() {
        for (int i = 0; i != this->data_.size(); i++) {
            if (this->colors_[i] == -1) {
                if (!(this->isBipartile(i))) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    int numOfVerts, numOfEdges;

    std::cin >> numOfVerts >> numOfEdges;

    std::vector<std::vector<int>> data(numOfVerts);

    for (auto i = 0; i != numOfEdges; i++) {
        int a, b;
        std::cin >> a >> b;
        data[a - 1].push_back(b - 1);
        data[b - 1].push_back(a - 1);
    }

    Graph graph(data);
    if (graph.isBipartileStrong()) {
        std::cout << "YES" << "\n";
    } else {
        std::cout << "NO" << "\n";
    }
}
