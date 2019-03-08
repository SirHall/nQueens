#include "MathMore.hpp"

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax){

    return ((value - inMin) / (outMin - inMin) * (outMax - inMax) + inMax);
}