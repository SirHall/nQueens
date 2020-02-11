#ifndef Queen_hpp
#define Queen_hpp

#include <memory>
// #include "uu_char.h"

struct Queen
{
private:
    u_char x, y;

public:
    Queen();
    Queen(u_char xPos, u_char yPos);
    ~Queen();
    u_char GetX() const;
    u_char GetY() const;
    void   SetX(u_char x);
    void   SetY(u_char y);
    bool   DoesCollide(Queen other) const;
    bool   DoesCollide(u_char x, u_char y) const;

    unsigned short PosSingle() const;

#pragma region Operator Overloads

    bool operator==(Queen other) const;
    bool operator!=(Queen other) const;

#pragma endregion
};

#endif