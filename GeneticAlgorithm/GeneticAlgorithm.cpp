#include "GeneticAlgorithm.h"
#include <math>

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
	do
	{
		this->calculatePopulationFitness();
		this->crossoverPopulation();
	}
	while(!this->stopFunction(this->population.front()));
	return this->bestIndividual;
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::generatePopulation()
{
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < sizeOfGeneration; i++)
	{
		Individual* individual = new Individual();
		for (int j = 0; j < numberOfGenes; j++)
		{
			int randomX, randomY;
			do
			{
				randomX = rand() % map.getNColumns();
				randomY = rand() % map.getNRows();
			}
			while (map.getMatrixMap(randomX, randomY) == '*');

			individual->setGene(make_pair(randomX, randomY), j);
		}
		population.insert(population.begin(), *individual);
	}
	this->bestIndividual = this->population.front();
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::printMap() const
{
	map.printMap();
}
// -------------------------------------------------------------------------------------------------
Individual* GeneticAlgorithm::crossover(const Individual& firstIndividual, const Individual& secondIndividual)
{
	int const random = rand() % (numberOfGenes-1);
	Individual* resultIndividual = new Individual();
	resultIndividual->setGenes(secondIndividual.getGenes());
	for(int it = 0; random > it; it++)
	{
		resultIndividual->setGene(firstIndividual.getGene(it), it);
	}
	return resultIndividual;
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::crossoverPopulation()
{
	vector<Individual> newGenProgenitors;
	this->selectParents(newGenProgenitors);
	this->population.clear();
	while((sizeOfGeneration - numberOfRemainingIndividuals) > this->population.size())
	{
		int random0, random1;

		do
		{
			random0 = rand() % numberOfRemainingIndividuals;
			random1 = rand() % numberOfRemainingIndividuals;
		}
		while (random0 == random1);

		Individual* resultIndividual = crossover(newGenProgenitors[random0], newGenProgenitors[random1]);
		this->mutation(*resultIndividual);
		this->population.push_back(*resultIndividual);
	}
	population.insert(population.begin(), newGenProgenitors.begin(), newGenProgenitors.end());
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::selectParents(vector<Individual>& nextGenProgenitors)
{
	while((!this->population.empty()) && (numberOfRemainingIndividuals > nextGenProgenitors.size()))
	{
		int idx = 0;
		Individual min = this->population.front();
		for(Individual individual : this->population)
		{
			idx++;
			if(individual.getPoints() < min.getPoints())
			{
				min = individual;
			}
		}
		newGenProgenitors.push_back(min);
		this->population.erase(this->population.begin()+idx-1);
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::mutation(Individual& individual)
{
	if(0 == (rand() % 100))
	{
		int geneMutated = rand() % 3;
		pair<int, int> mutatedGene(rand() % map.getNRows(), rand() % map.getNColumns());
		Individual->setGene(mutatedGene, geneMutated);
	}
	else
	{
		// No mutation
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::printPopulation() const
{
	for (int i = 0; i < sizeOfGeneration; i++)
	{
		population[i].printIndividual();
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::calculatePopulationFitness()
{
	for(auto& individual : this->population)
	{
		this->calculateFitness(Individual);
	}
}
// -------------------------------------------------------------------------------------------------
void GeneticAlgorithm::calculateFitness(Individual& individual)
{
	vector<int> fitnessFunction;
	fitnessFunction.push_back(this->manhattanXY(individual));
	fitnessFunction.push_back(this->manhattanYX(individual));
	fitnessFunction.push_back(this->diagonal(individual));
	
	int min = fitnessFunction[0];
	for(int fitness : fitnessFunction)
	{
		if(fitness < min)
		{
			min = fitness;
		}
	}
	individual.setPoints(min);
}
// -------------------------------------------------------------------------------------------------
int GeneticAlgorithm::manhattanXY(const Individual& individual) const
{
	vector<pair<int, int>> points;
	points.push_back(map.getOrigin());
	for (int i = 0; i < (int)individual.getGenes().size(); i++)
	{
		points.push_back(individual.getGenes()[i]);
	}
	points.push_back(map.getDestiny());
	int cells = 1, obstacles = 0;
	for (int i = 0; i < ((int)points.size() - 1); i++)
	{
		int deltaX = points[i + 1].first - points[i].first;
		int x;
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX))
		{
			cells += manhattanCellPoint;
			if ('*' == map.getMatrixMap(x, points[i].second))
			{
				obstacles += manhattanObstaclePoint;
			}
		}
		int deltaY = points[i + 1].second - points[i].second;
		int y;
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY))
		{
			cells += manhattanCellPoint;
			if ('*' == map.getMatrixMap(x, y))
			{
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)pow(cells, (obstacles + 1));
}
// -------------------------------------------------------------------------------------------------
int GeneticAlgorithm::manhattanYX(const Individual& individual) const
{
	vector<pair<int, int>> points;
	points.push_back(map.getOrigin());
	for (int i = 0; i < (int)individual.getGenes().size(); i++)
	{
		points.push_back(individual.getGenes()[i]);
	}
	points.push_back(map.getDestiny());
	int cells = 1, obstacles = 0;
	for (int i = 0; i < ((int)points.size() - 1); i++)
	{
		int deltaY = points[i + 1].second - points[i].second;
		int y;
		for (y = points[i].second; y != points[i + 1].second; y += deltaY / abs(deltaY))
		{
			cells += manhattanCellPoint;
			if ('*' == map.getMatrixMap(points[i].first, y))
			{
				obstacles += manhattanObstaclePoint;
			}
		}
		int deltaX = points[i + 1].first - points[i].first;
		int x;
		for (x = points[i].first; x != points[i + 1].first; x += deltaX / abs(deltaX))
		{
			cells += manhattanCellPoint;
			if ('*' == map.getMatrixMap(x, y))
			{
				obstacles += manhattanObstaclePoint;
			}
		}
	}
	return (int)pow(cells, (obstacles + 1));
}
// -------------------------------------------------------------------------------------------------
int GeneticAlgorithm::diagonal(const Individual& individual) const
{
	int ret = 0;

	for(int idx = 0; numberOfGenes > idx; idx++)
	{
		int diag[numDiagonal];
		diag[0] = 0;
		diag[1] = 0;
		diag[2] = 0;
		diag[3] = 0;
		pair<int, int> actualGene = individual.getGene(idx);
		int r, c;

		int numDiag = 0;

		while (numDiagonal > numDiag)
		{
			r = actualGene.first;
			c = actualGene.second;

			while (this->posInRange(r, c))
			{
				if('x' == map.getMatrixMap(r, c))
				{
					diag[numDiag] += diagonalGoalPoint;
				}
				else
				{
					if ('*' == map.getMatrixMap(r, c))
					{
						diag[numDiag] += diagonalObstaclePoint;
					}

				}

				if (0 == numDiag)
				{
					r--;
					c--;
				}

				if (1 == numDiag)
				{
					r++;
					c--;
				}

				if (2 == numDiag)
				{
					r--;
					c++;
				}

				if (3 == numDiag)
				{
					r++;
					c++;
				}

			}
		numDiag++;
		}

		int min = diag[0];
		for(int idx = 1; numDiagonal > idx; idx++)
		{
			if (diag[idx] < min)
			{
				min = diag[idx];
			}

		}

		ret += min;
	}

	return ret;
}
// -------------------------------------------------------------------------------------------------
bool GeneticAlgorithm::posInRange(int r, int c)
{
	bool ret = false;

	if((0 <= r) && (map.getNRows() > r) && (0 <= c) && (map.getNColumns() > c))
	{
		ret = true;
	}

	return ret;
}
// -------------------------------------------------------------------------------------------------
bool GeneticAlgorithm::stopFunction(Individual& individual)
{
	bool ret = false;
	if (individual.getPoints() < this->bestIndividual.getPoints())
	{
		stopCounter = 1;
		this->bestIndividual = individual;
	}
	else 
	{
		if (stopCounter == stopCriterion)
		{
			ret = true;
		}
	}
	stopCounter++;

	return ret;
}
// -------------------------------------------------------------------------------------------------