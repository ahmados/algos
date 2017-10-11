#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <utility>
#include <list>

class Graph {
 public:
    std::vector<std::list<std::pair<long, size_t>>> data;
    std::vector<long> disTime;
    explicit Graph(std::vector<std::list<std::pair<long,
        size_t>>>& data) {
        this->data = data;
        std::vector<long> disTime(data.size(), -1);
        this->disTime = disTime;
    }

    long dijsktra(size_t source, size_t target) {
        std::set<std::pair<long, size_t>> unVisited;
        auto defaultPair = std::make_pair(0, source);
        unVisited.insert(defaultPair);
        disTime[source] = 0;

        while (!unVisited.empty()) {
            size_t q = (unVisited.begin())->second;

            unVisited.erase(unVisited.begin());
            for (auto i = data[q].begin(); i != data[q].end(); ++i) {
                if ((disTime[q] + i->first < disTime[i->second]) ||
                    (disTime[i->second] == -1)) {
                    unVisited.erase(std::make_pair(disTime[i->second], i->second));
                        disTime[i->second] = disTime[q] +
                        i->first;
                    unVisited.insert(std::make_pair(disTime[i->second],
                        i->second));
                }
            }
        }
        return disTime[target];
    }
};

int main() {
    size_t numberOfCities, numberOfRoads;
    std::cin >> numberOfCities >> numberOfRoads;
    std::vector<std::list<std::pair<long, size_t>>> data(numberOfCities);
    for (auto i = 0; i != numberOfRoads; i++) {
        long length;
        size_t startRoad, endRoad;
        std::cin >> startRoad >> endRoad >> length;
        data[startRoad - 1].push_back(std::make_pair(length, endRoad - 1));
        data[endRoad - 1].push_back(std::make_pair(length, startRoad - 1));
    }

    size_t src, trg;
    std::cin >> src >> trg;

    Graph graph = Graph(data);
    long answer = graph.dijsktra(src - 1, trg - 1);
    std::cout << answer << "\n";
}
