#include "Board.hpp"
#include "Dir.hpp"
#include "MathMore.hpp"
#include "ProgressBar.hpp"
#include "Queen.hpp"
#include "SearchResults.hpp"
#include "Solver_BFS.hpp"
#include "Solver_BFS_Fast.hpp"
#include "Solver_HillDescent.hpp"
#include "Solver_Insert.hpp"
#include "Solver_SimAnnealing.hpp"
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string.h>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std::chrono;

int main(int argc, char *argv[])
{

    long size = 4;
    std::cout << "\tSize: ";
    std::cin >> size;

    // std::cout << "\n\t---CHILDREN---\n\n";

    std::cout << "\n\n";

    std::vector<std::shared_ptr<Solver_Base>> solvers(
        {std::shared_ptr<Solver_Base>(new Solver_BFS()),
         std::shared_ptr<Solver_Base>(new Solver_SimAnnealing()),
         std::shared_ptr<Solver_Base>(new Solver_HillDescent()),
         std::shared_ptr<Solver_Base>(new Solver_BFS_Fast()),
         std::shared_ptr<Solver_Base>(new Solver_Insert())});

    for (u_int i = 0; i < solvers.size(); i++)
        std::cout << "\t" << i << "\t" << solvers[i].get()->GetName() << "\n";

    u_int selection = 0;
    std::cout << "\n\tMake selection: ";
    std::cin >> selection;

    // This is kind of pointless...
    auto clock_start = steady_clock::now();
    solvers[selection]->Solve(size, clock_start)->Print();

    // Initialize a solver, solve the board, then print the results in one line
    // Solver_BFS().Solve(std::move(initBoard), clock_start)->Print();
    // Solver_SimAnnealing().Solve(std::move(initBoard), clock_start)->Print();
}
