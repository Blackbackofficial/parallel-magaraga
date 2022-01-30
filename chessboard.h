#include <vector>
#include <iostream>
#include <fstream>
#include <set>

using chessboard_map = std::vector<std::vector<uint16_t>>;//(y,x)

inline bool operator < (const chessboard_map& lhs, const chessboard_map& rhs);

class Chessboard {
public:
    Chessboard(std::size_t chessboard_size);
    std::set<chessboard_map> PrintHardDecision(int start, int end);
private:
    chessboard_map chessboard_map_;      //в конструкторе заполняется еденицами(true), по дефолту нулями;
    static std::set<chessboard_map> results; // здесь храним удачные результаты

    void AddMagaraja(chessboard_map initial_chessboard_map, size_t x, size_t y) const;

    void CloseTargetFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;

    void CloseVerticalAndHorizontalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseKnightFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseTopLeftDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseTopRightDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseDownLeftDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;
    void CloseDownRightDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const;

    void Print(std::ofstream& out) const;
};
