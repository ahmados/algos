#include <vector>
#include <iostream>
#include <utility>

class Graph {
 public:
    std::vector<std::vector<long int>> data;
    std::vector<std::vector<bool>> closGraph;
    explicit Graph(std::vector<std::vector<long int>> data) {
        this->data = data;
    }

    long int minWeight(std::vector<long int> minCutWeight,
        std::vector<bool> mstSet) {
        long int min = -1;
        long int min_index;
        for (auto i = 0; i != data.size(); i++) {
            if ((!mstSet[i]) && ((minCutWeight[i] < min)
                || (min == -1))) {
                min = minCutWeight[i];
                min_index = i;
            }
        }
        return min_index;
    }

    long int treeWeight(std::vector<long int> parent) {
        long int sum = 0;
        for (auto i = 1; i != parent.size(); i++) {
            sum = sum + data[parent[i]][i];
        }
        return sum;
    }

    std::pair<int, std::vector<long int>> primMST(long int max) {
        std::vector<long int> parent(data.size(), -2);
        std::vector<long int> minCutWeight(data.size(), 300000);
        std::vector<bool> mstSet(data.size());

        minCutWeight[0] = 0;
        parent[0] = -1;

        for (auto i = 0; i != data.size() - 1; i++) {
            long int u = minWeight(minCutWeight, mstSet);
            mstSet[u] = true;

            for (long int j = 0; j != data.size(); j++) {
                if (data[u][j] != 0) {
                    if ((!mstSet[j]) && (data[u][j] < minCutWeight[j])) {
                        parent[j] = u;
                        minCutWeight[j] = data[u][j];
                    }
                }
            }
        }

        return std::make_pair((this->treeWeight(parent)), parent);
    }
    /* int helpMST() {

    }*/

    long int TestPrimMST(int x, int y, int min) {
        int temp = data[x][y];
        data[x][y] = 300000;
        std::vector<long int> parent(data.size(), -2);
        std::vector<long int> minCutWeight(data.size(), 300000);
        std::vector<bool> mstSet(data.size());

        minCutWeight[0] = 0;
        parent[0] = -1;

        for (auto i = 0; i != data.size() - 1; i++) {
            long int u = minWeight(minCutWeight, mstSet);
            mstSet[u] = true;

            if (minCutWeight[u] == 300000) {
                data[x][y] = temp;
                return min;
            }

            for (long int j = 0; j != data.size(); j++) {
                if (data[u][j] != 0) {
                    if ((!mstSet[j]) && (data[u][j] < minCutWeight[j])) {
                        parent[j] = u;
                        minCutWeight[j] = data[u][j];
                    }
                }
            }
        }
        data[x][y] = temp;
        for (auto i = 0; i != parent.size(); i++) {
            if (parent[i] == -2) {
                return -1;
            }
        }
        return (this->treeWeight(parent));
    }
};

int main() {
    long int vertices, edges;
    long int max = 0;
    std::cin >> vertices >> edges;
    std::vector<std::vector<long int>> data(vertices,
        std::vector<long int>(vertices));
    for (auto i = 0; i != edges; i++) {
        long int a, b, w;
        std::cin >> a >> b >> w;
        data[a - 1][b - 1] = w;
        data[b - 1][a - 1] = w;
        if (w > max) {
            max = w;
        }
    }
    Graph graph(data);
    std::pair<long int, std::vector<long int>> answer = graph.primMST(max);
    auto parent = answer.second;
    std::cout << answer.first << " ";
    auto min = 300000;
    for (auto i = 1; i != data.size(); i++) {
        auto temp = graph.TestPrimMST(parent[i], i, min);
        if ((temp < min) && (temp != -1)) {
            min = temp;
        }
    }
    std::cout << min << "\n";
}
