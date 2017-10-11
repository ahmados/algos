#include <vector>
#include <iostream>
#include <queue>
#include <utility>

class Chessboard {
 private:
    std::vector<std::vector<int>> data_;
    std::pair<int, int> food_;
    std::vector<bool> isVisited_;

 public:
    explicit Chessboard(std::vector<std::vector<int>> data,
        std::pair<int, int> food) {
        this->data_ = data;
        this->food_ = food;
        std::vector<bool>
        isVisited((this->data_.size() * this->data_[0].size()), false);
        this->isVisited_ = isVisited;
    }

    int size() {
        return this->data_.size();
    }

    bool isVisited(std::pair<int, int> a) {
        // std::cout << a.first << " " << this->data_[0].size() << " " << a.second << "\n";
        return this->isVisited_[a.first * this->data_[0].size() + a.second];
    }

    int bfs(std::pair<int, int> source) {
        int sum = 0;
        int m = this->data_[0].size();
        std::vector<int> dis(this->data_.size() * this->data_[0].size(), -1);
        dis[source.first * m + source.second] = 0;
        this->isVisited_[source.first * m + source.second] = true;
        std::queue<std::pair<int, int>> q;
        q.push(source);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            std::vector<std::pair<int, int>> pairVect(8);
            pairVect[0] = std::make_pair(curr.first + 1, curr.second - 2);
            pairVect[1] = std::make_pair(curr.first + 1, curr.second + 2);
            pairVect[2] = std::make_pair(curr.first - 1, curr.second - 2);
            pairVect[3] = std::make_pair(curr.first - 1, curr.second + 2);
            pairVect[4] = std::make_pair(curr.first + 2, curr.second - 1);
            pairVect[5] = std::make_pair(curr.first + 2, curr.second + 1);
            pairVect[6] = std::make_pair(curr.first - 2, curr.second - 1);
            pairVect[7] = std::make_pair(curr.first - 2, curr.second + 1);
            for (auto i = 0; i != 8; i++) {
                int firstC = pairVect[i].first;
                int secondC = pairVect[i].second;
                if ((firstC < (this->data_.size()))
                    && (secondC < (this->data_[0].size()))) {
                    if (dis[firstC * m + secondC] == -1) {
                        q.push(pairVect[i]);
                        dis[firstC * m + secondC] =
                        dis[curr.first * m + curr.second] + 1;
                        if (this->data_[firstC][secondC] == 1) {
                            this->isVisited_[firstC * m + secondC] = true;
                            sum += dis[firstC * m + secondC];
                        }
                    }
                }
            }
        }
        return sum;
    }
};

int main() {
    int n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;
    auto food = std::make_pair(s - 1, t - 1);
    std::vector<std::pair<int, int>> blohs;
    std::vector<std::vector<int>> data(n,
        std::vector<int>(m));
    for (auto i = 0; i != q; i++) {
        int first, second;
        std::cin >> first >> second;
        data[first - 1][second - 1] = 1;
        auto bloh = std::make_pair(first - 1, second - 1);
        blohs.push_back(bloh);
    }
    Chessboard chessboard(data, food);
    int sum = chessboard.bfs(food);
    bool check = true;
    for (auto a : blohs) {
        if (!(chessboard.isVisited(a))) {
            check = false;
            // std::cout << a.first << " " << a.second << "\n";
        }
    }
    if (check) {
        std::cout << sum << "\n";
    } else {
        std::cout << -1 << "\n";
    }
}
