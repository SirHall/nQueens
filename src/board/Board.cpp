#include "Board.hpp"
#include <iostream>

Board::Board(u_char columns, u_char rows){
    x = columns;
    y = rows;
}

Board::Board(u_char columns, u_char rows, 
    std::vector<Queen> initQueens){
    
    x = columns;
    y = rows;
    queens = initQueens;
}

Board::~Board(){}

u_char Board::GetColumns(){return x;}
u_char Board::GetRows(){return y;}

void Board::AddQueen(u_char xPos, u_char yPos){
    queens.push_back(Queen(xPos, yPos));
}

bool Board::Collisions(Queen queen, u_char *count = NULL){
    u_char collisions = 0;
    for(u_char i = 0; i < queens.size(); i++){
        if(queens[i] == queen) //Same instance of queen
            continue;
        if(queen.DoesCollide(queens[i])){
            if(count == NULL)
                return true;
            collisions++;
        }
    }
    return collisions > 0;
}

bool Board::Collisions(u_char *count = NULL){
    u_char collisions = 0;
    for(u_char i = 0; i < queens.size(); i++){
        for(u_char j = i + 1; j < queens.size(); j++){
            if(queens[i].DoesCollide(queens[j])){
                if(count == NULL) //If the caller doesn't want a count
                    return true;
                collisions++;
            }
    }
        }
    *count = collisions;
    return collisions > 0;
}

Queen* Board::QueenAtPos(u_char checkX, u_char checkY){
    for(u_char i = 0; i < queens.size(); i++){
        if(queens[i].GetX() == checkX && queens[i].GetY() == checkY){
            return &queens[i];
        }
    }
    return NULL;
}

Board* Board::DeepCopy(){
    Board* newBoard = new Board(x, y);
    for(u_int i = 0; i < queens.size(); i++)
        newBoard->AddQueen(queens[i].GetX(), queens[i].GetY());
    return newBoard;
}

std::shared_ptr<std::vector<Board>> Board::GenChildBoards(){
    
    std::shared_ptr<std::vector<Board>>
        childBoards (new std::vector<Board>); 

    for(u_char index = 0; index < queens.size(); index++){
        Queen queen = queens[index];

        for(signed char xDiff = -1; xDiff <= 1; xDiff++){
            for(signed char yDiff = -1; yDiff <= 1; yDiff++){
                if(yDiff == 0 && xDiff == 0) 
                    continue;
                u_char 
                    checkX = queen.GetX() + xDiff,
                    checkY = queen.GetY() + yDiff; 
                if(
                    checkX < x && checkY < y && 
                    QueenAtPos(checkX, checkY) == NULL
                ){//Generate board
                    Board* newBoard = DeepCopy();
                    newBoard->MoveQueen(index, checkX, checkY);
                    childBoards->push_back(*newBoard);
                    delete newBoard;
                }
            }
        }
    }

    return childBoards;
}

void Board::MoveQueen(u_char index, u_char newX, u_char newY){
    if(index >= queens.size())
        throw std::invalid_argument("'index' falls outside of bounds");
    queens[index].SetX(newX);
    queens[index].SetY(newY);
}

#pragma region Operator Overloads

bool Board::operator==(Board *other){
    if(x == other->x && y == other->y && queens.size() == other->queens.size()){
        for(u_char i = 0; i < queens.size(); i++){
            if(queens[i] != other->queens[i])
                return false;
        }
        return true;
    }
    return false;
}

#pragma endregion

void Board::Print(){
    Queen *cQueen;

    for(u_char column = 0; column < x; column++){
        std::cout << '\t';
        for(u_char row = 0; row < y; row++){
            cQueen = QueenAtPos(column, row); 
            if(cQueen != NULL){
                if(Collisions(*cQueen))
                    std::cout << 'X'; //Queen is dead
                else
                    std::cout << 'O'; //Queen is alive
            }else{
                std::cout << 
                    (((row + column) % 2 == 0)
                        ? ' ' : '#');
            }
        }
        std::cout << '\n';
    }
}

