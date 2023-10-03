cmake_minimum_required(VERSION 3.24)
project(chessboard C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c board.c board.h move.c move.h main.c)
