#include <iostream>
#include <memory>
#include "Queen.hpp"
#include "Board.hpp"

int main(int argc, char* argv[]){
    std::unique_ptr<Board> board (new Board(4, 4, 
        {
            std::shared_ptr<Queen>(new Queen(3, 1)),
            std::shared_ptr<Queen>(new Queen(1, 1)),
            std::shared_ptr<Queen>(new Queen(2, 1)),
            std::shared_ptr<Queen>(new Queen(1, 4))
        }));
    
    // std::cout << "Before print\n";

    board->Print();
}