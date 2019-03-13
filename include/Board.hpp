#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <memory>
#include "Queen.hpp"
#include "Dir.hpp"
#include <functional>

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
        void Print(
            char sep, char indent,
            char aliveQueen, char deadQueen, 
            char whiteSquare, char blackSquare);
        void Print();
        Queen* QueenAtPos(u_char x, u_char y);
        std::shared_ptr<std::vector<std::shared_ptr<Board>>> GenChildBoards();

        void MoveQueen(u_char index, u_char newX, u_char newY);
        void MoveQueen(u_char index, Dir direction);

        u_char QueenSize() const;

        size_t QueenHash(u_char index) const;

        #pragma region Operator Overloads

        bool operator==(Board other);

        #pragma endregion
};

#endif