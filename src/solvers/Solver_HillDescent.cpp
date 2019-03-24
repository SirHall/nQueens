#include "Solver_HillDescent.hpp"
#include <iostream>
#include <random>
#include <time.h>
#include "MathMore.hpp"
#include "ProgressBar.hpp"

std::unique_ptr<SearchResults> Solver_HillDescent::Solve(
    u_char size,
    steady_clock::time_point &clock_start){
    
    srand(time(NULL)); //Seed random

    //If the loop failed to find any better boards, this is how many times
    //it will try again
    u_long retries = 100;
    std::cout << "Retries: ";
    std::cin >> retries;

    u_long currentTries = 0;

    u_long boardsChecked = 0;

    auto clock_lastPrint = steady_clock::now();
    double timeLeft = 100.0;

#pragma region Setup Initial Board

    //Setup initial board
    std::cout << "Initial Board:\n";
    std::unique_ptr<Board> bestBoard (new Board(size, size));
    for(int i = 0; i < size; i++){
        u_char xPos, yPos;
        do{
            xPos = rand() % size;
            yPos = rand() % size;
        }while(bestBoard->QueenAtPos(xPos, yPos)); //Find an empty position
        bestBoard->AddQueen(xPos, yPos);
    }

    u_long lowestCost;
    bestBoard->Collisions(&lowestCost);

    std::cout << '\n';
    bestBoard->Print();

#pragma endregion

    auto frontier = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

    auto solution = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

    clock_start = steady_clock::now();

    //Search state space
    for(;;){ //Loop infinitely
        //Cost before generating children
        u_long originalLowestCost = lowestCost; 
        auto childBoards = bestBoard->GenChildBoards(false, true);
        u_long lastBoards;

        // std::cout << childBoards->size() << "\n";

        u_long currentCost;

        PrintProgress(
            clock_start, &clock_lastPrint,
            30.0, std::ref(timeLeft),
            0, boardsChecked, lastBoards,
            UINT64_MAX, 25, boardsChecked
        );

        for(u_long j = 0; j < childBoards->size(); j++){
            boardsChecked++;
            std::unique_ptr<Board> childBoard = std::move(childBoards->at(j));
            if(!childBoard->Collisions(&currentCost)){
                //This board has no collisions, return immediately
                solution->push_back(std::move(childBoard));
                return std::move(
                    std::unique_ptr<SearchResults>(
                        new SearchResults(
                            boardsChecked, j,
                            std::move(solution), 
                            GetTime(clock_start)
                        )
                    )
                );
            }

            if(currentCost < lowestCost) //Reset tries
                currentTries = 0;
            // std::cout << (currentCost <= lowestCost);

            if(
                currentCost < lowestCost //If current < lower, accept now
                ||
                ( //If current == lowest, accept at random chance
                    (currentCost == lowestCost)
                    &&
                    (rand() % 2 == 0) //Will be true 50% of the time
                )
            ){
                bestBoard = std::move(childBoard);
                lowestCost = currentCost;
            }

            childBoards->clear();
        }

        //We're stuck, can't find a better board
        if(lowestCost == originalLowestCost){
            currentTries++;
            if(currentTries >= retries){
                return std::move(
                    std::unique_ptr<SearchResults>(
                        new SearchResults(
                            boardsChecked, boardsChecked,
                            std::move(solution), 
                            GetTime(clock_start)
                        )
                    )
                );
            }
        }
    }

}

std::string Solver_HillDescent::GetName(){
    return "Hill Descent";
}