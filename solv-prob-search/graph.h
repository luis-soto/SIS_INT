#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>

using namespace std;

enum Direction
{
    // Northwest
    NW,
    // North
    N,
    // Northeast
    NE,
    // East
    E,
    // Southeast
    SE,
    // South
    S,
    // Southwest
    SW,
    // West
    W,
    // used when direction doesn't matter
    DEFAULT
};

class State
{
    private:
		int x;
        int y;
        Direction dir;
    
    public:
        State(int x = 0, int y = 0, Direction dir = Direction::DEFAULT)
        {
            this->x = x;
            this->y = y;
            this->dir = dir;
        }

        ~State()
        {

        }

        Direction GetDir()
        {
            return this->dir;
        }

        int GetX()
        {
            return this->x;
        }

        int GetY()
        {
            return this->y;
        }

        void SetDir(Direction dir)
        {
            this->dir = dir;
        }

        void SetX(int x)
        {
            this->x = x;
        }

        void SetY(int y)
        {
            this->y = y;
        }
            
};

/// This class defines a directed graph
class Graph
{
	private:
        int** edges;
		vector<State*> graph;
        int numCols, numRows, numDir;

	public:
        Graph(int numCols, int numRows, int numDir = 8)
        {
            // Create Adjancency-matrix and initializes to 0
            edges = new int*[numCols*numDir*numRows]();
            
            for(int it = 0; it < numCols*numDir*numRows; it++)
            {
                edges[it] = new int[numCols*numDir*numRows]();
            }
            
            this->numCols = numCols;
            this->numDir = numDir;
            this->numRows = numRows;
        }

        ~Graph()
        {
            for(int it = 0; it < this->numCols*this->numDir*this->numRows; it++)
            {
                delete [] this->edges[it];
            }
            delete [] this->edges;
            this->graph.clear();
        }

        // Can return State* because State is a class and already has encapsulation
        State* GetStateByIdx(int idx) const
        {
            State* retState = nullptr;

            if((0 <= idx) && (this->graph.size() > idx))
            {
                retState = this->graph[idx];
            }

            return retState;
        }

        int GetEdgeWeigthByIdx(int idxOrigin, int idxEnd) const;

        // Returns the maximum number of nodes suported by the graph
        int GetExpectedNumOfNodes() const
        {
            return this->numRows*this->numCols*this->numDir;
        }

        bool IsValidEdge(int idxOrigin, int idxEnd) const;

        bool IsAdjacent(int idxOrigin, int idxEnd) const;

        void AddAdjacentNode(int idxOrigin, int idxEnd, int w = 1);

        void AddAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);

        // Check whether or not x and y are in the range of possible states
        bool IsValidState(int x, int y) const;

        bool IsAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir) const;

        void DeleteNode(int x, int y, Direction dir);

        void JoinEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);
        
        void JoinNode(int x, int y, Direction dir);
        
        // Verifies whether or not the node specified by <x,y,dir> belongs to the graph
        // Returns the index of the node if belongs to the graph and -1 id doesn't
        int NodeIsMember(int x, int y, Direction dir) const;

        void RemoveEdge(int originX, int originY, Direction originDir,
                            int endX, int endY, Direction endDir);
};

#endif // __GRAPH_H
