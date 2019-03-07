
cmake_minimum_required(VERSION 3.5)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unknown-pragmas -Wno-unused-parameter -Iinclude)

project(nQueen)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(EXECUTABLE_NAME "nQueen")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE nQueen_SRCS
    #[["*.hpp"]]
    "src/*.cpp"
    RELATIVE_PATH
)

add_executable(nQueen ${nQueen_SRCS})

target_include_directories(nQueen PUBLIC ${INCLUDE_DIR})
