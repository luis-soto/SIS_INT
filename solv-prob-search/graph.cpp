#include <iostream>
#include <fstream>
#include "tarefa1.h"

using namespace std;

void Graph::AddAdjacentNode(int idxOrigin, int idxEnd, int w)
{
	if((-1 != idxOrigin) && (-1 != idxEnd))
	{
		this->edges[idxOrigin][idxEnd] = w;
	}
}

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

bool Graph::IsAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir)
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

bool Graph::IsAdjacent(int idxOrigin, int idxEnd)
{
	bool isAdjacent = false;

	if(0 != this->edges[idxOrigin][idxEnd])
	{
		isAdjacent = true;
	}
	return isAdjacent;
}

void Graph::DeleteNode(int x, int y, Direction dir)
{
	int idx = this->NodeIsMember(x, y, dir);

	if(-1 != idx)
	{
		this->graph.erase(this->graph.begin()+idx);
	}	
}

int Graph::NodeIsMember(int x, int y, Direction dir) const
{
	int idx = -1;
	for(int it = 0; it < this->graph.size();it++)
	{
		if(this->graph[it]->x == x)
		{
			if(this->graph[it]->y == y)
			{
				if(this->graph[it]->dir == dir)
				{
					idx = it;
				}
			}			
		}
	}
	return idx;
}

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

void Graph::JoinNode(int x, int y, Direction dir)
{
	const int idx = this->NodeIsMember(x, y, dir);
	if(-1 == idx)
	{
		Node* newNode = new Node();
		if(nullptr != newNode)
		{
			newNode->dir = dir;
			newNode->x = x;
			newNode->y = y;
			this->graph.push_back(newNode);
		}
	}
}

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

void Graph::DisplayNode(int idx)
{
	cout << "Node " << idx << " represents state: <" << this->graph[idx]->x << "," << this->graph[idx]->y
		 << "," << this->graph[idx]->dir << ">" << endl;
}

int main()
{
	Graph graph(10, 10, 8);
	cout << "Starting graph creation..." << endl;
	graph.JoinNode(0,0,Direction::E);
	graph.JoinNode(9,1,Direction::NE);
	graph.DisplayNode(0);
	graph.DisplayNode(1);
	graph.DeleteNode(0,0,Direction::E);
	graph.DisplayNode(0);
	return 0;
}
