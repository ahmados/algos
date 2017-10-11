#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    double start;
    double end;
    double weight;
    Interval(double start, double end, double weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }

    bool operator<(Interval other) const {
        return (end < other.end);
    }
};

int prev(int j, std::vector<Interval>& vect) {
    if (vect[j].start < vect[0].end) {
        return -1;
    }
    int i = j;
    while (vect[i].end > vect[j].start) {
        if (i == 0) {
            return -1;
        }
        i--;
    }
    return i;
}

double maxweight(int n, std::vector<Interval>& vect,
    std::vector<double>& results) {
    if (n == -1) {
        return 0;
    } else {
        if (results[n] == -1) {
            results[n] = std::max((vect[n].weight + maxweight(prev(n, vect),
                vect, results)),
            maxweight(n - 1, vect, results));
            // std::cout << "A" << "\n";
            return results[n];
        } else {
            // std::cout << "B" << "\n";
            return results[n];
        }
    }
}

int main() {
    int numberOfInterval;
    std::cin >> numberOfInterval;
    std::vector<Interval> vect;
    for (auto i = 0; i != numberOfInterval; i++) {
        double start;
        double end;
        double weight;
        std::cin >> start >> end >> weight;
        Interval tempInterval = Interval(start, end, weight);
        vect.push_back(tempInterval);
    }
    std::sort(vect.begin(), vect.end());
    std::vector<double> results(vect.size());
    for (auto i = 0; i != results.size(); i++) {
        results[i] = -1;
    }
    /*  for (auto a : vect) {
          std::cout << a.start << " " << a.end << " " << a.weight << "\n";
    }  */
    std::cout << maxweight(vect.size() - 1, vect, results) << "\n";
}







