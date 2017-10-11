#include <vector>
#include <iostream>
#include <queue>
#include <utility>


class Metro {
 private:
    std::vector<std::vector<int>> data_;
 public:

    explicit Metro(std::vector<std::vector<int>> data) {
        this->data_ = data;
    }

    int howMany(int source, int target) {
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
                        // std::cout << i << " ";
                        q.push(i);
                        dis[i] = dis[curr] + 1;
                        if (i == target) {
                            return (dis[i] - 1);
                        }
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    int numberOfStation, numberOfLines;
    std::cin >> numberOfStation;
    std::cin >> numberOfLines;
    std::vector<std::vector<int>> data(numberOfStation,
        std::vector<int>(numberOfStation));
    for (auto i = 0; i != numberOfLines; i++) {
        int num;
        std::cin >> num;
        std::vector<int> stations;
        for (auto k = 0; k != num; k++) {
            int st;
            std::cin >> st;
            stations.push_back(st);
        }
        for (auto j = 0; j != stations.size(); j++) {
            for (auto h = 0; h != stations.size(); h++) {
                data[stations[j] - 1][stations[h] - 1] = 1;
            }
        }
    }
    int src, trg;
    std::cin >> src >> trg;
    /* for (auto i = 0; i != data.size(); i++) {
        for (auto j = 0; j != data.size(); j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }*/
    Metro metro = Metro(data);
    int answer = metro.howMany(src - 1, trg - 1);
    std::cout << answer << "\n";
}
