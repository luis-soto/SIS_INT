#include "graph.h"

using namespace std;

// -------------------------------------------------------------------------------------------------
void Graph::addAdjacentNode(int idxOrigin, int idxEnd, int w)
{
	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		this->_edges[idxOrigin][idxEnd] = w;
	}
}

// -------------------------------------------------------------------------------------------------
void Graph::addAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w)
{
	int idxOrigin = this->nodeIsMember(originX, originY, originDir);
	int idxEnd = this->nodeIsMember(endX, endY, endDir);

	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		this->_edges[idxOrigin][idxEnd] = w;
	}
}

// -------------------------------------------------------------------------------------------------
bool Graph::isAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir) const
{
	bool isAdjacent = false;
	int idxOrigin = this->nodeIsMember(originX, originY, originDir);
	int idxEnd = this->nodeIsMember(endX, endY, endDir);

	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		if(0 != this->_edges[idxOrigin][idxEnd])
		{
			isAdjacent = true;
		}
	}
	return isAdjacent;
}

// -------------------------------------------------------------------------------------------------
int Graph::getEdgeWeigthByIdx(int idxOrigin, int idxEnd) const
{
	int weigth = 0;

	if(isValidEdge(idxOrigin, idxEnd))
	{
		weigth = this->_edges[idxOrigin][idxEnd];
	}

	return weigth;
}

// -------------------------------------------------------------------------------------------------
bool Graph::isValidEdge(int idxOrigin, int idxEnd) const
{
	bool isValid = false;

	if(((0 <= idxOrigin) && (this->getExpectedNumOfNodes() > idxOrigin)) &&
		((0 <= idxEnd) && (this->getExpectedNumOfNodes() > idxEnd)))
	{
		isValid = true;
	}

	return isValid;
}

// -------------------------------------------------------------------------------------------------
bool Graph::isAdjacent(int idxOrigin, int idxEnd) const
{
	bool isAdjacent = false;

	if(0 != this->_edges[idxOrigin][idxEnd])
	{
		isAdjacent = true;
	}
	return isAdjacent;
}

// -------------------------------------------------------------------------------------------------
void Graph::deleteNode(int x, int y, Direction dir)
{
	int idx = this->nodeIsMember(x, y, dir);

	if(-1 != idx)
	{
		this->_graph.erase(this->_graph.begin()+idx);
	}	
}

// -------------------------------------------------------------------------------------------------
int Graph::nodeIsMember(int x, int y, Direction dir) const
{
	int idx = -1;
	for(int it = 0; it < this->_graph.size();it++)
	{
		if(this->_graph[it]->getX() == x)
		{
			if(this->_graph[it]->getY() == y)
			{
				if(this->_graph[it]->getDir() == dir)
				{
					idx = it;
				}
			}			
		}
	}
	return idx;
}

// -------------------------------------------------------------------------------------------------
void Graph::joinEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w)
{	
	int idxOrigin = this->nodeIsMember(originX, originY, originDir);
	int idxEnd = this->nodeIsMember(endX, endY, endDir);
	
	if(-1 == idxOrigin)
	{
		this->joinNode(originX, originY, originDir);
		idxOrigin = this->_graph.size()-1;
	}

	if(-1 == idxEnd)
	{
		this->joinNode(endX, endY, endDir);
		idxEnd = this->_graph.size()-1;
	}	
	
	if(!this->isAdjacent(idxOrigin, idxEnd))
	{
		this->addAdjacentNode(idxOrigin, idxEnd, w);
	}
}

// -------------------------------------------------------------------------------------------------
bool Graph::isValidState(int x, int y) const
{
	bool isValid = false;

	if((0 <= x) && (this->_numRows > x) && (0 <= y) && (this->_numCols > y))
	{
		isValid = true;
	}

	return isValid;
}

// -------------------------------------------------------------------------------------------------
void Graph::joinNode(int x, int y, Direction dir)
{
	if(this->isValidState(x, y))
	{
		const int idx = this->nodeIsMember(x, y, dir);

		// Node does not exist already
		if(-1 == idx)
		{
			State* newNode = new State(x, y, dir);
			if(nullptr != newNode)
			{
				this->_graph.push_back(newNode);
			}
		}
	}
}

// -------------------------------------------------------------------------------------------------
void Graph::removeEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir)
{
	int idxOrigin = this->nodeIsMember(originX, originY, originDir);
	int idxEnd = this->nodeIsMember(endX, endY, endDir);

	if((-1 != idxEnd) && (-1 != idxOrigin))
	{
		this->_edges[idxOrigin][idxEnd] = 0;
	}
}