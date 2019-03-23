#ifndef SearchResults_hpp
#define SearchResults_hpp

#include <cmath>
#include <memory>
#include <vector>

#include "Board.hpp"

class SearchResults{
    private:
        u_long uniqueBoards, expectedBoards;
        std::unique_ptr<std::vector<std::unique_ptr<Board>>> solutions;
        double timeTaken;
    public:
        SearchResults();
        SearchResults(
            u_long uniqueBoards, u_long expectedBoards, 
            std::unique_ptr<std::vector<std::unique_ptr<Board>>> solutions,
            double timeTaken);
        ~SearchResults();
        void Print();
};

#endif