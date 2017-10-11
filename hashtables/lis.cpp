#include <iostream>
#include <vector>
#include <algorithm>

// Binary search (note boundaries in the caller)
int SearchIndex(std::vector<int>& v, std::vector<int>& tailIndex,
    int l, int r, int key) {
    while ((r - l) > 1) {
    int m = l + (r - l)/2;
    if (v[tailIndex[m]] >= key)
        r = m;
    else
        l = m;
    }

    return r;
}

std::vector<int> LongestIncreasingSubsequence(std::vector<int>& v) {
    std::vector<int> result;
    std::vector<int> tailIndex(v.size());
    std::vector<int> prevIndex(v.size(), - 1);
    int length = 1;
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] <= v[tailIndex[0]]) {
            tailIndex[0] = i;
        } else if (v[i] > v[tailIndex[length - 1]]) {
            tailIndex[length] = i;
            prevIndex[i] = tailIndex[length - 1];
            length++;
        } else {
            int pos = SearchIndex(v, tailIndex, 0, length - 1, v[i]);
            tailIndex[pos] = i;
            prevIndex[i] = tailIndex[pos - 1];
        }
    }
    for (int i = tailIndex[length - 1]; i >= 0; i = prevIndex[i]) {
        result.push_back(v[i]);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (auto i = 0; i != n; i++) {
        std::cin >> v[i];
    }
    auto result = LongestIncreasingSubsequence(v);
    for (auto j = 0; j != result.size(); j++) {
        std::cout << result[j];
        if (j == (result.size() - 1)) {
            std::cout << "\n";
        } else {
            std::cout << " ";
        }
    }
}


