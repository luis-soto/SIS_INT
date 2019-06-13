#include "GeneticAlgorithm.h"
#include <math.h>
#include <algorithm>  

// -------------------------------------------------------------------------------------------------
GeneticAlgorithm::GeneticAlgorithm()
{
	stopCounter = 1;
}
// -------------------------------------------------------------------------------------------------
GeneticAlgorithm::~GeneticAlgorithm()
{

}
// -------------------------------------------------------------------------------------------------
Individual GeneticAlgorithm::findSolution()
{
	this->generatePopulation();
	do
	{
		this->calculatePopulationFitness();
		this->selectParents();
		this->crossoverPopulation();
	}while(!this->stopFunction(this->population.front()));
	return this->bestIndividual;
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::generatePopulation()
{
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
	this->calculatePopulationFitness();
	this->bestIndividual = this->population.front();
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::printMap()
{
	map.printMap();
}
// -------------------------------------------------------------------------------------------------
Individual* GeneticAlgorithm::crossover(Individual firstIndividual, Individual secondIndividual)
{
	int random = rand() % numberOfGenes;
	Individual* resultIndividual = new Individual();
	resultIndividual->setGenes(secondIndividual.getGenes());
	resultIndividual->setGene(firstIndividual.getGene(random), random);
	return resultIndividual;
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::crossoverPopulation()
{
	int random0, random1;
	vector <Individual> newGeneration;
	newGeneration.insert(newGeneration.begin(), population.begin(), population.begin() + numberOfRemainingIndividuals);
	for (int i = 0; i < (sizeOfGeneration - numberOfRemainingIndividuals); i++) {
		do {
			random0 = rand() % numberOfRemainingIndividuals;
			random1 = rand() % numberOfRemainingIndividuals;
		} while (random0 == random1);
		Individual * resultIndividual = crossover(population[random0], population[random1]);
		newGeneration.push_back(*resultIndividual);
	}
	population.insert(population.begin(), newGeneration.begin(), newGeneration.end());
	this->calculatePopulationFitness();
	this->selectParents();
}
// -------------------------------------------------------------------------------------------------
bool GeneticAlgorithm::comparePoints(Individual individual1, Individual individual2)
{
	return (individual1.getPoints() < individual2.getPoints());
}
//--------------------------------------------------------------------------------------------------
void GeneticAlgorithm::selectParents()
{
	vector<Individual> nextGenProgenitors;
	sort(population.begin(), population.end(), comparePoints);
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::mutation(Individual individual)
{
	if(0 == (rand() % 100))
	{
		int geneMutated = rand() % 3;
		pair<int, int> mutatedGene(rand() % map.getNRows(), rand() % map.getNColumns());
		individual.setGene(mutatedGene, geneMutated);
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::printPopulation()
{
	for (int i = 0; i < sizeOfGeneration; i++)
	{
		population[i].printIndividual();
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::calculatePopulationFitness()
{
	for(int i = 0; i < sizeOfGeneration; i++){
		population[i].setPoints(this->calculateFitness(population[i]));
	}
}
// -------------------------------------------------------------------------------------------------
int GeneticAlgorithm::calculateFitness(Individual individual)
{
	vector<int> fitnessFunction;
	fitnessFunction.push_back(manhattanXY(individual));
	fitnessFunction.push_back(manhattanYX(individual));
	//fitnessFunction.push_back(diagonal(individual));
	long long int min = fitnessFunction[0];
	for(int i=1;i<(int)fitnessFunction.size();i++)
	{
		if(fitnessFunction[i] < min)
		{
			min = fitnessFunction[i];
		}
	}
	return min;
}
// -------------------------------------------------------------------------------------------------
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
		int deltaY = points[i + 1].second - points[i].second;
		int y;
		if (points[i + 1].second == points[i].second && points[i + 1].first == points[i].first) {
			return (int)((pow(2, 32) - 1) / 2);
		}
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, points[i].second) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)(pow(cells, 3) + pow(obstacles, 4));
}
// -------------------------------------------------------------------------------------------------
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
		int deltaX = points[i + 1].first - points[i].first;
		int x;
		if (points[i + 1].second == points[i].second && points[i + 1].first == points[i].first) {
			return (int)((pow(2, 32) - 1) / 2);
		}
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(points[i].first, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX)) {
			cells += manhattanCellPoint;
			if (map.getMatrixMap(x, y) == '*') {
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)(pow(cells, 3) + pow(obstacles, 4));
}
// -------------------------------------------------------------------------------------------------
int GeneticAlgorithm::diagonal(Individual individual)
{
	vector<pair<int, int>> points;
	points.push_back(map.getOrigin());
	for (int i = 0; i < (int)individual.getGenes().size(); i++) {
		points.push_back(individual.getGenes()[i]);
	}
	points.push_back(map.getDestiny());
	int cells = 0, obstacles = 0;
	for (int i = 0; i < ((int)points.size() - 1); i++) {
		int deltaX = points[i + 1].first - points[i].first;
		int deltaY = points[i + 1].second - points[i].second;
		int x = points[i].first;
		int y = points[i].second;
		if (deltaX == 0 || deltaY == 0) {
			return (int)((pow(2, 32)-1)/2);
		}
		while (x > 0 && x < map.getNRows() && y > 0 && y < map.getNColumns()){
			cells += diagonalCellPoint;
			if (map.getMatrixMap(x, y) == '*') {
				obstacles += diagonalObstaclePoint;
			}
			else if (map.getMatrixMap(x, y) == 'x') {
				cells -= diagonalGoalPoint;
				break;
			}
			x += deltaX / abs(deltaX);
			y += deltaY / abs(deltaY);
		}
	}
	return (int)(pow(cells, 3) + pow(obstacles, 4));
}
// -------------------------------------------------------------------------------------------------
bool GeneticAlgorithm::stopFunction(Individual individual) {
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
// -------------------------------------------------------------------------------------------------