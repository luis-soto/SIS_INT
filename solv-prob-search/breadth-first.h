#ifndef BREADTH_FIRST_H
#define BREADTH_FIRST_H

#include "tree.h"
#include "problem-formulator.h"
#include <vector>

using namespace std;

class BreadthFirst
{
    private:
        ProblemFormulator* _problemFormulation;
        Tree* _searchTree;
        vector<Node*> _openList;
        int _visitedNodes;
        Node* _actualNode;
        vector<Action> _actionQueue;

    public:
        BreadthFirst(ProblemFormulator* problemFormulation);

        ~BreadthFirst()
        {
            delete this->_searchTree;
        }

        vector<Action> breadthFirstSearch();

        bool isGoal() const;
        
        int getVisitedNodes()
        {
            return this->_visitedNodes;
        }

        void addNodeToOpenList(Node* node);

        void displayOpenList() const;
};

#endif // BREADTH_FIRST_H