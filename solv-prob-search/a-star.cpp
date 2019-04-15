#include <cmath>
#include <iostream>
#include "a-star.h"

// -------------------------------------------------------------------------------------------------
AStar::AStar(ProblemFormulator* problemFormulation)
{
    this->_problemFormulation = problemFormulation;
    this->_searchTree = new Tree(this->_problemFormulation->getInitialState(),
                                this->_problemFormulation->getGraphModel());
    this->addNodeToOpenList(this->_searchTree->getRootNode());
    this->_actualNode = nullptr;
    this->_visitedNodes = 0;
}

// -------------------------------------------------------------------------------------------------
vector<Action> AStar::aStarSearch()
{
    bool pathFound = false;

    while(!this->_openList.empty() && !pathFound)
    {
        this->_visitedNodes++;
        int bestIdx = this->findBestNodeInOpenList();
        this->_actualNode = this->_openList[bestIdx];

        cout << endl;
        displayOpenList();
        cout << "bestIdx = " << bestIdx << endl;
        cout << "visiting node x = " << _actualNode->getState()->getX() << endl;
        cout << "visiting node y = " << _actualNode->getState()->getY() << endl;
        cout << "visiting node dir = " << _actualNode->getState()->getDir() << endl;
        cout << "visiting node f = " << _actualNode->getF() << endl;
        cout << "visited of visiting node = " << this->_actualNode->getVisited() << endl;
        cout << endl;

        this->_actualNode->setVisited(true);

        this->_openList.erase(this->_openList.begin()+bestIdx);
        
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
void AStar::addNodeToOpenList(Node* node)
{
    if(nullptr != node)
    {
        this->calculateF(node);
        this->_openList.push_back(node);
    }
}

// -------------------------------------------------------------------------------------------------
void AStar::calculateF(Node* node)
{
    if(nullptr != node)
    {
        double h = sqrt(pow((this->_problemFormulation->getGoalState()->getX()-node->getState()->getX()), 2) +
                        pow((this->_problemFormulation->getGoalState()->getY()-node->getState()->getY()), 2));
        node->setF(node->getG()+h);
    }
}

// -------------------------------------------------------------------------------------------------
int AStar::findBestNodeInOpenList() const
{
    int bestIdx;

    if(!this->_openList.empty())
    {
        bestIdx = 0;
        for(int idx = 0; idx < this->_openList.size(); idx++)
        {
            if(this->_openList[idx]->getF() < this->_openList[bestIdx]->getF())
            {
                bestIdx = idx;
            }
        }
    }
    else
    {
        bestIdx = -1;
    }

    return bestIdx;
}

// -------------------------------------------------------------------------------------------------
bool AStar::isGoal() const
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

void AStar::displayOpenList() const
{
    for(int idx = 0; this->_openList.size() > idx; idx++)
    {
        cout << "N" << idx+1 << "=" << this->_openList[idx]->getF() << "  ";
    }
    cout << endl;
}