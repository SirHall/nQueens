#ifndef Solver_BFS_Fast_hpp
#define Solver_BFS_Fast_hpp

#include "Solver_Base.hpp"
#include <memory>
#include "Board.hpp"
#include <chrono>
#include "SearchResults.hpp"
using namespace std::chrono;

class Solver_BFS_Fast : public Solver_Base{
    public:
        Solver_BFS_Fast();
        ~Solver_BFS_Fast();
        //NOTE: Use std::move(initBoard) to move possession  of board
        //  to this function 
        std::unique_ptr<SearchResults> Solve(
            u_char size,
            steady_clock::time_point &clock_start
            );
        std::string GetName();
};

#endif