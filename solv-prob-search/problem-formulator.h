#ifndef PROBLEM_FORMULATOR_H
#define PROBLEM_FORMULATOR_H

#include "graph.h"
#include "map.h"

using namespace std;

// Class that formulates the problem with initial state, goal and generates the graph model
class ProblemFormulator
{
    private:
        State* initialState;

        // goalState represents the set of states that we want to reach
        // goalState.x represents the x of interest, if -1 doesn't matter
        // goalState.y represents the y of interest, if -1 doesn't matter
        // goalState.dir represents the direction of interest, if DEFAULT doesn't matter
        State* goalState;
        // Represents the model of the rectangular grid
        Graph* graphModel;
        // Represents the map
        Map* map;
    public:
        ProblemFormulator();
        
        ~ProblemFormulator()
        {
            delete this->initialState;
            delete this->goalState;
            delete this->graphModel;
        }

        void GenerateGraph();
};


#endif // PROBLEM_FORMULATION_H