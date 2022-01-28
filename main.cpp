#include <iostream>
#include "maharaja.h"

int main() {
    Maharaja m = Maharaja(4,4,5);
    int positions = m.greedy_filling();
    std::cout << "Всего " << positions << " позиции" << std::endl;
    for (auto pos : m.get_results())
        std::cout << "(" << pos.first << "," << pos.second << ") ";
    return 0;
}
