#ifndef HashBoard_hpp
#define HashBoard_hpp

#include "Board.hpp"
#include "Queen.hpp"
#include <functional>

namespace std
{

    template <>
    struct hash<Queen>
    {
        std::size_t operator()(const Queen &k) const
        {
            using std::size_t;

            return k.PosSingle();
        }
    };

    template <>
    struct hash<Board>
    {
        std::size_t operator()(const Board &k) const
        {
            using std::hash;
            using std::size_t;
            size_t finalHash = 0;
            for (u_char i = 0; i < k.QueenSize(); i++)
                finalHash ^= k.QueenHash(i);
            return finalHash;
        }
    };

} // namespace std

#endif