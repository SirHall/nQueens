#include "SearchResults.hpp"
#include "ProgressBar.hpp"
#include "Solver_BFS.hpp"
#include "Solver_SimAnnealing.hpp"
#include <unordered_set>
#include "MathMore.hpp"
#include <functional>
#include "Queen.hpp"
#include "Board.hpp"
#include <string.h>
#include <iostream>
#include <sstream>
#include "Dir.hpp"
#include <memory>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std::chrono;

int main(int argc, char* argv[]){

    long size = 4;
    std::cout << "\tSize: ";
    std::cin >> size;

    //Setup initial board
    std::vector<Queen> queens = std::vector<Queen>();
    for(int i = 0; i < size; i++)
        queens.push_back(Queen(0, i));
    std::unique_ptr<Board> initBoard (new Board(size, size, queens));

    std::cout << '\n';
    initBoard->Print();

    // std::cout << "\n\t---CHILDREN---\n\n";

    std::cout << "\n\n";
    
    std::vector<std::shared_ptr<Solver_Base>> solvers({
        std::shared_ptr<Solver_Base>(new Solver_BFS()),
        std::shared_ptr<Solver_Base>(new Solver_SimAnnealing())
    });

    for(u_int i = 0; i < solvers.size(); i++)
        std::cout << "\t" << i << "\t" << solvers[i].get()->GetName() << "\n";

    u_int selection = 0;
    std::cout << "\n\tMake selection: ";
    std::cin >> selection;


    auto clock_start = steady_clock::now();
    solvers[selection]->Solve(std::move(initBoard), clock_start)->Print();

    //Initialize a solver, solve the board, then print the results in one line
    // Solver_BFS().Solve(std::move(initBoard), clock_start)->Print();
    // Solver_SimAnnealing().Solve(std::move(initBoard), clock_start)->Print();
}

