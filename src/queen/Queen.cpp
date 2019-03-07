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
    u_char xDiff = x - this->x;
    u_char yDiff = y - this->y;
    return xDiff == 0 || yDiff == 0 || (std::abs(xDiff) == std::abs(yDiff));
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