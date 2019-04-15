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
		int _x;
        int _y;
        Direction _dir;
    
    public:
        State(int x = 0, int y = 0, Direction dir = Direction::DEFAULT)
        {
            this->_x = x;
            this->_y = y;
            this->_dir = dir;
        }

        ~State()
        {

        }

        Direction getDir()
        {
            return this->_dir;
        }

        int getX()
        {
            return this->_x;
        }

        int getY()
        {
            return this->_y;
        }

        void setDir(Direction dir)
        {
            this->_dir = dir;
        }

        void setX(int x)
        {
            this->_x = x;
        }

        void setY(int y)
        {
            this->_y = y;
        }
            
};

/// This class defines a directed graph
class Graph
{
	private:
        int** _edges;
		vector<State*> _graph;
        int _numCols, _numRows, _numDir;

	public:
        Graph(int numCols, int numRows, int numDir = 8)
        {
            // Create Adjancency-matrix and initializes to 0
            this->_edges = new int*[numCols*numDir*numRows]();
            
            for(int it = 0; it < numCols*numDir*numRows; it++)
            {
                _edges[it] = new int[numCols*numDir*numRows]();
            }
            
            this->_numCols = numCols;
            this->_numDir = numDir;
            this->_numRows = numRows;
        }

        ~Graph()
        {
            for(int it = 0; it < getExpectedNumOfNodes(); it++)
            {
                delete [] this->_edges[it];
            }
            delete [] this->_edges;
            
            this->_graph.clear();
        }

        // Can return State* because State is a class and already has encapsulation
        State* getStateByIdx(int idx) const
        {
            State* retState = nullptr;

            if((0 <= idx) && (this->_graph.size() > idx))
            {
                retState = this->_graph[idx];
            }

            return retState;
        }

        int getEdgeWeigthByIdx(int idxOrigin, int idxEnd) const;

        // Returns the maximum number of nodes suported by the graph
        int getExpectedNumOfNodes() const
        {
            return this->_numRows*this->_numCols*this->_numDir;
        }

        int getNumStates()
        {
            return this->_graph.size();
        }

        bool isValidEdge(int idxOrigin, int idxEnd) const;

        bool isAdjacent(int idxOrigin, int idxEnd) const;

        void addAdjacentNode(int idxOrigin, int idxEnd, int w = 1);

        void addAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);

        // Check whether or not x and y are in the range of possible states
        bool isValidState(int x, int y) const;

        bool isAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir) const;

        void deleteNode(int x, int y, Direction dir);

        void joinEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);
        
        void joinNode(int x, int y, Direction dir);
        
        // Verifies whether or not the node specified by <x,y,dir> belongs to the graph
        // Returns the index of the node if belongs to the graph and -1 id doesn't
        int nodeIsMember(int x, int y, Direction dir) const;

        void removeEdge(int originX, int originY, Direction originDir,
                            int endX, int endY, Direction endDir);
};

#endif // __GRAPH_H
