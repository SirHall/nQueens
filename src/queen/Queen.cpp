#include "Queen.hpp"
#include <cstdlib>

Queen::Queen(){
    x = y = 0;
}

Queen::Queen(char xPos, char yPos){
    this->x = xPos;
    this->y = yPos;
}

Queen::~Queen(){

}

char Queen::GetX(){return x;}
char Queen::GetY(){return y;}

void Queen::SetX(char x){this->x = x;}
void Queen::SetY(char y){this->y = y;}

bool Queen::DoesCollide(char x, char y){
    char xDiff = x - this->x;
    char yDiff = y - this->y;
    return xDiff == 0 || yDiff == 0 || (std::abs(xDiff) == std::abs(yDiff));
}

bool Queen::DoesCollide(std::shared_ptr<Queen> other){
    return DoesCollide(other->x, other->y);
}

std::shared_ptr<Queen> Queen::Copy(){
    return std::shared_ptr<Queen>(new Queen(x, y));
}