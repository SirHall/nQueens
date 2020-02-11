#include "SearchResults.hpp"

#include "MathMore.hpp"
#include <iostream>

SearchResults::SearchResults()
{
    this->solutions = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>());
    this->timeTaken    = 0;
    this->uniqueBoards = 0;
}

SearchResults::SearchResults(
    u_long uniqueBoards, u_long expectedBoards,
    std::unique_ptr<std::vector<std::unique_ptr<Board>>> solutions,
    double                                               timeTaken)
{

    this->expectedBoards = expectedBoards;
    this->uniqueBoards   = uniqueBoards;
    this->solutions      = std::move(solutions);
    this->timeTaken      = timeTaken;
}

SearchResults::~SearchResults() {}

void SearchResults::Print()
{
    // Print out answers
    std::cout << "\tUnique Boards Discovered: " << uniqueBoards << '/'
              << expectedBoards << '\n';
    std::cout << "\n\n\t---SOLUTIONS---\n";
    std::cout << "\t " << timeTaken << " seconds\n";
    std::cout << "\tFound " << solutions->size() << " solutions:\n\n";

    // Only offer to print solutions if we actually found any
    if (solutions->size() > 0)
    {
        std::string answer = "";
        std::cout << "\tDisplay solutions?(y/n): ";
        std::cin >> answer;
        if (answer == "y" || answer == "Y")
        {
            std::cout << '\n';
            for (u_long i = 0; i < solutions->size(); i++)
            {
                solutions->at(i)->Print();
                std::cout << '\n';
            }
        }
    }
}

u_long SearchResults::Solutions() { return solutions->size(); }