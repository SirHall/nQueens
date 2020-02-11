#include "Solver_Base.hpp"

Solver_Base::Solver_Base() {}

// Solver_Base::~Solver_Base(){}

std::unique_ptr<SearchResults>
    Solver_Base::Solve(u_char size, steady_clock::time_point &clock_start)
{
    return std::unique_ptr<SearchResults>(new SearchResults());
}

std::string Solver_Base::GetName() { return "Base Solver (Does nothing)"; }