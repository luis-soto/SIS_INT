#ifndef __A_STAR_H
#define __A_STAR_H

#include "tree.h"
#include "problem-formulator.h"
#include <vector>

using namespace std;

class AStar
{
    private:
        ProblemFormulator* _problemFormulation;
        Tree* _searchTree;
        vector<Node*> _openList;
        int _visitedNodes;
        Node* _actualNode;
        vector<Action> _actionQueue;

    public:
        AStar(ProblemFormulator* problemFormulation);

        ~AStar()
        {
            delete this->_searchTree;
        }

        vector<Action> aStarSearch();

        void calculateF(Node* node);

        bool isGoal() const;
        
        int getVisitedNodes()
        {
            return this->_visitedNodes;
        }

        int findBestNodeInOpenList() const;

        void addNodeToOpenList(Node* node);

        void displayOpenList() const;
};

#endif // __A_STAR_H