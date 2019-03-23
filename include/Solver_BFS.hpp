#ifndef Solver_BFS_hpp
#define Solver_BFS_hpp

#include "Solver_Base.hpp"
#include <memory>
#include "Board.hpp"
#include <chrono>
#include "SearchResults.hpp"
using namespace std::chrono;

class Solver_BFS : public Solver_Base{
    public:
        Solver_BFS();
        ~Solver_BFS();
        //NOTE: Use std::move(initBoard) to move possession  of board
        //  to this function 
        std::unique_ptr<SearchResults> Solve(
            std::unique_ptr<Board> initBoard,
            steady_clock::time_point &clock_start
            );
        std::string GetName();
};

#endif