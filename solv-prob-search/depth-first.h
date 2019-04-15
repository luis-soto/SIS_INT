#ifndef DEPTH_FIRST_H
#define DEPTH_FIRST_H

#include "tree.h"
#include "problem-formulator.h"
#include <vector>

using namespace std;

class DepthFirst
{
    private:
        ProblemFormulator* _problemFormulation;
        Tree* _searchTree;
        vector<Node*> _openList;
        int _visitedNodes;
        Node* _actualNode;
        vector<Action> _actionQueue;

    public:
        DepthFirst(ProblemFormulator* problemFormulation);

        ~DepthFirst()
        {
            delete this->_searchTree;
        }

        vector<Action> depthFirstSearch();

        bool isGoal() const;
        
        int getVisitedNodes()
        {
            return this->_visitedNodes;
        }

        void addNodeToOpenList(Node* node);

        void displayOpenList() const;
};

#endif // DEPTH_FIRST_H