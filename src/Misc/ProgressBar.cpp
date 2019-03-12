#include "ProgressBar.hpp"

#include "MathMore.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

void PrintBar(double progress, unsigned char barLength){
    std::string bar = "";

    unsigned char completed = (unsigned char)(progress * barLength); 

    for(unsigned char i = 0; i < barLength; i++)
        bar += ((i < completed) ? '#' : '-');
    std::cout << "\r\t[" << bar << "] - " << std::round(progress * 100) << '%';
    std::cout << std::flush;
}


bool PrintProgress(
    steady_clock::time_point clock_start, 
    steady_clock::time_point *clock_lastPrint,
    double printRate,
    u_long solutions, u_long currentBoards, u_long targetBoards,
    u_char barLength, u_long currentDepth){

    auto now = steady_clock::now();

    if(GetTime(*clock_lastPrint, now) > (1 / printRate)){ 
        *clock_lastPrint = now;
        PrintBar((double)currentBoards / targetBoards, barLength);
        std::cout << " - "
            <<  "(depth=" << currentDepth + 1 << ") "
            << solutions << '/' << currentBoards << '/' << targetBoards
            << "    " << std::fixed << std::setprecision(2) 
            << std::round(GetTime(clock_start, now) * 100) / 100
            << "    "
            << std::flush;
        return true; //Return true as we have printed
    }
    return false; //We did not print
}