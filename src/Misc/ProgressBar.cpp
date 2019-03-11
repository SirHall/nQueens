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

    if(GetTime(*clock_lastPrint) > (1 / printRate)){ 
        *clock_lastPrint = steady_clock::now();
        // if(layers > 0)
        PrintBar((double)currentBoards / targetBoards, barLength);
        // else
            // std::cout << "\r    ";
        std::cout << " - "
            <<  "(depth=" << currentDepth + 1 << ") "
            << solutions << '/' << currentBoards 
            << "    " << std::fixed << std::setprecision(2) 
            << std::round(GetTime(clock_start) * 100) / 100
            << "    "
            << std::flush;
        return true; //Return true as we have printed
    }
    return false; //We did not print
}