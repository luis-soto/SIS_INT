#include "graph.h"
#include "tree.h"

using namespace std;

// -------------------------------------------------------------------------------------------------
void Graph::AddAdjacentNode(int idxOrigin, int idxEnd, int w)
{
	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		this->edges[idxOrigin][idxEnd] = w;
	}
}

// -------------------------------------------------------------------------------------------------
void Graph::AddAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w)
{
	int idxOrigin = this->NodeIsMember(originX, originY, originDir);
	int idxEnd = this->NodeIsMember(endX, endY, endDir);

	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		this->edges[idxOrigin][idxEnd] = w;
	}
}

// -------------------------------------------------------------------------------------------------
bool Graph::IsAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir) const
{
	bool isAdjacent = false;
	int idxOrigin = this->NodeIsMember(originX, originY, originDir);
	int idxEnd = this->NodeIsMember(endX, endY, endDir);

	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		if(0 != this->edges[idxOrigin][idxEnd])
		{
			isAdjacent = true;
		}
	}
	return isAdjacent;
}

// -------------------------------------------------------------------------------------------------
int Graph::GetEdgeWeigthByIdx(int idxOrigin, int idxEnd) const
{
	int weigth = 0;

	if(IsValidEdge(idxOrigin, idxEnd))
	{
		weigth = this->edges[idxOrigin][idxEnd];
	}

	return weigth;
}

// -------------------------------------------------------------------------------------------------
bool Graph::IsValidEdge(int idxOrigin, int idxEnd) const
{
	bool isValid = false;

	if(((0 <= idxOrigin) && (this->GetExpectedNumOfNodes() > idxOrigin)) &&
		((0 <= idxEnd) && (this->GetExpectedNumOfNodes() > idxEnd)))
	{
		isValid = true;
	}

	return isValid;
}

// -------------------------------------------------------------------------------------------------
bool Graph::IsAdjacent(int idxOrigin, int idxEnd) const
{
	bool isAdjacent = false;

	if(0 != this->edges[idxOrigin][idxEnd])
	{
		isAdjacent = true;
	}
	return isAdjacent;
}

// -------------------------------------------------------------------------------------------------
void Graph::DeleteNode(int x, int y, Direction dir)
{
	int idx = this->NodeIsMember(x, y, dir);

	if(-1 != idx)
	{
		this->graph.erase(this->graph.begin()+idx);
	}	
}

// -------------------------------------------------------------------------------------------------
int Graph::NodeIsMember(int x, int y, Direction dir) const
{
	int idx = -1;
	for(int it = 0; it < this->graph.size();it++)
	{
		if(this->graph[it]->GetX() == x)
		{
			if(this->graph[it]->GetY() == y)
			{
				if(this->graph[it]->GetDir() == dir)
				{
					idx = it;
				}
			}			
		}
	}
	return idx;
}

// -------------------------------------------------------------------------------------------------
void Graph::JoinEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w)
{	
	int idxOrigin = this->NodeIsMember(originX, originY, originDir);
	int idxEnd = this->NodeIsMember(endX, endY, endDir);
	
	if(-1 == idxOrigin)
	{
		this->JoinNode(originX, originY, originDir);
		idxOrigin = this->graph.size()-1;
	}

	if(-1 == idxEnd)
	{
		this->JoinNode(endX, endY, endDir);
		idxEnd = this->graph.size()-1;
	}	
	
	if(!this->IsAdjacent(idxOrigin, idxEnd))
	{
		this->AddAdjacentNode(idxOrigin, idxEnd, w);
	}
}

// -------------------------------------------------------------------------------------------------
bool Graph::IsValidState(int x, int y) const
{
	bool isValid = false;

	if((0 <= x) && (this->numRows > x) && (0 <= y) && (this->numCols > y))
	{
		isValid = true;
	}

	return isValid;
}

// -------------------------------------------------------------------------------------------------
void Graph::JoinNode(int x, int y, Direction dir)
{
	if(this->IsValidState(x, y))
	{
		const int idx = this->NodeIsMember(x, y, dir);

		// Node does not exist already
		if(-1 == idx)
		{
			State* newNode = new State(x, y, dir);
			if(nullptr != newNode)
			{
				this->graph.push_back(newNode);
			}
		}
	}
}

// -------------------------------------------------------------------------------------------------
void Graph::RemoveEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir)
{
	int idxOrigin = this->NodeIsMember(originX, originY, originDir);
	int idxEnd = this->NodeIsMember(endX, endY, endDir);

	if((-1 != idxEnd) && (-1 != idxOrigin))
	{
		this->edges[idxOrigin][idxEnd] = 0;
	}
}