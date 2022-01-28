#include <iostream>
#include "maharaja.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No arguments" << std::endl;
        return 0;
    }

    Maharaja m = Maharaja(atoi(argv[1]),atoi(argv[1]),atoi(argv[2]));
    int positions = m.greedy_filling();
    std::cout << "Всего " << positions << " позиции" << std::endl;
    for (auto pos : m.get_results())
        std::cout << "(" << pos.first << "," << pos.second << ") ";
    return 0;
}
