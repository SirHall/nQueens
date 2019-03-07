#include <iostream>
#include <memory>
#include "Queen.hpp"
#include "Board.hpp"
#include "Dir.hpp"

int main(int argc, char* argv[]){
    std::shared_ptr<Board> initBoard (new Board(4, 4, 
        {
            Queen(3, 1),
            Queen(1, 1),
            Queen(2, 1),
            Queen(0, 0)
        }));

    initBoard->Print();
    
    std::cout << "\n\t---CHILDREN---\n\n";

    auto boards = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    auto solutions = std::shared_ptr<std::vector<std::shared_ptr<Board>>>(
        new std::vector<std::shared_ptr<Board>>()
    );

    boards->push_back(initBoard);

    for(int i = 0; i < 150; i++){
        std::shared_ptr<std::vector<std::shared_ptr<Board>>> children
            (new std::vector<std::shared_ptr<Board>>());
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
                if(!childBoard->Collisions(NULL))
                    solutions->push_back(childBoard);
            }
        }
    }
    std::cout << "Size: " << boards->size() << '\n';
    boards->at(boards->size() - 1)->Print();
    std::cout << "\n\n\t---SOLUTIONS---\n";
    std::cout << "\tFound " << solutions->size() << " solutions:\n\n";
    for(auto solution : *solutions){
        solution->Print();
        std::cout << '\n';
    }

}