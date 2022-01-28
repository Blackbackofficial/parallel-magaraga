#include <iostream>
#include <chrono>
#include "maharaja.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No arguments" << std::endl;
        return 0;
    }

    auto begin = std::chrono::steady_clock::now();
    Maharaja m = Maharaja(atoi(argv[1]),atoi(argv[1]),atoi(argv[2]));
    int positions = m.greedy_filling();


    std::cout << "Всего " << positions << " позиции" << std::endl;
    for (auto pos : m.get_results())
        std::cout << "(" << pos.first << "," << pos.second << ") ";
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    return 0;
}
