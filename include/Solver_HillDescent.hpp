#ifndef Solver_HillDescent_hpp
#define Solver_HillDescent_hpp

#include "Solver_Base.hpp"

class Solver_HillDescent : public Solver_Base
{
public:
    Solver_HillDescent()  = default;
    ~Solver_HillDescent() = default;
    std::unique_ptr<SearchResults> Solve(u_char                    size,
                                         steady_clock::time_point &clock_start);
    std::string                    GetName();
};

#endif