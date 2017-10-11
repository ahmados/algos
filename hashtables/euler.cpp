#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

class City {
 private:
    std::vector<std::vector<int>> data_;

 public:
    explicit City(std::vector<std::vector<int>> data) {
        this->data_ = data;
    }

    int size() {
        return this->data_.size();
    }

    void remove(int n, int m) {
        this->data_[n][m]--;
        this->data_[m][n]--;
    }

    std::vector<int> eulerPath(int v) {
        std::vector<int> path;
        std::stack<int> s;
        s.push(v);
        while (!s.empty()) {
           int w = s.top();
            for (auto a = 0; a != this->data_.size(); a++) {
                if (this->data_[w][a] != 0) {
                    s.push(a);
                    this->remove(w, a);
                    a = this->data_.size() - 1;
                }
            }

            if (w == s.top()) {
                s.pop();
                path.push_back(w);
            }
        }
        return path;
    }
};

int main() {
    int numberOfSquares;
    std::vector<int> path;
    int start = 0;
    std::cin >> numberOfSquares;
    std::vector<int> degree(numberOfSquares);
    std::vector<std::vector<int>> data(numberOfSquares,
        std::vector<int>(numberOfSquares));
    for (auto i = 0; i != numberOfSquares; i++) {
        std::cin >> degree[i];

        if ((degree[i] % 2) == 1) {
            start = i;
        }

        for (auto j = 0; j != degree[i]; j++) {
            int a, length;
            std::cin >> a >> length;
            (data[i][a - 1])++;
        }
    }
    City city(data);
    path = city.eulerPath(start);
    std::cout << path.size() - 1 << "\n";
    for (auto i = 0; i != path.size(); i++) {
        if (i != path.size() - 1) {
            std::cout << path[i] + 1 << " ";
        } else {
            std::cout << path[i] + 1 << "\n";
        }
    }
    /*for (auto a : data) {
        for (auto b : a) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }*/
}








