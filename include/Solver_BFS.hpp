#ifndef Solver_BFS_hpp
#define Solver_BFS_hpp

#include "Board.hpp"
#include "SearchResults.hpp"
#include "Solver_Base.hpp"
#include <chrono>
#include <memory>
using namespace std::chrono;

class Solver_BFS : public Solver_Base
{
public:
    Solver_BFS();
    ~Solver_BFS();
    // NOTE: Use std::move(initBoard) to move possession  of board
    //  to this function
    std::unique_ptr<SearchResults> Solve(u_char                    size,
                                         steady_clock::time_point &clock_start);
    std::string                    GetName();
};

#endif