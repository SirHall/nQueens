#ifndef MathMore_hpp
#define MathMore_hpp

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax);
    
//No I will not be using recursion, too many allocations
unsigned long Factorial(unsigned long val);

#endif