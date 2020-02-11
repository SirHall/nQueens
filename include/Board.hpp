#ifndef Board_hpp
#define Board_hpp

#include "Dir.hpp"
#include "Queen.hpp"
#include <functional>
#include <memory>
#include <vector>

class Board
{
private:
    // The size of the board
    u_char             x, y;
    std::vector<Queen> queens;

public:
    Board(u_char columns, u_char rows);
    Board(u_char columns, u_char rows, std::vector<Queen> initQueens);
    ~Board();
    u_char GetColumns();
    u_char GetRows();
    u_char AddQueen(u_char xPos, u_char yPos);
    Board *DeepCopy();
    bool   Collisions(u_long *count);
    bool   Collisions(Queen queen, u_long *count);

    Queen GetQueen(u_char index);

    void   Print(char sep, char indent, char aliveQueen, char deadQueen,
                 char whiteSquare, char blackSquare);
    void   Print();
    Queen *QueenAtPos(u_char x, u_char y);
    std::unique_ptr<std::vector<std::unique_ptr<Board>>>
        GenChildBoards(bool horizontalOnly, bool canMoveBackwards);

    void MoveQueen(u_char index, u_char newX, u_char newY);
    void MoveQueen(u_char index, Dir direction);

    u_char QueenSize() const;

    size_t QueenHash(u_char index) const;

    bool Increment();

    static bool AlreadyExists(
        std::unique_ptr<Board> &                              board,
        std::unique_ptr<std::vector<std::unique_ptr<Board>>> &collection);

    bool RemoveQueen(u_char index);

#pragma region Operator Overloads

    bool operator==(Board other);

#pragma endregion

    bool IsWithinBoard(int xPos, int yPos);
};

#endif