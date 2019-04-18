#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm() {
	stopCounter = 1;
}


GeneticAlgorithm::~GeneticAlgorithm() {
}

void GeneticAlgorithm::generatePopulation() {
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < sizeOfGeneration; i++) {
		Individual* individual = new Individual();
		for (int j = 0; j < numberOfGenes; j++) {
			int randomX, randomY;
			do {
				randomX = rand() % map.getNColumns();
				randomY = rand() % map.getNRows();
			} while (map.getMatrixMap(randomX, randomY) == '*');
			individual->setGene(make_pair(randomX, randomY), j);
		}
		population.insert(population.begin(), *individual);
	}
}

void GeneticAlgorithm::printMap() {
	map.printMap();
}

Individual* GeneticAlgorithm::crossover(Individual firstIndividual, Individual secondIndividual) {
	int random = rand() % numberOfGenes;
	Individual* resultIndividual = new Individual();
	resultIndividual->setGenes(secondIndividual.getGenes());
	resultIndividual->setGene(firstIndividual.getGene(random), random);
	return resultIndividual;
}

void GeneticAlgorithm::crossoverPopulation() {
	int random0, random1;
	vector <Individual> newGeneration;
	newGeneration.insert(newGeneration.begin(), population.begin(), population.begin()+numberOfRemainingIndividuals);
	for (int i = 0; i < (sizeOfGeneration - numberOfRemainingIndividuals); i++) {
		do {
			random0 = rand() % numberOfRemainingIndividuals;
			random1 = rand() % numberOfRemainingIndividuals;
		} while (random0 == random1);
		Individual* resultIndividual = crossover(population[random0], population[random1]);
		newGeneration.push_back(*resultIndividual);
	}
	population.insert(population.begin(), newGeneration.begin(), newGeneration.end());
}

void GeneticAlgorithm::printPopulation() {
	for (int i = 0; i < sizeOfGeneration; i++) {
		population[i].printIndividual();
	}
}

int GeneticAlgorithm::manhattanXY(Individual individual) {
	vector<pair<int, int>> points;
	points.push_back(map.getOrigin());
	for (int i = 0; i < (int)individual.getGenes().size(); i++) {
		points.push_back(individual.getGenes()[i]);
	}
	points.push_back(map.getDestiny());
	int cells = 1, obstacles = 0;
	for (int i = 0; i < ((int)points.size() - 1); i++) {
		int deltaX = points[i + 1].first - points[i].first;
		int x;
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, points[i].second) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
		int deltaY = points[i + 1].second - points[i].second;
		int y;
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)pow(cells, (obstacles + 1));
}

int GeneticAlgorithm::manhattanYX(Individual individual) {
	vector<pair<int, int>> points;
	points.push_back(map.getOrigin());
	for (int i = 0; i < (int)individual.getGenes().size(); i++) {
		points.push_back(individual.getGenes()[i]);
	}
	points.push_back(map.getDestiny());
	int cells = 1, obstacles = 0;
	for (int i = 0; i < ((int)points.size() - 1); i++) {
		int deltaY = points[i + 1].second - points[i].second;
		int y;
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(points[i].first, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
		int deltaX = points[i + 1].first - points[i].first;
		int x;
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)pow(cells, (obstacles + 1));
}

int GeneticAlgorithm::stopFunction(Individual individual) {
	if (individual.getPoints() < bestIndividual.getPoints()) {
		stopCounter = 1;
		bestIndividual = individual;
		return 0;
	}
	else if (stopCounter == stopCriterion) {
		return 1;
	}
	stopCounter++;
	return 0;
}