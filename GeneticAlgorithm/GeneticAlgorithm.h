#pragma once
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

		void generatePopulation();

		void printMap();

		Individual* crossover(Individual firstIndividual, Individual secondIndividual);

		void crossoverPopulation();

		void printPopulation();

		int manhattanXY(Individual individual);

		int manhattanYX(Individual individual);

		int stopFunction(Individual individual);
};

