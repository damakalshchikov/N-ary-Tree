cmake_minimum_required(VERSION 3.30)
project(N_aryTree)

set(CMAKE_CXX_STANDARD 20)

add_executable(N_aryTree "Source Files/main.cpp"
        "Header Files/Node.h"
        "Source Files/Node.cpp"
        "Header Files/FileReader.h"
        "Source Files/FileReader.cpp"
        "Header Files/FileGenerator.h"
        "Source Files/FileGenerator.cpp"
        "Header Files/FinderLongestOddPath.h"
        "Source Files/FinderLongestOddPath.cpp")
