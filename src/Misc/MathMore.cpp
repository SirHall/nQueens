#include "MathMore.hpp"
#include <chrono>
using namespace std::chrono;

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

//nCr, taken from: https://stackoverflow.com/a/11809562
unsigned long combi(int n,int k)
{
    long ans=1;
    k=k>n-k?n-k:k;
    int j=1;
    for(;j<=k;j++,n--)
    {
        if(n%j==0)
        {
            ans*=n/j;
        }else
        if(ans%j==0)
        {
            ans=ans/j*n;
        }else
        {
            ans=(ans*n)/j;
        }
    }
    return ans;
}

double GetTime(steady_clock::time_point start){
    auto now = steady_clock::now();
    steady_clock::duration duration = now - start;
    return double(duration.count()) * 
        steady_clock::period::num / steady_clock::period::den;
}
