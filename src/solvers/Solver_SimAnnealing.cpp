#include "Dir.hpp"
#include "MathMore.hpp"
#include "ProgressBar.hpp"
#include "SearchResults.hpp"
#include "Solver_SimAnnealing.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <math.h> //Two math includes...
#include <random>
#include <time.h>
using namespace std::chrono;

Solver_SimAnnealing::Solver_SimAnnealing() {}

Solver_SimAnnealing::~Solver_SimAnnealing() {}

std::unique_ptr<SearchResults>
    Solver_SimAnnealing::Solve(u_char                    size,
                               steady_clock::time_point &clock_start)
{

#pragma region Setup Initial Board

    // Setup initial board
    std::cout << "Initial Board:\n";
    std::vector<Queen> queens = std::vector<Queen>();
    for (int i = 0; i < size; i++)
        queens.push_back(Queen(i, i)); // Place queens diagonally
    std::unique_ptr<Board> initBoard(new Board(size, size, queens));

    std::cout << '\n';
    initBoard->Print();

#pragma endregion

    std::srand(std::time(NULL));

    u_long maxIterations = 1000;
    std::cout << "\tIterations: ";
    std::cin >> maxIterations;

    double initTemp = 1000000;
    std::cout << "\tInitial Temperature: ";
    std::cin >> initTemp;

    double targetTemp = 0.001;
    std::cout << "\tTarget Temperature: ";
    std::cin >> targetTemp;

    double coolingRate = FindCoolingVal(maxIterations, initTemp, targetTemp);

    std::unique_ptr<Board> bestBoard = std::move(initBoard),
                           currentBoard =
                               std::unique_ptr<Board>(bestBoard->DeepCopy());

    u_long boardsChecked = 0, lastBoards = 0;

    u_int currentCost;

    double temp = initTemp;

    auto   clock_lastPrint = steady_clock::now();
    double timeLeft        = 100.0;

    std::unique_ptr<std::vector<std::unique_ptr<Board>>> solution(
        new std::vector<std::unique_ptr<Board>>);

    clock_start = steady_clock::now();

    for (u_long i = 0; i < maxIterations; i++)
    {

        PrintProgress(clock_start, &clock_lastPrint, 15.0, timeLeft, 0,
                      boardsChecked, lastBoards, maxIterations, 25, i);

        auto newBoard = std::unique_ptr<Board>(currentBoard->DeepCopy());
        MoveRandomQueenRandomly(newBoard);
        boardsChecked++;

        u_long newCost = UINT64_MAX;

        // Test for number of collisions, and see if there are any
        if (!newBoard->Collisions(&newCost))
        {
            // New board has no collisions, return it
            solution->push_back(std::move(newBoard));
            return std::unique_ptr<SearchResults>(
                new SearchResults(boardsChecked, maxIterations,
                                  std::move(solution), GetTime(clock_start)));
        }

        if (newCost < currentCost || RandAccept(currentCost, newCost, temp))
        {
            currentBoard = std::move(newBoard);
            currentCost  = newCost;
        }

        temp *= 1.0 - coolingRate;
    }

    std::cout << '\n';

    return std::move(std::unique_ptr<SearchResults>(
        new SearchResults(boardsChecked, maxIterations, std::move(solution),
                          GetTime(clock_start))));
}

void Solver_SimAnnealing::MoveRandomQueenRandomly(std::unique_ptr<Board> &board)
{

    u_char queenIndex;
    Queen  queen;
    int    randX, randY;

    do
    {
        // It's possible to place a queen where it can no longer be moved,
        // therefore we must also reselect a queen
        queenIndex = rand() % board->QueenSize();
        queen      = board->GetQueen(queenIndex);
        randX = queen.GetX() + (rand() % 3 - 1); // Rand from -1 to 1
        randY = queen.GetY() + (rand() % 3 - 1);
    } while (!board->IsWithinBoard(randX, randY) || // New pos is inside board
             board->QueenAtPos(randX, randY));      // It's not on another queen

    board->MoveQueen(queenIndex, randX, randY); // Pick random direction
}

double Solver_SimAnnealing::FindCoolingVal(u_long iterations, double initTemp,
                                           double targetTemp)
{
    // Can see my proof for this here:
    //  https://www.desmos.com/calculator/cwzfjjl8z2
    return -(std::pow(targetTemp / initTemp, 1.0 / iterations)) + 1;
}

bool Solver_SimAnnealing::RandAccept(u_int currentCost, u_int newCost,
                                     double temp)
{

    if (newCost < currentCost)
        return true;
    return std::exp((currentCost - newCost) / temp) >
           (rand() / (RAND_MAX + 1.0)); // Number from 0 to 1
}

std::string Solver_SimAnnealing::GetName() { return "Simulated Annealing"; }