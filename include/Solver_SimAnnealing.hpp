#ifndef Solver_SimAnnealing_hpp
#define Solver_SimAnnealing_hpp

#include "Solver_Base.hpp"

class Solver_SimAnnealing : public Solver_Base{
    private:
        double FindCoolingVal(
            u_long iterations, 
            double initTemp, 
            double targetTemp
        );

        //Will randomly choose whether or not to accept a new board or not
        bool RandAccept(u_int currentCost, u_int newCost, double temp);

        //How's that for creative function names?
        //Atleast it's really clear what this does...
        void MoveRandomQueenRandomly(std::unique_ptr<Board> &board);

    public:
        Solver_SimAnnealing();
        ~Solver_SimAnnealing();
        //NOTE: Use std::move(initBoard) to move possession  of board
        //  to this function 
        std::unique_ptr<SearchResults> Solve(
            std::unique_ptr<Board> initBoard,
            steady_clock::time_point &clock_start
            );
        std::string GetName();
};

#endif