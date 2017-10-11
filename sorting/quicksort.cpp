#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>

template<typename Iter>
Iter partition(Iter begin, Iter end, int predicate) {
    Iter left = begin;
    Iter right = end - 1;
    int temporary;
    while ((right - left) >= 0) {
        while ((*left < predicate)) {
            left++;
        }
        while ((*right > predicate)) {
            right--;
        }
        if ((right - left) >= 0) {
            temporary = *left;
            *left = *right;
            *right = temporary;
            left++;
            right--;
        }
    }
    return (left);
}

template<typename Iter>
void quicksort(Iter begin, Iter end) {
    if ((end - begin) < 2) {
        return;
    }
    int predicate = ((*(begin + (std::rand() % (end - begin))) +
            *(begin + (std::rand() % (end - begin)))) / 2);
    auto iterPart = partition(begin, end, predicate);
    quicksort(begin, iterPart);
    quicksort(iterPart, end);
}

int main(int argc, char const *argv[]) {
    int numberOfElements;
    std::cin >> numberOfElements;
    std::vector<int> myVector;
    if (numberOfElements != 0) {
        for (auto i = 0; i != numberOfElements; i++) {
            int a;
            std::cin >> a;
            myVector.push_back(a);
        }
    }
    quicksort(myVector.begin(), myVector.end());
    for (auto a : myVector) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}

