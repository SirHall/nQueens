#include "Board.hpp"
#include <iostream>

Board::Board(char columns, char rows){
    x = columns;
    y = rows;
}

Board::Board(char columns, char rows, 
    std::vector<std::shared_ptr<Queen>> initQueens){
    
    x = columns;
    y = rows;
    queens = initQueens;
}

Board::~Board(){}

char Board::GetColumns(){return x;}
char Board::GetRows(){return y;}

void Board::AddQueen(char xPos, char yPos){
    queens.push_back(std::shared_ptr<Queen>(new Queen(xPos, yPos)));
}

bool Board::Collisions(std::shared_ptr<Queen> queen, char *count = NULL){
    char collisions = 0;
    for(unsigned char i = 0; i < queens.size(); i++){
        if(queens[i].get() == queen.get()) //Same instance of queen
            continue;
        if(queen->DoesCollide(queens[i])){
            if(count == NULL)
                return true;
            collisions++;
        }
    }
    return collisions > 0;
}

bool Board::Collisions(char *count = NULL){
    char collisions = 0;
    for(unsigned char i = 0; i < queens.size(); i++){
        for(unsigned char j = i + 1; j < queens.size(); j++){
            if(queens[i]->DoesCollide(queens[j])){
                if(count == NULL) //If the caller doesn't want a count
                    return true;
                collisions++;
            }
        }
    }
    *count = collisions;
    return collisions > 0;
}

std::shared_ptr<Queen> Board::QueenAtPos(char x, char y){
    for(char i = 0; i < queens.size(); i++){
        if(queens[i]->GetX() == x && queens[i]->GetY() == y){
            return queens[i];
        }
    }
    return std::shared_ptr<Queen>(NULL);
}

std::vector<std::unique_ptr<Board>> Board::GenChildBoards(){

}

void Board::Print(){
    std::shared_ptr<Queen> cQueen;

    for(char column = 1; column <= x; column++){
        std::cout << '\t';
        for(char row = 1; row <= y; row++){
            cQueen = QueenAtPos(column, row); 
            if(cQueen.get() != NULL){
                if(Collisions(cQueen))
                    std::cout << 'X'; //Queen is dead
                else
                    std::cout << 'O'; //Queen is alive
            }else{
                std::cout << 
                    ((row + column) % 2 == 0)
                        ? ' ' : (char)219;
            }
        }
        std::cout << '\n';
    }
}

