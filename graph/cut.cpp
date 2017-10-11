#include <vector>
#include <iostream>
#include <algorithm>

class Graph {
 private:
    std::vector<std::vector<int>> data_;
    std::vector<bool> isDiscovered_;
    std::vector<int> discTime_;
    std::vector<int> low_;
    std::vector<int> parent_;
    std::vector<bool> isAP_;

 public:
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data_ = data;
        std::vector<bool> defaultBool(data.size(), false);
        this->isDiscovered_ = defaultBool;
        std::vector<int> defaultVector(data.size());
        this->discTime_ = defaultVector;
        this->low_ = defaultVector;
        std::vector<int> parents(data.size(), -1);
        this->parent_ = parents;
        this->isAP_ = defaultBool;
    }

    void APhelp(int a) {
        static int time = 0;
        int childNum = 0;
        this->isDiscovered_[a] = true;
        this->discTime_[a] = time;
        this->low_[a] = time;
        time++;

        for (auto v : this->data_[a]) {
            if (!this->isDiscovered_[v]) {
                childNum++;
                this->parent_[v] = a;
                this->APhelp(v);

                this->low_[a] = std::min(this->low_[a], this->low_[v]);

                if ((this->parent_[a] == -1) && (childNum > 1)) {
                    this->isAP_[a] = true;
                }

                if ((this->parent_[a] != -1) &&
                    (this->low_[v] >= this->discTime_[a])) {
                    this->isAP_[a] = true;
                }
            } else if (v != this->parent_[a]) {
                this->low_[a] = std::min(this->low_[a], this->discTime_[v]);
            }
        }
    }

    void superAP() {
        for (auto i = 0; i != this->data_.size(); i++) {
            if (!this->isDiscovered_[i]) {
                APhelp(i);
            }
        }

        std::vector<int> articulPoints;

        for (auto i = 0; i != this->data_.size(); i++) {
            if (this->isAP_[i]) {
                articulPoints.push_back(i);
            }
        }

        std::sort(articulPoints.begin(), articulPoints.end());

        std::cout << articulPoints.size() << "\n";
        for (auto a : articulPoints) {
            std::cout << a + 1 << "\n";
        }
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

    graph.superAP();
}
