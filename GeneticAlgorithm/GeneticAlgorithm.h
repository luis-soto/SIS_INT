#ifndef __GENETIC_ALGORITHM_H
#define __GENETIC_ALGORITHM_H
#include "Map.h"
#include "Individual.h"
#include "Header.h"

class GeneticAlgorithm
{
	private:
		vector <Individual> population;
		Map map;
		int stopCounter;
		Individual bestIndividual;

	public:
		GeneticAlgorithm();

		virtual ~GeneticAlgorithm();

		Individual findSolution();

		void generatePopulation();

		void printMap() const;

		Individual* crossover(const Individual& firstIndividual, const Individual& secondIndividual);

		void crossoverPopulation();

		void selectParents(vector<Individual>& nextGenProgenitors);

		void mutation(Individual& individual);

		void printPopulation() const;

		void calculatePopulationFitness();

		void calculateFitness(Individual& individual);

		int manhattanXY(const Individual& individual) const;

		int manhattanYX(const Individual& individual) const;

		int diagonal(const Individual& individual) const;

		bool posInRange(int r, int c) const;

		bool stopFunction(Individual& individual);
};

#endif // __GENETIC_ALGORITHM_H