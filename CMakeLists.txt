cmake_minimum_required(VERSION 3.17)

project(Sudoku
        VERSION 1
        DESCRIPTION "a tiny text-graphics sudoku game"
        LANGUAGES C)

configure_file(f1.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_executable(67 67.c)
