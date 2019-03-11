#include <iostream>
#include <memory>
#include "Queen.hpp"
#include "Board.hpp"
#include "Dir.hpp"
#include "ProgressBar.hpp"
#include "MathMore.hpp"
#include <string>
#include <chrono>
#include <sstream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std::chrono;


int main(int argc, char* argv[]){

    long size = 4;
    std::cout << "\tSize: ";
    std::cin >> size;

    int layers = 50;
    std::cout << "\t# of layers(-1=infinite): ";
    std::cin >> layers;

    std::vector<Queen> queens = std::vector<Queen>();

    for(int i = 0; i < size; i++)
        queens.push_back(Queen(i, i));

    std::shared_ptr<Board> initBoard (new Board(size, size, queens));

    std::cout << '\n';
    initBoard->Print();
    
    std::cout << "\n\t---CHILDREN---\n\n";

    u_long expectedBoards = 
        combi(size * size, size);

    //Explored
    auto explored = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    auto frontier = std::shared_ptr<std::queue<std::shared_ptr<Board>>>(
        new std::queue<std::shared_ptr<Board>>()
    );

    //Temporarily stores the immediate children of the frontier
    auto fronterChildren = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    auto solutions = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );


    u_int previousSize = 0;
    frontier->push(initBoard);

    auto clock_start = steady_clock::now();
    auto clock_lastPrint = steady_clock::now();

    #pragma region Search Space

    for(long i = 0; i < layers || layers < 0; i++){
        while(!frontier->empty()){
            std::shared_ptr<Board> frontierBoard = frontier->front();
            frontier->pop();
            
            //Ensure that this is a new board
            bool alreadyExists = false;
            for(auto exploredBoard : *explored){ //Only add new boards
                if(*frontierBoard == *exploredBoard){
                    alreadyExists = true;
                    break;
                }
            }
            if(!alreadyExists){
                //Generate children
                auto boardChildren = frontierBoard->GenChildBoards();
                for(auto childBoard : *boardChildren)
                    fronterChildren->push_back(childBoard);

                //Add it to the explored set
                explored->push_back(frontierBoard);
                if(!frontierBoard->Collisions(NULL))
                    solutions->push_back(frontierBoard);
            }

            PrintProgress(
                clock_start, &clock_lastPrint,
                30.0, solutions->size(), 
                explored->size(),// + frontier->size() + fronterChildren->size(),
                expectedBoards, 25, i
            );

        }

        // u_long 
        //     exploredSize = explored->size(),
        //     frontierSize = frontier->size(),
        //     frontierChildrenSize = fronterChildren->size();

        // int b = 1;

        if(fronterChildren->size() == 0)
            break; //We didn't find any new boards

        for(auto frontierChild : *fronterChildren)
            frontier->push(frontierChild);
        fronterChildren->clear();

        // exploredSize = explored->size();
        // frontierSize = frontier->size();
        // frontierChildrenSize = fronterChildren->size();

        // int a = 1;
   
    }

    std::cout << "\n"; //Jump to new line from progress bar

    #pragma endregion

    std::cout << "\tUnique Boards Discovered: " << explored->size() << '\n';
    std::cout << "\n\n\t---SOLUTIONS---\n";
    std::cout << "\t " << GetTime(clock_start) << " seconds\n";
    std::cout << "\tFound " << solutions->size() << " solutions:\n\n";
    
    if(solutions->size() > 0){
        std::string answer = "";
        std::cout << "\tDisplay solutions?(y/n): ";
        std::cin >> answer;
        if(answer == "y"){
            std::cout << '\n';
            for(auto solution : *solutions){
                solution->Print();
                std::cout << '\n';
            }
        }
    }
    

}

