#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<int> printLCS(std::vector<std::vector<int>>& way, std::vector<int>& seq,
    int i, int j, std::vector<int>& result) {
    if ((i == 0) || (j == 0)) {
        return result;
    }
    if (way[i][j] == 1) {
        result = printLCS(way, seq, i - 1, j - 1, result);
        result.push_back(seq[i - 1]);
        return result;
    } else if (way[i][j] == 0) {
        result = printLCS(way, seq, i - 1, j, result);
        return result;
    } else {
        result = printLCS(way, seq, i, j - 1, result);
        return result;
    }
}

int main() {
    int firstLen, secondLen;

    std::cin >> firstLen;
    std::vector<int> firstSeq(firstLen);
    for (auto i = 0; i != firstLen; i++) {
        std::cin >> firstSeq[i];
    }

    std::cin >> secondLen;
    std::vector<int> secondSeq(secondLen);
    for (auto i = 0; i != secondLen; i++) {
        std::cin >> secondSeq[i];
    }

    std::vector<std::vector<int>> way(firstLen + 1,
        std::vector<int>(secondLen + 1));
    std::vector<std::vector<int>> lcs(firstLen + 1,
        std::vector<int>(secondLen + 1));

    for (auto i = 0; i != firstLen + 1; i++) {
        lcs[i][0] = 0;
    }

    for (auto j = 0; j != secondLen + 1; j++) {
        lcs[0][j] = 0;
    }

    for (auto i = 1; i != firstLen + 1; i++) {
        for (auto j = 1; j != secondLen + 1; j++) {
            if (firstSeq[i - 1] == secondSeq[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                way[i][j] = 1;
            } else if (lcs[i - 1][j] >= lcs[i][j - 1]) {
                lcs[i][j] = lcs[i - 1][j];
                way[i][j] = 0;
            } else {
                lcs[i][j] = lcs[i][j - 1];
                way[i][j] = 2;
            }
        }
    }
    std::vector<int> result;
    result = printLCS(way, firstSeq, firstLen, secondLen, result);
    for (auto i = 0; i != result.size(); i++) {
        std::cout << result[i];
        if (i == (result.size() - 1)) {
            std::cout << "\n";
        } else {
            std::cout << " ";
        }
    }
}
