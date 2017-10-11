#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::list<int> ordered_;
    std::vector<bool> isDiscovered_;
    std::vector<std::vector<int>> strongComps_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<bool> defaultBool(data.size(), false);
        this->isDiscovered_ = defaultBool;
    }

    int size() const {
        return this->data_.size();
    }

    Graph getTranspose() {
        std::vector<std::vector<int>>
        dataTranspose(this->data_.size());
        for (int i = 0; i != this->data_.size(); i++) {
            for (auto a : this->data_[i]) {
                dataTranspose[a].push_back(i);
            }
        }
        Graph graphT(dataTranspose);
        return graphT;
    }

    void visit(int i, std::vector<int>& temp) {
        this->isDiscovered_[i] = true;
        temp.push_back(i);
        for (auto a : this->data_[i]) {
            if (!this->isDiscovered_[a]) {
                visit(a, temp);
            }
        }
    }

    void fillOrder(int i, std::stack<int>& stack) {
        this->isDiscovered_[i] = true;

        for (auto a : this->data_[i]) {
            if (!this->isDiscovered_[a]) {
                fillOrder(a, stack);
            }
        }

        stack.push(i);
    }

    std::vector<bool> isDiscovered() {
        return this->isDiscovered_;
    }

    void sconn() {
        std::stack<int> stack;

        for (auto i = 0; i != this->data_.size(); i++) {
            if (!isDiscovered_[i]) {
                fillOrder(i, stack);
            }
        }

        Graph graphRev = this->getTranspose();

        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (!graphRev.isDiscovered()[v]) {
                std::vector<int> temp;
                graphRev.visit(v, temp);
                this->strongComps_.push_back(temp);
            }
        }
    }

    std::vector<std::vector<int>> getStrongComps() {
        return this->strongComps_;
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
    }

    Graph graph(data);
    graph.sconn();
    std::vector<std::vector<int>> strongComps = graph.getStrongComps();
    std::vector<int> topological(data.size());
    for (auto j = 0; j != strongComps.size(); j++) {
        for (auto i = 0; i != strongComps[j].size(); i++) {
            topological[strongComps[j][i]] = j;
        }
    }
    std::cout << strongComps.size() << "\n";
    for (auto i = 0; i != topological.size(); i++) {
        if (i == (topological.size() - 1)) {
            std::cout << topological[i] + 1 << "\n";
        } else {
            std::cout << topological[i] + 1 << " ";
        }
    }
}
