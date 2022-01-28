#include <iostream>
#include <time.h>
#include "maharaja.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No arguments" << std::endl;
        return 0;
    }

    clock_t begin = clock();
    Maharaja m = Maharaja(atoi(argv[1]),atoi(argv[1]),atoi(argv[2]));
    int positions = m.greedy_filling();
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    std::cout << time_spent << std::endl;

    std::cout << "Всего " << positions << " позиции" << std::endl;
    for (auto pos : m.get_results())
        std::cout << "(" << pos.first << "," << pos.second << ") ";
    return 0;
}
