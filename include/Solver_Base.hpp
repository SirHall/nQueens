#ifndef Solver_Base_hpp
#define Solver_Base_hpp

#include "SearchResults.hpp"

#include <memory>
#include "Board.hpp"
#include <chrono>
#include <string>

using namespace std::chrono;

class Solver_Base{
    public:
        Solver_Base();
        virtual ~Solver_Base() = default;
        virtual std::unique_ptr<SearchResults> Solve(
            u_char size,
            steady_clock::time_point &clock_start
        );
        virtual std::string GetName();
};

#endif