#include "Queen.hpp"
#include <cstdlib>

Queen::Queen(){
    x = y = 0;
}

Queen::Queen(u_char xPos, u_char yPos){
    this->x = xPos;
    this->y = yPos;
}

Queen::~Queen(){

}

u_char Queen::GetX(){return x;}
u_char Queen::GetY(){return y;}

void Queen::SetX(u_char x){this->x = x;}
void Queen::SetY(u_char y){this->y = y;}

bool Queen::DoesCollide(u_char x, u_char y){
    //Must cast to int so we can have negative values
    int xDiff = (int)x - (int)this->x;
    int yDiff = (int)y - (int)this->y;
    return xDiff == 0 || yDiff == 0 || 
        (xDiff == yDiff) || (xDiff == -yDiff); //Faster than std::abs()
}

bool Queen::DoesCollide(Queen other){
    return DoesCollide(other.x, other.y);
}

bool Queen::operator==(Queen other){
    return x == other.x && y == other.y;
}

bool Queen::operator!=(Queen other){
    return x != other.x || y != other.y;
}