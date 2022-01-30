#include "chessboard.h"

ChessBoard::ChessBoard(size_t chessboard_size) {
    chessboard_map_.resize(chessboard_size); // создали chessboard_size строк(y)
    for (vector<uint16_t> &x : chessboard_map_) { // создали chessboard_size столбцов(x)
        x.resize(chessboard_size, 1);    //заполнили true
    }
}

set<chessboard_map> ChessBoard::results = {};

set<chessboard_map> ChessBoard::PrintHardDecision(int start, int end) {
    vector <pair<size_t, size_t>> coordinates;
    for (size_t i = 0; i < chessboard_map_.size(); ++i) {
        for (size_t j = 0; j < chessboard_map_.size(); ++j) {
            coordinates.push_back({i, j});
        }
    }

    for (int i = start; i < end; i++) {
        int x = i / chessboard_map_.size();
        int y = i % chessboard_map_.size();
        AddMagaraja(chessboard_map_, x, y);
    }
    return results;
}

// Здесь мы КОПИРУЕМ initial_chessboard
void ChessBoard::AddMagaraja(chessboard_map initial_chessboard_map, size_t x, size_t y) const {
    CloseTargetFields(initial_chessboard_map, x, y);
    initial_chessboard_map[y][x] = 2; // Cтавим Магараджу
    bool no_fields = true;

    for (size_t i = 0; i < initial_chessboard_map.size(); ++i) { //y
        for (size_t j = 0; j < initial_chessboard_map.size(); ++j) { //x
            if (initial_chessboard_map[i][j] == 1) {
                no_fields = false;
                AddMagaraja(initial_chessboard_map, j, i);
            }
        }
    }

    if (no_fields) {
        results.insert(move(initial_chessboard_map));
    }
}

void ChessBoard::CloseTargetFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    CloseVerticalAndHorizontalFields(initial_chessboard_map, x, y);
    CloseDiagonalFields(initial_chessboard_map, x, y);
    CloseKnightFields(initial_chessboard_map, x, y);
}


void ChessBoard::CloseVerticalAndHorizontalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    for (size_t i = 0; i < initial_chessboard_map.size(); ++i) {
        initial_chessboard_map[i][x] = 0;
        initial_chessboard_map[y][i] = 0;
    }
}

void ChessBoard::CloseDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    CloseTopLeftDiagonalFields(initial_chessboard_map, x, y);
    CloseTopRightDiagonalFields(initial_chessboard_map, x, y);
    CloseDownLeftDiagonalFields(initial_chessboard_map, x, y);
    CloseDownRightDiagonalFields(initial_chessboard_map, x, y);
}

void ChessBoard::CloseKnightFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    if (x > 0 && y > 1) { //TL
        initial_chessboard_map[y - 2][x - 1] = 0;
    }
    if (x > 1 && y > 0) { //LT
        initial_chessboard_map[y - 1][x - 2] = 0;
    }
    if (x + 1 < initial_chessboard_map.size() && y > 1) { //TR
        initial_chessboard_map[y - 2][x + 1] = 0;
    }
    if (x > 1 && y + 1 < initial_chessboard_map.size()) { //LD
        initial_chessboard_map[y + 1][x - 2] = 0;
    }
    if (x + 2 < initial_chessboard_map.size() && y > 0) { //RT
        initial_chessboard_map[y - 1][x + 2] = 0;
    }
    if (x > 0 && y + 2 < initial_chessboard_map.size()) { //DL
        initial_chessboard_map[y + 2][x - 1] = 0;
    }
    if (x + 1 < initial_chessboard_map.size() && y + 2 < initial_chessboard_map.size()) { //DR
        initial_chessboard_map[y + 2][x + 1] = 0;
    }
    if (x + 2 < initial_chessboard_map.size() && y + 1 < initial_chessboard_map.size()) { //RD
        initial_chessboard_map[y + 1][x + 2] = 0;
    }
}

void ChessBoard::CloseTopLeftDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    while (x != 0 && y != 0) {
        initial_chessboard_map[y][x] = 0; //заполняет левую верхнюю диагональ
        x -= 1;
        y -= 1;
    }
    initial_chessboard_map[y][x] = 0;
}

void ChessBoard::CloseTopRightDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    while (x < initial_chessboard_map.size() && y != 0) {
        initial_chessboard_map[y][x] = 0; //заполняет правую верхнюю диагональ
        x += 1;
        y -= 1;
    }

    if (y == 0 && x != initial_chessboard_map.size()) {
        initial_chessboard_map[y][x] = 0;
    }
}

void ChessBoard::CloseDownLeftDiagonalFields(chessboard_map &initial_chessboard_map, size_t x, size_t y) const {
    while (x != 0 && y < initial_chessboard_map.size()) {
        initial_chessboard_map[y][x] = 0; //заполняет левую нижнюю диагональ
        x -= 1;
        y += 1;
    }

    if (x == 0 && y != initial_chessboard_map.size()) {
        initial_chessboard_map[y][x] = 0;
    }
}

void ChessBoard::CloseDownRightDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    while (((x += 1) < initial_chessboard_map.size()) && ((y += 1) < initial_chessboard_map.size())) {
        initial_chessboard_map[y][x] = 0; //заполняет правую нижнюю диагональ нулями
    }
}