#include <vector>
#include <iostream>
#include <utility>
#include <cmath>
#include <set>
#include <algorithm>
#include <iomanip>

struct subSet {
    int parent;
    int rank;
};

int find(std::vector<subSet>& subsets, int x) {
    if (subsets[x].parent != x) {
        subsets[x].parent  = find(subsets, subsets[x].parent);
    }
    return subsets[x].parent;
}

void myUnion(std::vector<subSet>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    subsets[xroot].parent = yroot;

    /* if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[xroot].parent = yroot;
        (subsets[yroot].rank)++;
    }*/
}

struct Edge {
    int src;
    int trg;
    double weight;
};

const bool comp(Edge edge1, Edge edge2) {
    return (edge1.weight < edge2.weight);
}

class Graph {
 public:
    std::vector<std::vector<double>> data;
    std::vector<std::vector<bool>> closGraph;
    explicit Graph(std::vector<std::vector<double>> data) {
        this->data = data;
    }

    double kruskalMST(std::vector<subSet>& subsets, std::vector<Edge>& edges,
        std::vector<Edge>& result) {
        double sum = 0;
        for (auto i = 0; i != edges.size(); i++) {
            Edge next = edges[i];
            int x = find(subsets, next.src);
            int y = find(subsets, next.trg);

            // std::cout << next.src << " " << next.trg << " " << x << " " << y << "\n";

            if (x != y) {
                myUnion(subsets, x, y);
                sum = sum + next.weight;
            }
        }
        return sum;
    }
};

int main() {
    int points;
    std::cin >> points;
    std::vector<Edge> result(points);
    std::vector<std::pair<int, int>> coordinates(points);

    for (auto i = 0; i != points; i++) {
        int x, y;
        std::cin >> x >> y;
        coordinates[i] = std::make_pair(x, y);
    }

// vector af all subsets;

    std::vector<subSet> subsets(points);
    for (int i = 0; i != points; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

// set of sorted edges;

    std::vector<Edge> edges;

    std::vector<std::vector<double>> data(points,
        std::vector<double>(points, 0.0));
    for (auto i = 0; i != points; i++) {
        for (auto j = 0; j != i; j++) {
            int x = coordinates[i].first - coordinates[j].first;
            int y = coordinates[i].second - coordinates[j].second;
            data[i][j] = std::sqrt((x) * (x) + (y) * (y));
            data[j][i] = data[i][j];
            Edge edge;
            edge.src = i;
            edge.trg = j;
            edge.weight = data[i][j];
            edges.push_back(edge);
        }
    }
    std::sort(edges.begin(), edges.end(), comp);
    /*for (auto a : edges) {
        std::cout << a.weight << " ";
    }
    std::cout << "\n";*/

    int linesegs;
    std::cin >> linesegs;
    for (auto j = 0; j != linesegs; j++) {
        int s, t;
        std::cin >> s >> t;
        int x = find(subsets, s - 1);
        int y = find(subsets, t - 1);

        if (x != y) {
            Edge edge;
            edge.src = x;
            edge.trg = y;
            edge.weight = data[x][y];
            myUnion(subsets, x, y);
        }
    }

    Graph graph(data);
    double answer = graph.kruskalMST(subsets, edges, result);
    printf("%6f\n", answer);
}

