#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <Windows.h>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) {
            return;
        }
        std::vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        std::vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }

private:
    void Merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        auto leftIt = left.begin();
        auto rightIt = right.begin();
        auto arrIt = arr.begin();

        while (leftIt != left.end() && rightIt != right.end()) {
            if (*leftIt <= *rightIt) {
                *arrIt = *leftIt;
                ++leftIt;
            }
            else {
                *arrIt = *rightIt;
                ++rightIt;
            }
            ++arrIt;
        }

        while (leftIt != left.end()) {
            *arrIt = *leftIt;
            ++leftIt;
            ++arrIt;
        }

        while (rightIt != right.end()) {
            *arrIt = *rightIt;
            ++rightIt;
            ++arrIt;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");
    

    std::vector<int> arr(10);

    std::cout << "Введите 10 чисел для сортировки: ";
    for (int& num : arr) {
        std::cin >> num;
    }

    MergeSort sorter;
    std::thread mergeSortThread([&sorter, &arr]() {
        sorter.Sort(arr);
        });

    mergeSortThread.join();

    std::cout << "Отсортированный массив: ";
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
