#include "MathMore.hpp"

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax){

    return ((value - inMin) / (outMin - inMin) * (outMax - inMax) + inMax);
}

unsigned long Factorial(unsigned long val){
    unsigned long fact = val;
    for(unsigned long i = val - 1; i > 1; i--)
        fact *= i;
    return fact;
}