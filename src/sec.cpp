#include <iostream>
#include <parlay/parallel.h>
#include <vector>
#include <random>
#include <iostream>

void _quicksort(std::vector<int> &arr, std::ptrdiff_t from, std::ptrdiff_t to) {
    if (to - from <= 1) {
        return;
    }

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<std::ptrdiff_t> dist(from, to - 1);
    int pivot = arr[dist(gen)];
    std::ptrdiff_t l = from;
    std::ptrdiff_t r = to;
    std::ptrdiff_t i = from;

    while (i < r) {
        if (arr[i] < pivot)      {std::swap(arr[l], arr[i]); ++l; ++i;}
        else if (arr[i] > pivot) {r--; std::swap(arr[i], arr[r]);}
        else {++i;}
    }

    _quicksort(arr, from, l + 1);
    _quicksort(arr, r, to);
}

void quicksort(std::vector<int> &arr) {
    _quicksort(arr, 0, arr.size());
}

int main() {
    // parlay::parallel_for(0, 10, [](int i) {
    //     std::cout << "Hello, World from iteration " << i << "!" << std::endl;
    // });

    auto v = std::vector<int> {1,0,6,7,3,4};
    quicksort(v);
    for (auto vv: v) {
        std::cout << vv << " ";
    }

    return 0;
}

