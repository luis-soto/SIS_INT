#ifndef __TREE_H
#define __TREE_H

#include "graph.h"
#include <vector>

using namespace std;

enum Action
{
    TURN_LEFT,
    TURN_RIGHT,
    FRONT,
    NO_ACTION
};

class Node
{
	private:
		State* state;
		bool visited;
        Node* parent;
		vector<Node*> successors;
        // The necessary action to get to this node from the parent node
        Action action;
        // heuristic function for the node
        int f;
        // path cost till this node
        int g;

	public:
        Node(State* state, Node* parent = nullptr, int g = 0, Action action = NO_ACTION, int f = 0, bool visited = false)
        {
            this->state = state;
            this->visited = visited;
            this->parent = parent;
            this->f = f;
            this->g = g;
            this->action = action;
        }        

		~Node()
		{
			
		}

        void AddSuccessor(Node* newSuccessor);

        Action GetAction()
        {
            return this->action;
        }

        bool GetVisited() const
		{
			return this->visited;
		}
		
		int GetNumberOfSuccessors() const
		{
			return this->successors.size();
		}

        int GetF()
        {
            return this->f;
        }

        int GetG()
        {
            return this->g;
        }

        // IMPLEMENTED
        Node* GetSuccessor(int idx);

        // Can return Node* because Node (this class) is a class and already have encapsulation
        Node* GetParent() const
        {
            return this->parent;
        }

        State* GetState() const
        {
            return this->state;            
        }

		void SetVisited(bool visited)
		{
			this->visited = visited;
		}

        void SetAction(Action action)
        {
            this->action = action;
        }

        void SetF(int f)
        {
            this->f = f;
        }

        void SetG(int g)
        {
            this->g = g;
        }

        void SetParent(Node* parent)
        {
            this->parent = parent;
        }
};

class Tree
{
	private:
		Node* root;
        // tree class is friend of graph class
        Graph* graph;

	public:
        // When a tree is created it must receive the pointer to the root (source) state
        // and the associated graph
        Tree(State* rootState, Graph* graph)
        {
            this->root = new Node(rootState);
            this->graph = graph;
        }

		~Tree()
		{
			
		}

        // IMPLEMENTED
        // Find the successors from the node specified and expands the tree with them
        void FindSuccessors(Node* parent);

        // Determine the action taken to get from parent to child
        // idx is the index of the child in the graph
        Action DetermineAction(int idx, Node* parent);
};

#endif // __TREE_H