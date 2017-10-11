#include <iostream>
#include <vector>

long long int kuznec(int n, int k, std::vector<long long int>& vect) {
    if (n == 0) {
        vect[0] = 1;
        return 1;
    } else {
        if (n < k) {
            vect[n] = kuznec(n, n, vect);
            return vect[n];
        } else {
            long long int s = 0;
            for (auto i = 1; i != k + 1; i++) {
                if (vect[n - i] == 0) {
                    vect[n - i] = kuznec(n - i, k, vect);
                    s = s + vect[n - i];
                } else {
                    s = s + vect[n - i];
                }
            }
            vect[n] = s;
            return vect[n];
        }
    }
}

int main() {
    int k, n;
    std::cin >> n >> k;
    std::vector<long long int> vect(k);
    std::cout << kuznec(n - 1, k, vect) << "\n";
}

