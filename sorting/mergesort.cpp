#include <vector>
#include <iostream>
#include <utility>

template <typename Iter>
void maxToTheEnd(Iter begin, Iter end) {
    if ((end - begin) > 1) {
        int max = *begin;
        int index = 0;
        int maxIndex = 0;
        for (auto iter = begin; iter != end; iter++) {
            if (max < *iter) {
                max = *iter;
                maxIndex = index;
            }
            index++;
        }
        int temp = *(end - 1);
        *(end - 1) = max;
        *(begin + maxIndex) = temp;
    }
}

template <typename Iter>
void maxSelectionSort(Iter begin, Iter end) {
    if ((end - begin) > 1) {
        for (auto i = 0; i != (end - begin); i++) {
            maxToTheEnd(begin, end - i);
        }
    }
}

template <typename Iter>
void merge_help(Iter beginFirst, Iter endFirst,
                Iter beginSecond, Iter endSecond, Iter result) {
    int sizeFirst = endFirst - beginFirst;
    int sizeSecond = endSecond - beginSecond;
    int indexOne = 0;
    int indexTwo = 0;
    for (auto i = 0; i != sizeFirst + sizeSecond; i++) {
        if ((indexOne < sizeFirst) && (indexTwo < sizeSecond)) {
            if ((*(beginFirst + indexOne) < *(beginSecond + indexTwo))
            /*&& (indexOne < sizeFirst)*/) {
                *(result + i) = *(beginFirst + indexOne);
                indexOne++;
                // std::cout << "  index_one:  "<< indexOne;
            } else {
                *(result + i) = *(beginSecond + indexTwo);
                indexTwo++;
                // std::cout << "  index_two:  " << indexTwo;
            }
        } else if (indexOne >= sizeFirst) {
            *(result + i) = *(beginSecond + indexTwo);
            indexTwo++;
        } else {
            *(result + i) = *(beginFirst + indexOne);
            indexOne++;
        }
    }
    // std::cout << "\n";
}

template<typename Iter>
void merge_sort(Iter begin, Iter end) {
    int size = end - begin;
    if (size < 2) {
        return;
    }
    Iter mid = begin + (size / 2);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    std::vector<int> result(size);
    merge_help(begin, mid, mid, end, result.begin());
    std::move(result.begin(), result.end(), begin);
}

int main(int argc, char const *argv[]) {
    int numberOfElements;
    std::cin >> numberOfElements;
    std::vector<int> myVector;
    std::vector<int> secondVector;
    if (numberOfElements != 0) {
        for (auto i = 0; i != numberOfElements; i++) {
            int a;
            std::cin >> a;
            myVector.push_back(a);
        }
    }
    merge_sort(myVector.begin(), myVector.end());
    for (auto a : myVector) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}

