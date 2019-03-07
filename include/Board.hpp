#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <memory>
#include "Queen.hpp"

class Board{
    private:
        //The size of the board
        char x, y;
        std::vector<std::shared_ptr<Queen>> queens;
    public:
        Board(char columns, char rows);
        Board(char columns, char rows, 
            std::vector<std::shared_ptr<Queen>> initQueens);
        ~Board();
        char GetColumns();
        char GetRows();
        void AddQueen(char xPos, char yPos);
        std::shared_ptr<Board> DeepCopy();
        bool Collisions(char *count);
        bool Collisions(std::shared_ptr<Queen> queen, char *count);
        void Print();
        std::shared_ptr<Queen> QueenAtPos(char x, char y);
        std::vector<std::unique_ptr<Board>> GenChildBoards();
};

#endif