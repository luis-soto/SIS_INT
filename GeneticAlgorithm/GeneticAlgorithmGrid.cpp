#include "Header.h"
#include "Map.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"

int main()
{
	GeneticAlgorithm* geneticAlgorithm = new GeneticAlgorithm();
	geneticAlgorithm->printMap();
	geneticAlgorithm->findSolution().printIndividual();
	delete geneticAlgorithm;
	return 0;
}

