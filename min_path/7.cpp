#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <utility>

class District {
 public:
    std::vector<std::vector<std::vector<long long>>> data;
    std::vector<long long> distTime;
    explicit District(std::vector<std::vector<std::vector<long long>>>& Data) {
        data = Data;
        std::vector<long long> distTime(data.size(), -1);
        this->distTime = distTime;
    }

    long long busTime(long long source, long long target) {
        std::set<std::pair<long long, long long>> unVisited;
        auto defaultPair = std::make_pair(0, source);
        unVisited.insert(defaultPair);
        distTime[source] = 0;
        while (!unVisited.empty()) {
            long long u = (unVisited.begin())->second;

            unVisited.erase(unVisited.begin());
            for (auto i = 0; i != data[u].size(); i++) {
                if ((data[u][i][1] >= distTime[u]) && ((distTime[data[u][i][0]] == -1) ||
                    (data[u][i][2] < distTime[data[u][i][0]]))) {
                    unVisited.erase(std::make_pair(distTime[data[u][i][0]],
                        data[u][i][0]));
                    distTime[data[u][i][0]] = data[u][i][2];
                    unVisited.insert(std::make_pair(distTime[data[u][i][0]],
                        data[u][i][0]));
                }
            }
        }
        return distTime[target];
    }
};

int main() {
    long long numberOfVillages, numberOfRoads, src, trg;
    std::cin >> numberOfVillages;
    std::cin >> src >> trg;
    std::cin >> numberOfRoads;
    std::vector<std::vector<std::vector<long long>>> data(numberOfVillages);
    for (auto i = 0; i != numberOfRoads; i++) {
        long long firstVillage, secondVillage, time1, time2;
        std::cin >> firstVillage >> time1 >> secondVillage >> time2;
        std::vector<long long> tempVect;
        tempVect.push_back(secondVillage - 1);
        tempVect.push_back(time1);
        tempVect.push_back(time2);
        data[firstVillage - 1].push_back(tempVect);
    }

    District district = District(data);
    std::cout << district.busTime(src - 1, trg - 1) << "\n";
}
