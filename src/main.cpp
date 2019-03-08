#include <iostream>
#include <memory>
#include "Queen.hpp"
#include "Board.hpp"
#include "Dir.hpp"
#include "ProgressBar.hpp"
#include "MathMore.hpp"
#include <string>

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


    for(long i = 0; i < layers || layers < 0; i++){
        std::shared_ptr<std::vector<std::shared_ptr<Board>>> children
            (new std::vector<std::shared_ptr<Board>>());
            if(layers > 0)
                PrintProgress((double)i / (layers - 1), 50);
            else
                std::cout << "\r\t";
            std::cout << " - " << solutions->size() << '/' << boards->size() 
                << std::flush;
        for(auto board : *boards)
            children = board->GenChildBoards();
        for(auto childBoard : *children){
            bool alreadyExists = false;
            for(auto board : *boards)
                if(*childBoard == board.get()){
                    alreadyExists = true;
                    break;}
            if(!alreadyExists){
                boards->push_back(childBoard);
                if(boards->size() == boards->capacity())
                    boards->reserve(boards->capacity() * 2);
                if(!childBoard->Collisions(NULL))
                    solutions->push_back(childBoard);
            }
        }
        if(previousSize == boards->size())//We have scanned all possiblities
            break;
        previousSize = boards->size();
    }
    std::cout << "\r\n";

    std::cout << "\tBoards Discovered: " << boards->size() << '\n';
    std::cout << "\n\n\t---SOLUTIONS---\n";
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