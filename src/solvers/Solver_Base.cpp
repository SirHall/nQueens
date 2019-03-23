#include "Solver_Base.hpp"

Solver_Base::Solver_Base(){}

// Solver_Base::~Solver_Base(){}

std::unique_ptr<SearchResults> Solver_Base::Solve(
    std::unique_ptr<Board> initBoard,
    steady_clock::time_point &clock_start
){
    return std::unique_ptr<SearchResults>(new SearchResults());
}