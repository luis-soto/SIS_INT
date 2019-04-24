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

		void printMap();

		Individual* crossover(Individual firstIndividual, Individual secondIndividual);

		void crossoverPopulation();

		static bool comparePoints(Individual individual1, Individual individual2);

		void selectParents();

		void mutation(Individual individual);

		void printPopulation();

		void calculatePopulationFitness();

		int calculateFitness(Individual individual);

		int manhattanXY(Individual individual);

		int manhattanYX(Individual individual);

		int diagonal(Individual individual);

		bool stopFunction(Individual individual);
};

#endif // __GENETIC_ALGORITHM_H