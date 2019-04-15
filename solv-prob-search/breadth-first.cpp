#include "breadth-first.h"
#include <cmath>
#include <iostream>

// -------------------------------------------------------------------------------------------------
BreadthFirst::BreadthFirst(ProblemFormulator* problemFormulation)
{
    this->_problemFormulation = problemFormulation;
    this->_searchTree = new Tree(this->_problemFormulation->getInitialState(),
                                this->_problemFormulation->getGraphModel());
    this->addNodeToOpenList(this->_searchTree->getRootNode());
    this->_actualNode = nullptr;
    this->_visitedNodes = 0;
}

// -------------------------------------------------------------------------------------------------
vector<Action> BreadthFirst::breadthFirstSearch()
{
    bool pathFound = false;

    while(!this->_openList.empty() && !pathFound)
    {
        this->_visitedNodes++;
        this->_actualNode = this->_openList[0];

        cout << endl;
        displayOpenList();
        cout << "visiting node x = " << this->_actualNode->getState()->getX() << endl;
        cout << "visiting node y = " << this->_actualNode->getState()->getY() << endl;
        cout << "visiting node dir = " << this->_actualNode->getState()->getDir() << endl;
        cout << "visiting node f = " << this->_actualNode->getF() << endl;
        cout << "visited of visiting node = " << this->_actualNode->getVisited() << endl;
        cout << endl;

        this->_actualNode->setVisited(true);

        this->_openList.erase(this->_openList.begin());
        
        if(this->isGoal())
        {
            pathFound = true;
        }
        else
        {
            this->_searchTree->findSuccessors(this->_actualNode);
            for(int idx = 0; this->_actualNode->getNumberOfSuccessors() > idx; idx++)
            {
                Node* successor = this->_actualNode->getSuccessor(idx);
                if(nullptr != successor)
                {
                    this->addNodeToOpenList(successor);
                }
            }
        }
    }

    if(this->_openList.empty())
    {
        cout << "Path not found." << endl;
    }

    if(pathFound)
    {
        cout << "Path found." << endl;
        this->_actionQueue = this->_searchTree->generateActionQueue(this->_actualNode);
    }
    return this->_actionQueue;
}

// -------------------------------------------------------------------------------------------------
void BreadthFirst::addNodeToOpenList(Node* node)
{
    if(nullptr != node)
    {
        this->_openList.push_back(node);
    }
}

// -------------------------------------------------------------------------------------------------
bool BreadthFirst::isGoal() const
{
    bool isGoal = false;
    if(nullptr != this->_actualNode)
    {
        if((this->_actualNode->getState()->getX() == this->_problemFormulation->getGoalState()->getX()) &&
            (this->_actualNode->getState()->getY() == this->_problemFormulation->getGoalState()->getY()))
        {
            if(Direction::DEFAULT != this->_problemFormulation->getGoalState()->getDir())
            {
                if(this->_actualNode->getState()->getDir() == this->_problemFormulation->getGoalState()->getDir())
                {
                    isGoal = true;
                }
            }
            else
            {
                isGoal = true;
            }
        }
    }
    return isGoal;
}

// -------------------------------------------------------------------------------------------------
void BreadthFirst::displayOpenList() const
{
    for(int idx = 0; this->_openList.size() > idx; idx++)
    {
        cout << "N" << idx+1 << "=" << this->_openList[idx]->getF() << "  ";
    }
    cout << endl;
}