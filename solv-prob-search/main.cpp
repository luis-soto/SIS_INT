#include <iostream>
#include "problem-solver.h"

using namespace std;

int main()
{
	ProblemSolver* problemSolver = new ProblemSolver();

	problemSolver->searchSolution(SolveWith::A_STAR);
	cout << "Solving with A* Search" << endl;

	problemSolver->searchSolution(SolveWith::BFS);
	cout << "Solving with Breadth-first Search" << endl;

	problemSolver->searchSolution(SolveWith::DFS);
	cout << "Solving with Depth-first Search" << endl;

	return 0;
}
