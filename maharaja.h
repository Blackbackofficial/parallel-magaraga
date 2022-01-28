//
// Created by User on 28.01.2022.
//

#ifndef MPI_MAG_MAHARAJA_H
#define MPI_MAG_MAHARAJA_H

#include <vector>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <iostream>

typedef std::pair<int, int> position;

class Maharaja {
private:
    int width;
    int height;
    int processes;
    std::vector<bool> cells;
    std::vector<position> positions;

    bool full_check();
    int count_ceils(int x, int y);
    position search_min_position();

public:
    Maharaja(int xM, int yM, int processes) {
        this->width = xM;
        this->height = yM;
        this->cells = std::vector<bool>(xM*yM, false);
        this->processes = processes;
    };

    bool take_position(int x, int y);
    int greedy_filling();
    std::vector<position> get_results() { return positions; }
};

#endif //MPI_MAG_MAHARAJA_H
