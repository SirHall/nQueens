#include "MathMore.hpp"
#include "ProgressBar.hpp"
#include "Solver_Insert.hpp"
#include <iostream>

static void
    SolveRec(Board &                                               board,
             std::unique_ptr<std::vector<std::unique_ptr<Board>>> &solutions,
             u_char                                                x_index)
{
    if (x_index >= board.GetColumns())
        return;

    for (std::size_t y = 0; y < board.GetRows(); y++)
    {
        u_char queenIndex = board.AddQueen(x_index, y);
        // We found a solution!
        if ((x_index == board.GetColumns() - 1) && (!board.Collisions(nullptr)))
            solutions->push_back(std::unique_ptr<Board>(board.DeepCopy()));
        else
            SolveRec(board, solutions, x_index + 1);
        board.RemoveQueen(queenIndex);
    }
}

std::unique_ptr<SearchResults>
    Solver_Insert::Solve(u_char size, steady_clock::time_point &clock_start)
{
    auto board     = std::make_unique<Board>(size, size);
    auto solutions = std::make_unique<std::vector<std::unique_ptr<Board>>>();

    clock_start = steady_clock::now();

    SolveRec(*board, solutions, 0);

    return std::move(std::unique_ptr<SearchResults>(
        new SearchResults(1, 1, std::move(solutions), GetTime(clock_start))));
}

std::string Solver_Insert::GetName() { return "Insert"; }