#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <memory>
#include "Queen.hpp"

class Board{
    private:
        //The size of the board
        u_char x, y;
        std::vector<Queen> queens;

    public:
        Board(u_char columns, u_char rows);
        Board(u_char columns, u_char rows, 
            std::vector<Queen> initQueens);
        ~Board();
        u_char GetColumns();
        u_char GetRows();
        void AddQueen(u_char xPos, u_char yPos);
        Board* DeepCopy();
        bool Collisions(u_char *count);
        bool Collisions(Queen queen, u_char *count);
        void Print();
        Queen* QueenAtPos(u_char x, u_char y);
        std::shared_ptr<std::vector<Board>> GenChildBoards();

        void MoveQueen(u_char index, u_char newX, u_char newY);

        #pragma region Operator Overloads

        bool operator==(Board *other);

        #pragma endregion
};

#endif