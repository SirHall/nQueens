#include <iostream>
#include <memory>
#include "Queen.hpp"
#include "Board.hpp"

int main(int argc, char* argv[]){
    std::unique_ptr<Board> board (new Board(4, 4, 
        {
            Queen(3, 1),
            Queen(1, 1),
            Queen(2, 1),
            Queen(3, 3)
        }));
    
    auto children = board->GenChildBoards();
    
    std::cout << children->size() << '\n';

    board->Print();

    for(u_int32_t i = 0; i < children->size(); i++){
        children->at(i).Print();
        std::cout << '\n';
    }
}