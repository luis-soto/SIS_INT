#ifndef __MAP_DISPLAYER_H
#define __MAP_DISPLAYER_H

#include "map.h"
#include "tree.h"
#include <vector>

class MapDisplayer
{
    private:
        char** _map;
        int _rows;
        int _cols;
        int _rowPos;
        int _colPos;

    public:
        MapDisplayer(Map* map);

        ~MapDisplayer();

        void showSolution(std::vector<Action> solution);

        void displayMap();

        void turnRight();

        void turnLeft();

        void goFront();
};

#endif // __MAP_DISPLAYER_H