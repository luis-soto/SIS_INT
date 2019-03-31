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
    W
};

// This class defines the nodes of a graph (directed or undirected)
struct Node
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
		vector<Node*> graph;
        int numCols, numRows, numDir;

        // IMPLEMENTED
        bool IsAdjacent(int idxOrigin, int idxEnd);

        // IMPLEMENTED
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

        // IMPLEMENTED
        void AddAdjacentNode(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);

        // IMPLEMENTED
        bool IsAdjacent(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir);

        // IMPLEMENTED
        void DeleteNode(int x, int y, Direction dir);

        // IMPLEMENTED
        void JoinEdge(int originX, int originY, Direction originDir,
                        int endX, int endY, Direction endDir, int w = 1);
        
        // IMPLEMENTED
        void JoinNode(int x, int y, Direction dir);
        
        // IMPLEMENTED
        // Verifies whether or not the node specified by <x,y,dir> belongs to the graph
        // Returns the index of the node if belongs to the graph and -1 id doesn't
        int NodeIsMember(int x, int y, Direction dir) const;

        // IMPLEMENTED
        void RemoveEdge(int originX, int originY, Direction originDir,
                            int endX, int endY, Direction endDir);

        void DisplayNode(int idxOrigin);
};

#endif // GRAPH_H
