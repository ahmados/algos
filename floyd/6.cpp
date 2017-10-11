#include <vector>
#include <iostream>
#include <utility>

class Graph {
 public:
    std::vector<std::vector<int>> data;
    std::vector<std::vector<bool>> closGraph;
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data = data;
    }

    int minWeight(std::vector<int> minCutWeight,
        std::vector<bool> mstSet) {
        int min = -1;
        int min_index;
        for (auto i = 0; i != data.size(); i++) {
            if ((!mstSet[i]) && ((minCutWeight[i] < min)
                || (min == -1))) {
                min = minCutWeight[i];
                min_index = i;
            }
        }
        return min_index;
    }

    std::pair<std::pair<std::vector<int>, int>,
    std::vector<std::pair<int, int>>> treeU(std::vector<int> parent) {
        std::vector<int> ourVect(parent.size());
        std::vector<std::pair<int, int>> ans(parent.size());
        if (parent.size() == 1) {
            return std::make_pair(std::make_pair(ourVect, 0), ans);
        }
        int sum = 0;
        for (auto i = 1; i != parent.size(); i++) {
            if (parent[i] == -1) {
                return std::make_pair(std::make_pair(ourVect, -1), ans);
            }
            sum = sum + data[parent[i]][i];
            ourVect[i] = data[parent[i]][i];
            ans[i] = std::make_pair(parent[i], i);
        }
        return std::make_pair(std::make_pair(ourVect, sum), ans);
    }

    std::pair<std::pair<std::vector<int>, int>, std::vector<std::pair<int, int>>>
    primMST() {
        std::vector<int> parent(data.size(), -1);
        std::vector<int> minCutWeight(data.size(), 30001);
        std::vector<bool> mstSet(data.size());

        minCutWeight[0] = 0;
        parent[0] = -1;

        for (auto i = 0; i != data.size() - 1; i++) {
            int u = minWeight(minCutWeight, mstSet);
            mstSet[u] = true;

            for (int j = 0; j != data.size(); j++) {
                if (data[u][j] != 0) {
                    if ((!mstSet[j]) && (data[u][j] < minCutWeight[j])) {
                        parent[j] = u;
                        minCutWeight[j] = data[u][j];
                    }
                }
            }
        }
        return (this->treeU(parent));
    }

    void localNetwork(int p5, int p6, int q5, int q6, bool flag) {
        auto mst = (this->primMST()).first;
        auto ans = (this->primMST()).second;
        if ((mst.second > (q1 + q2)) || (mst.second == -1)) {
            std::cout << "Impossible" << "\n";
        }
        std::vector<std::vector<int>> dp(data.size() + 1,
            std::vector<int>(q5 + 1));
        std::vector<std::vector<bool>> prev(data.size() + 1,
            std::vector<int>(q6 + 1));
        for (auto i = 1; i != data.size(); i++) {
            for (auto j = 0; j != q5 + 1; j++) {
                dp[i][j] = dp[i - 1][j];
                if (!(mst.first[i - 1] > j)) {
                    prev[i][j] = 0;
                    if (dp[i][j] < dp[i - 1][j - mst.first[i - 1]]
                        + mst.first[i - 1]) {
                        dp[i][j] = dp[i - 1][j - mst.first[i - 1]]
                        + mst.first[i - 1];
                        prev[i][j] = 1;
                    }
                }
            }
        }
        std::vector<bool> u(data.size() + 1);
        int result = 0;
        int cur1 = data.size() - 1;
        int cur2 = q5;
        while (cur1 > 0) {
            if (prev[cur1][cur2]) {
                cur2 = cur2 - mst.first[cur1 - 1];
                result += mst.first[cur1 - 1];
                u[cur1] = 1;
            }
            cur1 = cur1 - 1;
        }
        if ((mst.second - result) > q6) {
            std::cout << "Impossible" << "\n";
        }
        std::cout << (mst.second - result) * p6 + result * p5 << "\n";
        for (auto i = 0; i != data.size() - 1; i++) {
            std::cout << ans[i] + 1 << " ";
            if (flag) {
                if (u[i + 1]) {
                    std::cout << 6 << "\n";
                } else {
                    std::cout << 5 << "\n";
                }
            } else {
                if (u[i + 1]) {
                    std::cout << 5 << "\n";
                } else {
                    std::cout << 6 << "\n";
                }
            }
        }
    }
};

int main() {
    int vertices, edges;
    int max = 0;
    std::cin >> vertices >> edges;
    std::vector<std::pair<int, int>> preAns;
    std::vector<std::vector<int>> data(vertices,
        std::vector<int>(vertices));
    for (auto i = 0; i != edges; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        data[a - 1][b - 1] = w;
        data[b - 1][a - 1] = w;
        if (w > max) {
            max = w;
        }
        preAns.push_back();
    }
    Graph graph(data);
    int p5, q5, p6, q6;
    std::cin >> p5 >> q5 >> p6 >> q6;
    bool flag = 0;
    if (p5 > p6) {
        std::swap(p5, p6);
        std::swap(q5, q6);
        flag = 1;
    }
    graph.localNetwork(p5, p6, q5, q6, flag);
}

