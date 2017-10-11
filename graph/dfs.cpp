#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<std::vector<int>> comps_;
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

    void DFS(int a) {
        std::vector<int> currComp;
        std::stack<int> s;
        s.push(a);
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (this->isDiscovered_[v] == false) {
                this->isDiscovered_[v] = true;
                currComp.push_back(v);
                for (auto a : (this->data_)[v]) {
                    s.push(a);
                }
            }
        }
        this->comps_.push_back(currComp);
    }

    void advancedDFS() {
        for (auto i = 0; i != this->size(); i++) {
            if (this->isDiscovered_[i] == false) {
                this->DFS(i);
            }
        }
    }

    std::vector<std::vector<int>> getComps() {
        return comps_;
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
    graph.advancedDFS();
    std::vector<std::vector<int>> comps = graph.getComps();
    std::cout << comps.size() << "\n";
    for (auto a : comps) {
        std::cout << a.size() << "\n";
        std::cout << a[0] + 1;
        for (auto i = 1; i != a.size(); i++) {
            std::cout << " " << a[i] + 1;
        }
        std::cout << "\n";
    }
}
