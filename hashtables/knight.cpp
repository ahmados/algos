#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// ndef and mdef - size of the desk
long int knight(int n, int m, std::vector<std::vector<long int>>& vect) {
    if ((n == 0) && (m == 0)) {
        //std::cout << "B" << "\n";
        vect[0][0] = 1;
        return 1;
    } else if ((n < 0) || (m < 0)) {
        //std::cout << "A" << n << " " << m << "\n";
        return 0;
    } else {
        //std::cout << "C" << n << " " << m << "\n";
        if (vect[n][m] == -1) {
            vect[n][m] = (knight(n - 2, m - 1, vect) +
                knight(n - 1, m - 2, vect));
            return vect[n][m];
        } else {
            return vect[n][m];
        }
    }
}

int main() {
    int ndef, mdef;
    std::cin >> ndef >> mdef;
    std::vector<std::vector<long int>> vect(ndef, std::vector<long int>(mdef));
    for (auto i = 0; i != ndef; i++) {
        for (auto j = 0; j != mdef; j++) {
            vect[i][j] = -1;
        }
    }
    std::cout << knight(ndef - 1, mdef - 1, vect) << "\n";
}
