#ifndef __INDIVIDUAL_H
#define __INDIVIDUAL_H

#include "Header.h"

class Individual
{
	private:
		vector<pair <int, int>> genes = vector<pair <int, int>>(numberOfGenes);
		int points;

	public:
		Individual();

		virtual ~Individual();

		void setGene(pair<int, int> valGene, int pos);

		void setGenes(vector<pair <int, int>> valGenes);

		pair <int, int> getGene(int pos);

		vector<pair <int, int>> getGenes();

		void setPoints(int valPoints);

		int getPoints();

		void printIndividual();
};

#endif // __INDIVIDUAL_H