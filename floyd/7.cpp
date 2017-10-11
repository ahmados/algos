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
    long int weight;
};

const bool comp(Edge edge1, Edge edge2) {
    return (edge1.weight < edge2.weight);
}

class Graph {
 public:
    std::vector<std::vector<long int>> data;
    std::vector<std::vector<bool>> closGraph;
    explicit Graph(std::vector<std::vector<long int>> data) {
        this->data = data;
    }

    long int kruskalMST(std::vector<subSet>& subsets, std::vector<Edge>& edges,
        std::vector<Edge>& result) {
        long int sum = 0;
        for (auto i = 0; i != edges.size(); i++) {
            Edge next = edges[i];
            int x = find(subsets, next.src);
            int y = find(subsets, next.trg);

            // std::cout << next.src << " " << next.trg << " " << x << " " << y << "\n";

            if (x != y) {
                myUnion(subsets, x, y);
                sum = sum + next.weight;
                std::set<std::pair<int, int>>
            }
        }
        return sum;
    }
};

int main() {
    int points, edges;
    std::cin >> points >> segs;
    std::vector<Edge> result(points);

// vector af all subsets;

    std::vector<subSet> subsets(points);
    for (int i = 0; i != points; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

// set of sorted edges;

    std::vector<Edge> edges;

    std::vector<std::vector<long int>> data(points,
        std::vector<long int>(points, 0));
    for (auto i = 0; i != segs; i++) {
            int x, y, w;
            std::cin >> x >> y >> w;
            data[x - 1][y - 1] = w;
            Edge edge;
            edge.src = x;
            edge.trg = y;
            edge.weight = w;
            edges.push_back(edge);
    }
    std::sort(edges.begin(), edges.end(), comp);
    /*for (auto a : edges) {
        std::cout << a.weight << " ";
    }
    std::cout << "\n";*/

    Graph graph(data);
    long int answer = graph.kruskalMST(subsets, edges, result);
}
