#ifndef GRAPH_H
#define GRAPH_H

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

struct State
{
		unsigned int x;
        unsigned int y;
        Direction dir;
};

/// This class defines a directed graph
class Graph
{
	private:
        int** edges;
		vector<State*> graph;
        int numCols, numRows, numDir;

        bool IsAdjacent(int idxOrigin, int idxEnd);

        void AddAdjacentNode(int idxOrigin, int idxEnd, int w = 1);

	public:
        Graph(int numCols, int numRows, int numDir)
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

        void AddAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);

        bool IsAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir);

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

#endif // GRAPH_H
