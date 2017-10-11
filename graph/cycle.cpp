#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<int> colors_;
    std::vector<int> parent_;
    std::vector<int> cycle_;
    // int cycleVert_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<int> colors(data.size(), -1);
        this->colors_ = colors;
        std::vector<int> parent(data.size(), -1);
        this->parent_ = parent;
    }

    int getParent(int i) {
        return this->parent_[i];
    }

    std::vector<int> cycle() {
        return this->cycle_;
    }

    bool isCycle(int a) {
        std::vector<int> parent(this->data_.size(), -1);
        this->parent_ = parent;
        std::stack<int> s;
        s.push(a);
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (this->colors_[v] == -1) {
                this->colors_[v] = 1;
                for (auto i = 0; i != this->data_.size(); i++) {
                    if ((this->data_[v][i] == 1) &&
                        (i != this->parent_[v])) {
                        if (this->colors_[i] == 1) {
                            for (auto j = v; j != i ; j = this->parent_[j]) {
                                this->cycle_.push_back(j);
                            }
                            /* for (auto j = 0; j != this->parent_.size(); j++) {
                                std::cout << this->parent_[j] << " ";
                            }*/
                            this->cycle_.push_back(i);
                            return true;
                        }
                        s.push(i);
                        this->parent_[i] = v;
                    }
                }
            }
        }
        return false;
    }

    bool isCycleStrong() {
        for (auto i = 0; i != this->data_.size(); i++) {
            if (this->colors_[i] == -1) {
                if (this->isCycle(i)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    int numOfVerts;
    std::cin >> numOfVerts;
    std::vector<std::vector<int>> data(numOfVerts,
        std::vector<int>(numOfVerts));
    for (auto i = 0; i != numOfVerts; i++) {
        for (auto j = 0; j != numOfVerts; j++) {
            std::cin >> data[i][j];
        }
    }
    Graph graph(data);
    if (graph.isCycleStrong()) {
        std::cout << "YES" << "\n";
        int sz = (graph.cycle()).size();
        std::cout << sz << "\n";
        for (auto i = 0; i != sz; i++) {
            if (i == sz - 1) {
                std::cout << (graph.cycle())[i] + 1 << "\n";
            } else {
                std::cout << (graph.cycle())[i] + 1 << " ";
            }
        }
    } else {
        std::cout << "NO" << "\n";
    }
}


