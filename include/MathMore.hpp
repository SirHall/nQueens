#ifndef MathMore_hpp
#define MathMore_hpp

#include <chrono>
using namespace std::chrono;

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax);
    
//No I will not be using recursion, too many allocations
unsigned long Factorial(unsigned long val);

unsigned long combi(int n,int k);

double GetTime(steady_clock::time_point start);

#endif