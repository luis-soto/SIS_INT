#include "Map.h"

Map::Map(){
	matrixMap = nullptr;
	nColumns = 0;
	nRows = 0;
    readFile();
}

Map::~Map(){
    for(int i=0; i<nRows; i++){
        delete(matrixMap[i]);
    }
    delete(matrixMap);
}

void Map::allocateMatrixMap(){
	matrixMap = new char*[nRows];
    for(int i=0; i<nRows;i++){
		matrixMap[i] = new char[nColumns];
    }
}

void Map::readFile(){
    FILE *f = nullptr;
	errno_t error;
    do{
        error = fopen_s(&f,"Env.txt","r");
    }while(error != 0);
	if (f != nullptr) {
		fscanf_s(f, "%d\n", &nRows);
		fscanf_s(f, "%d\n", &nColumns);
		allocateMatrixMap();
		for (int i = 0; i < nRows; i++) {
			for (int j = 0; j < nColumns; j++) {
				fscanf_s(f, "%c", &matrixMap[i][j], 1);
				if (strchr("^<>v", matrixMap[i][j]) != nullptr)
					origin = make_pair(j, i);
				else if (matrixMap[i][j] == 'x')
					destiny = make_pair(j, i);
			}
			fscanf_s(f, "\n");
		}
		fclose(f);
	}
}

void Map::printMap(){
    for(int i=0;i<nRows;i++){
        for(int j=0;j<nColumns;j++){
            cout << matrixMap[i][j];
        }
        cout << endl;
    }
}

int Map::getNRows(){
    return nRows;
}

int Map::getNColumns(){
    return nColumns;
}

pair<int, int> Map::getOrigin() {
	return origin;
}

pair<int, int> Map::getDestiny() {
	return destiny;
}

char Map::getMatrixMap(int valX, int valY){
    return matrixMap[valY][valX];
}
