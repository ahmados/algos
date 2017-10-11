#include <iostream>
#include <string>
#include <algorithm>

int remainder(std::string longNumber, int n) {
    if (n == 1) {
        return 0;
    } else if (n == 2) {
        return ((longNumber[longNumber.length() - 1] - '0') % 2);
    } else if (n == 4) {
        longNumber = "0" + longNumber;
        std::string lastTwo = longNumber.substr(longNumber.length() - 2, 2);
        int intOfLastTwo = std::stoi(lastTwo);
        return (intOfLastTwo % 4);
    } else if (n == 8) {
        longNumber = "00" + longNumber;
        std::string lastThree = longNumber.substr(longNumber.length() - 3, 3);
        int intOfLastThree = std::stoi(lastThree);
        return (intOfLastThree % 8);
    } else if (n == 3) {
        int sum = 0;
        for (auto i = 0; i != longNumber.length(); i++) {
            sum = sum + (longNumber[i] - '0');
        }
        return (sum % 3);
    } else if (n == 9) {
        int sum = 0;
        for (auto i = 0; i != longNumber.length(); i++) {
            sum = sum + (longNumber[i] - '0');
        }
        return (sum % 9);
    } else if (n == 5) {
        return ((longNumber[longNumber.length() - 1] - '0') % 5);
    } else if (n == 6) {
        if (remainder(longNumber, 3) == 0) {
            return (remainder(longNumber, 2) * 3);
        } else if (remainder(longNumber, 3) == 1) {
            return (4 - remainder(longNumber, 2) * 3);
        } else if (remainder(longNumber, 3) == 2) {
            return (remainder(longNumber, 2) * 3) + 2;
        }
    } else if (n == 7) {
        std::reverse(longNumber.begin(), longNumber.end());
        int sum = 0;
        for (auto i = 0; i != longNumber.length(); i++) {
            if ((i % 6) == 0) {
                sum = sum + (longNumber[i] - '0');
            } else if ((i % 6) == 1) {
                sum = sum + (longNumber[i] - '0') * 3;
            } else if ((i % 6) == 2) {
                sum = sum + (longNumber[i] - '0') * 2;
            } else if ((i % 6) == 3) {
                sum = sum + (longNumber[i] - '0') * 6;
            } else if ((i % 6) == 4) {
                sum = sum + (longNumber[i] - '0') * 4;
            } else if ((i % 6) == 5) {
                sum = sum + (longNumber[i] - '0') * 5;
            }
        }
        return (sum % 7);
    }
    return 0;
}

int main() {
    int n;
    std::string longNumber;
    std::cin >> n;
    std::cin >> longNumber;
    std::cout << remainder(longNumber, n) << "\n";
}




