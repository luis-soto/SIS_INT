#ifndef PROBLEM_SOLVER_H
#define PROBLEM_SOLVER_H

#include <vector>
#include "problem-formulator.h"
#include "tree.h"

enum SolveWith
{
    A_STAR,
    DFS,
    BFS
};
class ProblemSolver
{
    private:
        ProblemFormulator* _problemFormulation;
        vector<Action> _solution;

    public:
        ProblemSolver();

        ~ProblemSolver()
        {
            delete this->_problemFormulation;
        }

        std::vector<Action> searchSolution(SolveWith searchAlgorithm = SolveWith::A_STAR);
};

#endif // PROBLEM_SOLVER_H