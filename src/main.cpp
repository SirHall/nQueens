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
using namespace std::chrono;

double GetTime(steady_clock::time_point start){
    auto now = steady_clock::now();
    steady_clock::duration duration = now - start;
    return double(duration.count()) * 
        steady_clock::period::num / steady_clock::period::den;
}

int main(int argc, char* argv[]){

    long size = 4;
    std::cout << "\tSize: ";
    std::cin >> size;

    int layers = 50;
    std::cout << "\t# of layers(-1=infinite): ";
    std::cin >> layers;

    std::vector<Queen> queens = std::vector<Queen>();

    for(int i = 0; i < size; i++)
        queens.push_back(Queen(i, 0));

    std::shared_ptr<Board> initBoard (new Board(size, size, queens));

    std::cout << '\n';
    initBoard->Print();
    
    std::cout << "\n\t---CHILDREN---\n\n";

    auto boards = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    auto solutions = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    u_int previousSize = 0;
    boards->push_back(initBoard);

    auto clock_start = steady_clock::now();
    auto clock_lastPrint = steady_clock::now();

    #pragma region Search Space

    for(long i = 0; i < layers || layers < 0; i++){

        std::shared_ptr<std::vector<std::shared_ptr<Board>>> children
            (new std::vector<std::shared_ptr<Board>>());
        
        for(auto board : *boards){ //For all found boards
            auto tmpChildren = board->GenChildBoards(); //Generate its children
            for(auto childBoard : *tmpChildren)
                children->push_back(childBoard);
        }

        for(auto childBoard : *children){ //Ensure it's a valid board

        #pragma region Printing

        if(GetTime(clock_lastPrint) > (1/11.0)){ //Update the display at 30fps
            clock_lastPrint = steady_clock::now();
            if(layers > 0)
                PrintProgress((double)i / (layers - 1), 50);
            else
                std::cout << "\r    ";
            std::cout << " - "
                <<  "(n=" << i + 1 << ") "
                << solutions->size() << '/' << boards->size() 
                << "    " << std::round(GetTime(clock_start) * 100) / 100
                << "    "
                << std::flush;
        }

        #pragma endregion

            bool alreadyExists = false;
            for(auto board : *boards) //This board already exists
                if(*childBoard == board.get()){
                    alreadyExists = true;
                    break;}
            if(!alreadyExists){ //If this is a unique board
                boards->push_back(childBoard); //Push to main boards
                if(boards->size() == boards->capacity()) //If full...
                    boards->reserve(boards->capacity() * 2); //double capacity
                if(!childBoard->Collisions(NULL)) //If board has no collisions
                    solutions->push_back(childBoard); //Then add to solutions
            }
        }
        if(previousSize == boards->size())//We have scanned all possiblities
            break; //Stop searching
        previousSize = boards->size(); //How many boards we found this iteration 
    }
    std::cout << "\n"; //Jump to new line from progress bar

    #pragma endregion

    std::cout << "\tBoards Discovered: " << boards->size() << '\n';
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