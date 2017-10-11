#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <utility>
#include <list>

class SummerCamp {
 public:
    std::vector<std::list<std::pair<long long, long long>>> data;
    std::vector<std::vector<long long>> maxMass;
    explicit SummerCamp(std::vector<std::list<std::pair<long long, long long>>>& Data,
        std::vector<std::vector<long long>> MaxMass) {
        data = Data;
        maxMass = MaxMass;
    }

    long long dijsktra(long long source, long long target, long long weight) {
        std::vector<long long> distTime(data.size(), -1);
        std::set<std::pair<long long, long long>> unVisited;
        auto defaultPair = std::make_pair(0, source);
        unVisited.insert(defaultPair);
        distTime[source] = 0;

        while (!unVisited.empty()) {
            long long q = (unVisited.begin())->second;

            unVisited.erase(unVisited.begin());
            for (auto i = data[q].begin(); i != data[q].end(); ++i) {
                if ((weight <= maxMass[q][i->second]) &&
                    ((distTime[q] + i->first < distTime[i->second]) ||
                    (distTime[i->second] == -1))) {
                    unVisited.erase(std::make_pair(distTime[i->second],
                        i->second));
                        distTime[i->second] = distTime[q] +
                        i->first;
                    unVisited.insert(std::make_pair(distTime[i->second],
                        i->second));
                }
            }
        }
        return distTime[target];
    }

    long long binarySearch(long long src, long long trg, long long time, long long widest) {
        if (data.size() == 1) {
            return 10000000;
        }
        long long l = 0;
        long long m;
        long long r = 10000000;
        while (l <= r) {
            m = (l + r) / 2;
            /* std::cout << m << " " << this->dijsktra(src, trg, m)
            << " " << this->dijsktra(src, trg, m + 1) << " "
            << time << "\n";*/
            if (((this->dijsktra(src, trg, m) <= time) &&
                (this->dijsktra(src, trg, m) != -1)) &&
            ((this->dijsktra(src, trg, m + 1) > time) ||
                (this->dijsktra(src, trg, m + 1) == -1))) {
                return m;
            } else if ((this->dijsktra(src, trg, m) <= time) &&
                (this->dijsktra(src, trg, m) != -1)) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return 0;
    }
};

int main() {
    long long vertices, edges;
    std::cin >> vertices >> edges;
    std::vector<std::list<std::pair<long long, long long>>> data(vertices);
    std::vector<std::vector<long long>> maxMass(vertices,
        std::vector<long long>(vertices));
    long long widest = 0;
    for (auto i = 0; i != edges; i++) {
        long long v1, v2, t, mass;
        std::cin >> v1 >> v2 >> t >> mass;
        mass = (mass - 3000000) / 100;
        if (widest < mass) {
            widest = mass;
        }
        maxMass[v1 - 1][v2 - 1] = mass;
        maxMass[v2 - 1][v1 - 1] = mass;
        data[v1 - 1].push_back(std::make_pair(t, v2 - 1));
        data[v2 - 1].push_back(std::make_pair(t, v1 - 1));
    }
    SummerCamp lksh = SummerCamp(data, maxMass);
    long long answer = lksh.binarySearch(0, vertices - 1, 1440, widest);
    /* for (auto a : maxMass) {
        for (auto b : a) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }*/
    std::cout << answer << "\n";
}
