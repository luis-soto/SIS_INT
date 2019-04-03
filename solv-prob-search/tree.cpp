#include "tree.h"
#include <stdlib.h>							// abs()

using namespace std;

// -------------------------------------------------------------------------------------------------
void Node::AddSuccessor(Node* newSuccessor)
{
	this->successors.push_back(newSuccessor);
}

// -------------------------------------------------------------------------------------------------
Node* Node::GetSuccessor(int idx)
{
	Node* ret = nullptr;
	
	if(this->successors.size() > idx)
	{
		ret = this->successors[idx];
	}
	else
	{
		// Node don't have this number of successors
	}
	
	return ret;
}

// -------------------------------------------------------------------------------------------------
void Tree::FindSuccessors(Node* parent)
{
	if(nullptr != parent)
	{
		vector<int> adjNodes;
		int parentIdx = this->graph->NodeIsMember(parent->GetState()->GetX(), parent->GetState()->GetY(),
												  parent->GetState()->GetDir());
		
		// Determine adjacent nodes (interpreted as children in the tree)
		for(int adjIdx = 0; adjIdx < graph->GetExpectedNumOfNodes(); adjIdx++)
		{
			if(graph->IsAdjacent(parentIdx, adjIdx))
			{
				adjNodes.push_back(adjIdx);
			}
		}

		// Create nodes and add them to the successors vector of the parent node
		for(int idx = 0; idx < adjNodes.size(); idx++)
		{
			Action action = DetermineAction(adjNodes[idx], parent);

			Node* newNode = new Node(graph->GetStateByIdx(adjNodes[idx]), parent,
									(parent->GetG())+graph->GetEdgeWeigthByIdx(parentIdx, adjNodes[idx]), action);

			if(nullptr != newNode)
			{
				parent->AddSuccessor(newNode);
			}
		}

		adjNodes.clear();
	}
	else
	{
		// Isn't a valid node
	}
}

// -------------------------------------------------------------------------------------------------
Action Tree::DetermineAction(int idx, Node* parent)
{
	Action action;

	if((1 == abs(graph->GetStateByIdx(idx)->GetX()-parent->GetState()->GetX())) ||
		(1 == abs(graph->GetStateByIdx(idx)->GetY()-parent->GetState()->GetY())))
	{
		action = Action::FRONT;
	}
	else
	{
		if((1 == (graph->GetStateByIdx(idx)->GetDir()-parent->GetState()->GetDir())) ||
			((Direction::W-Direction::NW) == (graph->GetStateByIdx(idx)->GetDir()-parent->GetState()->GetDir())))
		{
			action = Action::TURN_RIGHT;
		}
		else
		{
			if((-1==(graph->GetStateByIdx(idx)->GetDir()-parent->GetState()->GetDir())) ||
				((Direction::NW-Direction::W) == (graph->GetStateByIdx(idx)->GetDir()-parent->GetState()->GetDir())))
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