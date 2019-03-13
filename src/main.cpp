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
#include <unordered_set>
#include <functional>
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
        queens.push_back(Queen(0, i));

    std::shared_ptr<Board> initBoard (new Board(size, size, queens));

    std::cout << '\n';
    initBoard->Print();
    
    std::cout << "\n\t---CHILDREN---\n\n";

    u_long expectedBoards = 
        SearchSpace(size);
        // combi(size * size, size);

    //NewExplored
    auto newExplored = std::unordered_set<Board>();

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

        if(fronterChildren->size() == 0)
            break; //We didn't find any new boards

        for(auto frontierChild : *fronterChildren)
            frontier->push(frontierChild);
        fronterChildren->clear();
    }

    std::cout << "\n"; //Jump to new line from progress bar

    #pragma endregion

    //Print out answers
    std::cout << "\tUnique Boards Discovered: " << explored->size() << '\n';
    std::cout << "\n\n\t---SOLUTIONS---\n";
    std::cout << "\t " << GetTime(clock_start) << " seconds\n";
    std::cout << "\tFound " << solutions->size() << " solutions:\n\n";
    
    //Only offer to print solutions if we actually found any
    if(solutions->size() > 0){ 
        std::string answer = "";
        std::cout << "\tDisplay solutions?(y/n): ";
        std::cin >> answer;
        if(answer == "y" || answer == "Y"){
            std::cout << '\n';
            for(auto solution : *solutions){
                solution->Print();
                std::cout << '\n';
            }
        }
    }
    

}

