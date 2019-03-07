#ifndef Queen_hpp
#define Queen_hpp

#include <memory>

class Queen{
    private:
        char x, y;
    public:
        Queen();
        Queen(char xPos, char yPos);
        ~Queen();
        char GetX();
        char GetY();
        void SetX(char x);
        void SetY(char y);
        bool DoesCollide(std::shared_ptr<Queen> other);
        bool DoesCollide(char x, char y);
        std::shared_ptr<Queen> Copy();
};

#endif