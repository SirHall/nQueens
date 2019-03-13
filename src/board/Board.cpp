#include "Board.hpp"
#include <iostream>
#include <algorithm>

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
    if(count != NULL)
        *count = collisions / 2;
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
    if(count != NULL)
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

std::shared_ptr<std::vector<std::shared_ptr<Board>>> Board::GenChildBoards(){
    
    std::shared_ptr<std::vector<std::shared_ptr<Board>>>
        childBoards (new std::vector<std::shared_ptr<Board>>); 
    
    for(u_char index = 0; index < queens.size(); index++){ //All queens
        Queen queen = queens[index];
    
        for(signed char xDiff = 1; xDiff <= 1; xDiff++){ //All x moves
            // for(signed char yDiff = -1; yDiff <= 1; yDiff++){ //All y moves
                if(/*yDiff == 0 && */xDiff == 0)
                    continue;
                u_char 
                    checkX = queen.GetX() + xDiff;//,
                    // checkY = queen.GetY() + yDiff; 
                if(
                    checkX < x && /*checkY < y &&*/ 
                    QueenAtPos(checkX, queen.GetY()) == NULL
                ){//Generate board
                    auto newBoard = std::shared_ptr<Board>(DeepCopy());
                    newBoard->MoveQueen(index, checkX, queen.GetY());
                    childBoards->push_back(newBoard);
                }
            // }
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

void Board::MoveQueen(u_char index, Dir direction){
    if(index >= queens.size())
        throw std::invalid_argument("'index' falls outside of bounds");
    signed char xRel = 0, yRel = 0;

    switch (direction)
    {
        case Dir::Up:           xRel =  0;  yRel = -1; break;
        case Dir::Down:         xRel =  0;  yRel =  1; break;
        case Dir::Right:        xRel =  1;  yRel =  0; break;
        case Dir::Left:         xRel = -1;  yRel =  0; break;
        case Dir::Up_Right:     xRel =  1;  yRel =  -1; break;
        case Dir::Up_Left:      xRel =  -1; yRel = -1; break;
        case Dir::Down_Right:   xRel =  1;  yRel =  1; break;
        case Dir::Down_Left:    xRel =  -1; yRel =  1; break;
    }

    //Making sure that the queen stays in bounds
    if  (
            !(xRel == 1 && queens[index].GetX() >= x - 1) && 
            !(xRel == -1 && queens[index].GetX() == 0)
        )
        queens[index].SetX(queens[index].GetX() + xRel);
        
    if  (
            !(yRel == 1 && queens[index].GetY() >= y - 1) && 
            !(yRel == -1 && queens[index].GetY() == 0)
        )
        queens[index].SetY(queens[index].GetY() + yRel);

}

#pragma region Operator Overloads

bool Board::operator==(Board other){
    //Check our dimensions, and queen count are equal
    if(x == other.x && y == other.y && queens.size() == other.queens.size()){
        for(u_char i = 0; i < queens.size(); i++){
            //Queens have different positions
            if(other.QueenAtPos(queens[i].GetX(), queens[i].GetY()) == NULL) 
                return false;
        }
        return true; //Everything is the same
    }
    return false;
}

#pragma endregion

void Board::Print(){
    Print('\n', '\t', 'O', 'X', ' ', '#');
}

u_char Board::QueenSize() const{
    return queens.size();
}

size_t Board::QueenHash(u_char index) const{
    return queens[index].PosSingle();
}

void Board::Print(
            char sep = '\n', char indent = '\t', 
            char aliveQueen = 'O', char deadQueen = 'X', 
            char whiteSquare = ' ', char blackSquare = '#'){
    Queen *cQueen;
    
    for(u_char row = 0; row < y; row++){
        std::cout << indent;
        // for(u_char row = y - 1; row >= 0; row--){
        for(u_char column = 0; column < x; column++){
            cQueen = QueenAtPos(column, row); 
            if(cQueen != NULL){
                if(Collisions(*cQueen))
                    std::cout << deadQueen; //Queen is dead
                else
                    std::cout << aliveQueen; //Queen is alive
            }else{
                std::cout << 
                    (((row + column) % 2 == 0)
                        ? whiteSquare : blackSquare);
            }
        }
        std::cout << sep;
    }
}

