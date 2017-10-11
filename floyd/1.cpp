#include <vector>
#include <iostream>

class Graph {
 public:
    std::vector<std::vector<int>> data;
    std::vector<std::vector<bool>> closGraph;
    explicit Graph(std::vector<std::vector<int>> data) {
        this->data = data;
        std::vector<std::vector<bool>> closGraph(data.size(), std::vector<bool>(data.size()));
        this->closGraph = closGraph;
    }

    void floyd(int s, int v) {
        closGraph[s][v] = true;
        for (auto i = 0; i != data.size(); i++) {
            if (data[v][i] == 1) {
                if (closGraph[s][i] == false) {
                    this->floyd(s, i);
                }
            }
        }
    }

    std::vector<std::vector<bool>> getClosure() {
        for (auto i = 0; i != data.size(); i++) {
            this->floyd(i, i);
        }
        return closGraph;
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

    std::vector<std::vector<bool>> answer = graph.getClosure();
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

