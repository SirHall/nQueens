#pragma once
#ifndef SOLVERS_SOLVER_INSERT_HPP
#define SOLVERS_SOLVER_INSERT_HPP

#include "Board.hpp"
#include "SearchResults.hpp"
#include "Solver_Base.hpp"
#include <chrono>
#include <memory>
using namespace std::chrono;

class Solver_Insert : public Solver_Base
{
private:
protected:
public:
    Solver_Insert()  = default;
    ~Solver_Insert() = default;

    std::unique_ptr<SearchResults> Solve(u_char                    size,
                                         steady_clock::time_point &clock_start);
    std::string                    GetName();
};

#endif
