#ifndef PROBLEM_FORMULATOR_H
#define PROBLEM_FORMULATOR_H

#include "graph.h"
#include "map.h"

using namespace std;

// Class that formulates the problem with initial state, goal and generates the graph model
class ProblemFormulator
{
    private:
        State* _initialState;

        // goalState represents the set of states that we want to reach
        // goalState.x represents the x of interest, if -1 doesn't matter
        // goalState.y represents the y of interest, if -1 doesn't matter
        // goalState.dir represents the direction of interest, if DEFAULT doesn't matter
        State* _goalState;
        // Represents the model of the rectangular grid
        Graph* _graphModel;
        // Represents the map
        Map* _map;
    public:
        ProblemFormulator();
        
        ~ProblemFormulator()
        {
            delete this->_initialState;
            delete this->_goalState;
            delete this->_graphModel;
        }

        State* getGoalState()
        {
            return this->_goalState;
        }

        State* getInitialState()
        {
            return this->_initialState;
        }

        Graph* getGraphModel()
        {
            return this->_graphModel;
        }

        Map* getMap()
        {
            return this->_map;
        }

        void generateGraph();
};


#endif // PROBLEM_FORMULATION_H