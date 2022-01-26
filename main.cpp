
#include <iostream>
#include <fstream>

#include "chessboard.h"
#include "log_duration.h"

using namespace std;


int main() {
    size_t chessboard_size = 0;
    cout << "Введите размер доски: "sv;
    cin >> chessboard_size;

    while (chessboard_size <= 0) {
        cout << "Think better, Введите размер доски: "sv;
        cin >> chessboard_size;
    }

    Chessboard chessboard(chessboard_size);

    // TODO перенести вывод времени в текстовый файл так же как и колличество процессов
    LogDuration log("Hard with par");
    chessboard.PrintHardDecision();

    return 0;
}

