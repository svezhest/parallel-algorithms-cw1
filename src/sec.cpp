#include <iostream>
#include <parlay/parallel.h>
#include <vector>


int main() {
    parlay::parallel_for(0, 10, [](int i) {
        std::cout << "Hello, World from iteration " << i << "!" << std::endl;
    });
    return 0;
}

void quicksort(std::vector<int> &arr) {

}
