#include "ProgressBar.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include "MathMore.hpp"

void PrintProgress(double progress, unsigned char barLength){
    std::string bar = "";

    unsigned char completed = (unsigned char)(progress * barLength); 

    for(unsigned char i = 0; i < barLength; i++)
        bar += ((i < completed) ? '#' : '-');
    std::cout << "\r\t[" << bar << "] - " << std::round(progress * 100) << '%';
    std::cout << std::flush;
}