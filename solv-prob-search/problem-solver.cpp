#include "problem-solver.h"
#include "a-star.h"
#include "breadth-first.h"
#include "depth-first.h"

using namespace std;

// -------------------------------------------------------------------------------------------------
ProblemSolver::ProblemSolver()
{
    this->_problemFormulation = new ProblemFormulator();
}

// -------------------------------------------------------------------------------------------------
vector<Action> ProblemSolver::searchSolution(SolveWith searchAlgorithm)
{
    this->_solution.clear();
    // Error when using swith-case: can't declarate variables inside case (scope)
    if(SolveWith::A_STAR == searchAlgorithm)
    {
        AStar* aStar = new AStar(this->_problemFormulation);
        this->_solution = aStar->aStarSearch();

        cout << endl;
        cout << "number of states: " << this->_problemFormulation->getGraphModel()->getNumStates() << endl;
        cout << "number of visited states: " << aStar->getVisitedNodes() << endl;
        cout << endl;

        delete aStar;
    }
    else
    {
        if(SolveWith::BFS == searchAlgorithm)
        {
            BreadthFirst* breadthFirst = new BreadthFirst(this->_problemFormulation);
            this->_solution = breadthFirst->breadthFirstSearch();

            cout << endl;
            cout << "number of states: " << this->_problemFormulation->getGraphModel()->getNumStates() << endl;
            cout << "number of visited states: " << breadthFirst->getVisitedNodes() << endl;
            cout << endl;

            delete breadthFirst;
        }
        else
        {
            if(SolveWith::DFS == searchAlgorithm)
            {
                DepthFirst* depthFirst = new DepthFirst(this->_problemFormulation);
                this->_solution = depthFirst->depthFirstSearch();

                cout << endl;
                cout << "number of states: " << this->_problemFormulation->getGraphModel()->getNumStates() << endl;
                cout << "number of visited states: " << depthFirst->getVisitedNodes() << endl;
                cout << endl;

                delete depthFirst;
            }
        }
        
    }
   
    if(!this->_solution.empty())
	{
		cout << "Solution:" << endl << endl;
		for(int idx = this->_solution.size()-1; 0 <= idx ; idx--)
		{
			switch(this->_solution[idx])
			{
				case Action::TURN_LEFT:
					cout << "TURN_LEFT" << endl;
					break;

				case Action::TURN_RIGHT:
					cout << "TURN_RIGHT" << endl;
				break;

				case Action::FRONT:
					cout << "FRONT" << endl;
					break;
			}
		}
	}
    return this->_solution;
}