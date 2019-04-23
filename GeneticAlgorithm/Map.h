#ifndef __MAP_H
#define __MAP_H
#include "Header.h"

class Map
{
    protected:
        int nColumns, nRows;
		pair<int, int> origin, destiny;
        char **matrixMap;

    public:
        //Executa a leitura do arquivo txt
        Map();

        virtual ~Map();

        //Aloca uma matriz de acordo com quantidade de linhas e colunas do mapa
        void allocateMatrixMap();

        //Realiza leitura do arquivo txt, obtendo a matrix mapa e a quantidade de linhas e colunas
        void readFile();

        //Imprime o mapa
        void printMap();

        int getNRows();

        int getNColumns();

		pair<int, int> getOrigin();

		pair<int, int> getDestiny();

        //Retorna o caractere da matriz mapa de acordo com os valores de entrada
        char getMatrixMap(int valX, int valY);

};

#endif // __MAP_H