#include "Queen.hpp"
#include <cstdlib>

Queen::Queen() { x = y = 0; }

Queen::Queen(u_char xPos, u_char yPos)
{
    this->x = xPos;
    this->y = yPos;
}

Queen::~Queen() {}

u_char Queen::GetX() const { return x; }
u_char Queen::GetY() const { return y; }

void Queen::SetX(u_char x) { this->x = x; }
void Queen::SetY(u_char y) { this->y = y; }

bool Queen::DoesCollide(u_char x, u_char y) const
{
    // Must cast to int so we can have negative values
    int xDiff = (int)x - (int)this->x;
    int yDiff = (int)y - (int)this->y;
    return xDiff == 0 || yDiff == 0 || (xDiff == yDiff) ||
           (xDiff == -yDiff); // Faster than std::abs()
}

bool Queen::DoesCollide(Queen other) const
{
    return DoesCollide(other.x, other.y);
}

unsigned short Queen::PosSingle() const { return x | (y << 8); }

bool Queen::operator==(Queen other) const
{
    return x == other.x && y == other.y;
}

bool Queen::operator!=(Queen other) const
{
    return x != other.x || y != other.y;
}