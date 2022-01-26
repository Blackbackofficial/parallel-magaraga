cmake_minimum_required(VERSION 3.11)

project(Magaraja)
set(CMAKE_CXX_STANDARD 17)

# воспользуйтесь этой переменной при создании цели
set(FILES chessboard.h chessboard.cpp
            log_duration.h)

if(CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

# добавляем цель hello для сборки исполняемого файла
# hello.exe под Windows, hello под Linux и macOS
add_executable("chessboard" ${FILES} "main.cpp") 