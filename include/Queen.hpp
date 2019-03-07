#ifndef Queen_hpp
#define Queen_hpp

#include <memory>
// #include "uu_char.h"

struct Queen{
    private:
        u_char x, y;
    public:
        Queen();
        Queen(u_char xPos, u_char yPos);
        ~Queen();
        u_char GetX();
        u_char GetY();
        void SetX(u_char x);
        void SetY(u_char y);
        bool DoesCollide(Queen other);
        bool DoesCollide(u_char x, u_char y);

        #pragma region Operator Overloads

        bool operator ==(Queen other);
        bool operator !=(Queen other);
        
        #pragma endregion
};

#endif