#include "Solver_BFS.hpp"
#include "MathMore.hpp"
#include <iostream>
#include "ProgressBar.hpp"

Solver_BFS::Solver_BFS(){

}

Solver_BFS::~Solver_BFS(){

}

std::unique_ptr<SearchResults> Solver_BFS::Solve(
    std::unique_ptr<Board> initBoard, 
    steady_clock::time_point &clock_start){
    
    int layers = -1;
    std::cout << "\t# of layers(-1=infinite): ";
    std::cin >> layers;

    u_long expectedBoards = Pow(initBoard->GetColumns());

#pragma region Storage Constructs

    auto explored = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

    auto frontier = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

    //Temporarily stores the immediate children of the frontier
    auto fronterChildren = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

    auto solutions = std::unique_ptr<std::vector<std::unique_ptr<Board>>>(
        new std::vector<std::unique_ptr<Board>>()
    );

#pragma endregion

    u_long exploredSize = 0;
    u_long lastExploredSize = 0;
    double timeLeft = 0;
    auto clock_lastPrint = steady_clock::now();

    frontier->push_back(std::move(initBoard));

#pragma region Search State Space

    for(long i = 0; i < layers || layers < 0; i++){
        while(!frontier->empty()){

            //Take node off the front
            std::unique_ptr<Board> frontierBoard = std::move(frontier->front());
            frontier->erase(frontier->begin());

            // Ensure that this is a new board
            bool alreadyExists = false;
            
            alreadyExists = Board::AlreadyExists(frontierBoard, explored);
            
            if(!alreadyExists){
                //Generate children
                auto boardChildren = frontierBoard->GenChildBoards();

                //For every childboard
                while(boardChildren->size() > 0){
                    std::unique_ptr<Board> childBoard = 
                        std::move(boardChildren->at(boardChildren->size() - 1));
                    boardChildren->erase(boardChildren->end());

                    //Make sure board is not in frontier or explored
                    if(
                    !Board::AlreadyExists(childBoard, frontier)
                    &&
                    !Board::AlreadyExists(childBoard, fronterChildren))
                        fronterChildren->push_back(std::move(childBoard));
                
                }
                // std::cout << "Before\n";
                //Push a copy to frontierBoard
                if(!frontierBoard->Collisions(NULL)) 
                    solutions->push_back(
                        std::unique_ptr<Board>(frontierBoard->DeepCopy())
                    );
                
                //Add it to the explored set
                explored->push_back(std::move(frontierBoard));
                exploredSize++;
                
                // std::cout << "After\n";
            }
            PrintProgress(
                clock_start, &clock_lastPrint,
                30.0, timeLeft, solutions->size(), 
                exploredSize, lastExploredSize,
                // explored->size(),// + frontier->size() + fronterChildren->size(),
                expectedBoards, 25, i
                ); 
            
        }

        if(fronterChildren->size() == 0)
            break; //We didn't find any new boards

        while(fronterChildren->size() > 0){
            //Move from frontierChildren to frontier
            frontier->push_back(
                std::move(
                    fronterChildren->at(fronterChildren->size() - 1)
                )
            );
            fronterChildren->erase(fronterChildren->end());
        }
        fronterChildren->clear(); //Just to make sure I guess
    }
#pragma endregion

    std::cout << "\n\n";
    return std::move(
        std::unique_ptr<SearchResults>(
            new SearchResults(
                explored->size(), 
                expectedBoards, 
                std::move(solutions), 
                GetTime(clock_start)
            )
        )
    );
}

std::string Solver_BFS::GetName(){
    return "Row-Only Breadth First Search";
}