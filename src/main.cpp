#include <iostream>
#include <parlay/parallel.h>

int main() {
    parlay::parallel_for(0, 10, [](int i) {
        std::cout << "Hello, World from iteration " << i << "!" << std::endl;
    });
    return 0;
}
