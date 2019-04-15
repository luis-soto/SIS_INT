#ifndef __TREE_H
#define __TREE_H

#include "graph.h"
#include <vector>
#include <iostream>

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
		State* _state;
		bool _visited;
        Node* _parent;
		vector<Node*> _successors;
        Action _action;
        double _f;
        int _g;

	public:
        Node(State* state, Node* parent = nullptr, int g = 0, Action action = NO_ACTION, int f = 0, bool visited = false)
        {
            this->_state = state;
            this->_visited = visited;
            this->_parent = parent;
            this->_f = f;
            this->_g = g;
            this->_action = action;
        }        

		~Node()
		{
			
		}

        void addSuccessor(Node* newSuccessor);

        Action getAction() const
        {
            return this->_action;
        }

        bool getVisited() const
		{
			return this->_visited;
		}
		
		int getNumberOfSuccessors() const
		{
			return this->_successors.size();
		}

        int getF() const
        {
            return this->_f;
        }

        int getG() const
        {
            return this->_g;
        }

        Node* getSuccessor(int idx);

        // Can return Node* because Node (this class) is a class and already have encapsulation
        Node* getParent() const
        {
            return this->_parent;
        }

        State* getState() const
        {
            return this->_state;            
        }

		void setVisited(bool visited)
		{
			this->_visited = visited;
		}

        void setAction(Action action)
        {
            this->_action = action;
        }

        void setF(int f)
        {
            this->_f = f;
        }

        void setG(int g)
        {
            this->_g = g;
        }

        void setParent(Node* parent)
        {
            this->_parent = parent;
        }
};

class Tree
{
	private:
		Node* _root;
        vector<Node*> _nodes;
        Graph* _graph;

	public:
        // When a tree is created it must receive the pointer to the root (source) state
        // and the associated graph
        Tree(State* rootState, Graph* graph)
        {
            this->_root = new Node(rootState);
            this->_nodes.push_back(this->_root);
            this->_graph = graph;
        }

		~Tree()
		{
			this->_nodes.clear();
		}

        // Find the successors from the node specified and expands the tree with them
        void findSuccessors(Node* parent);

        // Determine the action taken to get from parent to child
        // idx is the index of the child in the graph
        Action determineAction(int idx, Node* parent);

        Node* getRootNode()
        {
            return this->_root;
        }

        bool isNodeInTree(State* state) const;

        vector<Action> generateActionQueue(Node* node);
};

#endif // __TREE_H