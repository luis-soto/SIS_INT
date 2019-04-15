#include "tree.h"
#include <stdlib.h>							// abs()

using namespace std;

// -------------------------------------------------------------------------------------------------
void Node::addSuccessor(Node* newSuccessor)
{
	if(nullptr != newSuccessor)
	{
		this->_successors.push_back(newSuccessor);
	}
}

// -------------------------------------------------------------------------------------------------
Node* Node::getSuccessor(int idx)
{
	Node* ret = nullptr;
	
	if(this->_successors.size() > idx)
	{
		ret = this->_successors[idx];
	}
	else
	{
		// Node don't have this number of successors
	}
	
	return ret;
}

// -------------------------------------------------------------------------------------------------
void Tree::findSuccessors(Node* parent)
{
	if(nullptr != parent)
	{
		//// Need to verify if the State* returned by GetState() is nullptr
		int parentIdx = this->_graph->nodeIsMember(parent->getState()->getX(), parent->getState()->getY(),
												  parent->getState()->getDir());
		
		if(-1 != parentIdx)
		{
			vector<int> adjNodes;

			// Determine adjacent nodes (interpreted as children in the tree)
			for(int adjIdx = 0; adjIdx < this->_graph->getExpectedNumOfNodes(); adjIdx++)
			{
				if(this->_graph->isAdjacent(parentIdx, adjIdx))
				{
					adjNodes.push_back(adjIdx);
				}
			}

			// Create nodes and add them to the successors vector of the parent node
			// if the nodes don't exist already
			for(int idx = 0; idx < adjNodes.size(); idx++)
			{
				if(!this->isNodeInTree(this->_graph->getStateByIdx(adjNodes[idx])))
				{
					Action action = determineAction(adjNodes[idx], parent);

					Node* newNode = new Node(this->_graph->getStateByIdx(adjNodes[idx]), parent,
											(parent->getG())+this->_graph->getEdgeWeigthByIdx(parentIdx,
											adjNodes[idx]), action);

					this->_nodes.push_back(newNode);

					if(nullptr != newNode)
					{
						parent->addSuccessor(newNode);
					}
				}
			}

			adjNodes.clear();
			}
	}
	else
	{
		// Isn't a valid node
	}
}

// -------------------------------------------------------------------------------------------------
Action Tree::determineAction(int idx, Node* parent)
{
	Action action;

	if((1 == abs(this->_graph->getStateByIdx(idx)->getX()-parent->getState()->getX())) ||
		(1 == abs(this->_graph->getStateByIdx(idx)->getY()-parent->getState()->getY())))
	{
		action = Action::FRONT;
	}
	else
	{
		if((1 == (this->_graph->getStateByIdx(idx)->getDir()-parent->getState()->getDir())) ||
			((Direction::W-Direction::NW) == (this->_graph->getStateByIdx(idx)->getDir()-parent->getState()->getDir())))
		{
			action = Action::TURN_RIGHT;
		}
		else
		{
			if((-1==(this->_graph->getStateByIdx(idx)->getDir()-parent->getState()->getDir())) ||
				((Direction::NW-Direction::W) == (this->_graph->getStateByIdx(idx)->getDir()-parent->getState()->getDir())))
			{
				action = Action::TURN_LEFT;
			}
			else
			{
				action = Action::NO_ACTION;
			}
		}
	}
	return action;
}

// -------------------------------------------------------------------------------------------------
bool Tree::isNodeInTree(State* state) const
{
	bool isNodeInTree = false;
	if(nullptr != state)
	{
		if(!this->_nodes.empty())
		{
			for(auto it : this->_nodes)
			{
				if((state->getX() == it->getState()->getX()) && (state->getY() == it->getState()->getY())
					&& (state->getDir() == it->getState()->getDir()))
				{
					isNodeInTree = true;
				}
			}
		}
	}
	return isNodeInTree;
}

// -------------------------------------------------------------------------------------------------
vector<Action> Tree::generateActionQueue(Node* node)
{
	vector<Action> actionQueue;
	if(nullptr != node)
	{
		while(nullptr != node)
		{
			actionQueue.push_back(node->getAction());
			node = node->getParent();
		}
	}
	return actionQueue;
}