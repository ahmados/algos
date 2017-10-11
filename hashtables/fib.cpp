#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long int myPrime = 10000000000000099;
    std::vector<long long int> fibs(30000);
    fibs[0] = 1;
    fibs[1] = 1;
    std::string fibYouWant;
    std::string resultString = "";
    int numberOfQuires;

    for (auto i = 0; i != 30000; i++) {
        fibs[i + 2] = (fibs[i + 1] + fibs[i]) % myPrime;
    }
    std::sort(fibs.begin(), fibs.end());
    std::cin >> numberOfQuires;

    for (auto i = 0; i != numberOfQuires; i++) {
        long long int tempLong = 0;
        std::cin >> fibYouWant;

        for (auto i = 0; i != fibYouWant.length(); i++) {
            tempLong = (fibYouWant[i] - '0') + tempLong * 10;
            tempLong = tempLong % myPrime;
        }

        long long int realFib = tempLong;

        auto result = std::binary_search(fibs.begin(), fibs.end(), realFib);

        if (result) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}




