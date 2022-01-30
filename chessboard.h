#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <mpi.h>
#include <time.h> 
#include <set>


#define FIRST_THREAD 0


using namespace std;
using chessboard_map = vector<vector<uint16_t>>; //(y,x)


class Chessboard {
    public:
        Chessboard(size_t chessboard_size);
        set<chessboard_map> PrintHardDecision(int start, int end);

    private:
        chessboard_map chessboard_map_; //в конструкторе заполняется еденицами(true), по дефолту нулями;
        static set<chessboard_map> results; // здесь храним удачные результаты

        void AddMagaraja(chessboard_map initial_chessboard_map, size_t x, size_t y) const;

        void CloseTargetFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseVerticalAndHorizontalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseKnightFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseTopLeftDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseTopRightDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseDownLeftDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
        void CloseDownRightDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const;
};