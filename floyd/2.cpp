#include <vector>
#include <iostream>

class Graph {
 public:
    std::vector<std::vector<int>> data;
    std::vector<std::vector<int>> dist;
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data = data;
        this->dist = data;
    }

    std::vector<std::vector<int>> floyd() {
        for (auto k = 0; k != data.size(); k++) {
            for (auto i = 0; i != data.size(); i++) {
                for (auto j = 0; j != data.size(); j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        return this->dist;
    }
};

int main() {
    int vertices;
    std::cin >> vertices;
    std::vector<std::vector<int>> data(vertices, std::vector<int>(vertices));
    for (auto i = 0; i != vertices; i++) {
        for (auto j = 0; j != vertices; j++) {
            std::cin >> data[i][j];
        }
    }
    Graph graph(data);

    std::vector<std::vector<int>> answer = graph.floyd();
    for (auto i = 0; i != vertices; i++) {
        for (auto j = 0; j != vertices; j++) {
            if (j != (vertices - 1)) {
                std::cout << answer[i][j] << " ";
            } else {
                std::cout << answer[i][j] << "\n";
            }
        }
    }
}
