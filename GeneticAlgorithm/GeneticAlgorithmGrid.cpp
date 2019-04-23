#include "Header.h"
#include "Map.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"

int main()
{
	GeneticAlgorithm* geneticAlgorithm = new GeneticAlgorithm();
	geneticAlgorithm->printMap();
	geneticAlgorithm->generatePopulation();
	geneticAlgorithm->printPopulation();
	geneticAlgorithm->crossoverPopulation();

	std::cout << "New population:" << endl;
	
	geneticAlgorithm->printPopulation();
	delete geneticAlgorithm;
	return 0;
}

