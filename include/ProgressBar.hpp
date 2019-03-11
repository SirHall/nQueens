#ifndef ProgressBar_hpp
#define ProgressBar_hpp

#include <chrono>
#include <cmath>
using namespace std::chrono;

void PrintBar(double progress, unsigned char barLength);

bool PrintProgress(
    steady_clock::time_point clock_start,
    steady_clock::time_point* clock_lastPrint,
    double printRate,
    u_long solutions, u_long currentBoards, u_long targetBoards,
    u_char barLength, u_long currentDepth);

#endif