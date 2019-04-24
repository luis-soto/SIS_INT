#include "Individual.h"

Individual::Individual(){
	points = 0;
}


Individual::~Individual(){
}

void Individual::setGene(pair<int, int> valGene, int pos) {
	if (pos >= 0 && pos < numberOfGenes) {
		genes[pos] = valGene;
	}
}

void Individual::setGenes(vector<pair <int, int>> valGenes) {
	genes = valGenes;
}


pair <int, int> Individual::getGene(int pos) {
	return genes[pos];
}

vector<pair <int, int>> Individual::getGenes() {
	return genes;
}

void Individual::setPoints(int valPoints) {
	this->points = valPoints;
}

int Individual::getPoints() {
	return this->points;
}

void Individual::printIndividual() {
	for (int i = 0; i < (int)genes.size(); i++) {
		std::cout << "(" << genes[i].first << "," << genes[i].second << ")" << " ";
	}
	std::cout << "Points: " << getPoints() << endl;
}