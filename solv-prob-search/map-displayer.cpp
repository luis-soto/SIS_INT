#include "map-displayer.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
// -------------------------------------------------------------------------------------------------
MapDisplayer::MapDisplayer(Map* map)
{
    this->_rows = map->getRows();
    this->_cols = map->getCols();

    this->_map = new char*[this->_rows]();

    for(int idx = 0; this->_rows > idx; idx++)
    {
        this->_map[idx] = new char[this->_cols]();
    }

    for(int r = 0; this->_rows > r; r++)
    {
        for(int c = 0; this->_cols > c; c++)
        {
            this->_map[r][c] = map->getItemByPos(r, c);
            if((map->getItemByPos(r, c) != 'x') && (map->getItemByPos(r, c) != '.') &&
               (map->getItemByPos(r, c) != '*'))
            {
                this->_colPos = c;
                this->_rowPos = r;
            }
        }
    }
}
// -------------------------------------------------------------------------------------------------
MapDisplayer::~MapDisplayer()
{
    for(int idx = 0; this->_rows > idx; idx++)
    {
        delete this->_map[idx];
    }
    delete this->_map;
}
// -------------------------------------------------------------------------------------------------
void MapDisplayer::showSolution(vector<Action> solution)
{
    int idx = solution.size()-1;

    while(0 <= idx)
    {
        if(Action::FRONT == solution[idx])
        {
            if((this->_cols > this->_colPos) && (this->_rows > this->_rowPos))
            {
                this->goFront();
            }
        }
        else
        {
            if(Action::TURN_LEFT == solution[idx])
            {
                this->turnLeft();
            }
            else
            {
                if(Action::TURN_RIGHT == solution[idx])
                {
                    this->turnRight();
                }
            }
        }
        this->displayMap();
        sleep_for(seconds(1));
        idx--;
    }
}
// -------------------------------------------------------------------------------------------------
void MapDisplayer::displayMap()
{
    for(int r = 0; this->_rows > r; r++)
    {
        for(int c = 0; this->_cols > c; c++)
        {
            cout << this->_map[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------------------------------------------------------------------------------
void MapDisplayer::goFront()
{
    switch(this->_map[this->_rowPos][this->_colPos])
    {
        case '<':
            this->_map[this->_rowPos][this->_colPos-1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos-1;
            break;

        case '>':
            this->_map[this->_rowPos][this->_colPos+1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos+1;
            break;

        case 'v':
            this->_map[this->_rowPos+1][this->_colPos] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_rowPos = this->_rowPos+1;
            break;

        case '^':
            this->_map[this->_rowPos-1][this->_colPos] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_rowPos = this->_rowPos-1;
            break;

        case '%':
            this->_map[this->_rowPos-1][this->_colPos-1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos-1;
            this->_rowPos = this->_rowPos-1;
            break;

        case '\\':
            this->_map[this->_rowPos+1][this->_colPos+1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos+1;
            this->_rowPos = this->_rowPos+1;
            break;

        case '/':
            this->_map[this->_rowPos+1][this->_colPos-1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos-1;
            this->_rowPos = this->_rowPos+1;
            break;

        case '\?':
            this->_map[this->_rowPos-1][this->_colPos+1] = this->_map[this->_rowPos][this->_colPos];
            this->_map[this->_rowPos][this->_colPos] = '.';
            this->_colPos = this->_colPos+1;
            this->_rowPos = this->_rowPos-1;
            break;
    }
}
// -------------------------------------------------------------------------------------------------
void MapDisplayer::turnLeft()
{
    switch(this->_map[this->_rowPos][this->_colPos])
    {
        case '<':
            this->_map[this->_rowPos][this->_colPos] = '/';
            break;

        case '>':
            this->_map[this->_rowPos][this->_colPos] = '\?';
            break;

        case 'v':
            this->_map[this->_rowPos][this->_colPos] = '\\';
            break;

        case '^':
            this->_map[this->_rowPos][this->_colPos] = '%';
            break;

        case '%':
            this->_map[this->_rowPos][this->_colPos] = '<';
            break;

        case '\\':
            this->_map[this->_rowPos][this->_colPos] = '>';
            break;

        case '/':
            this->_map[this->_rowPos][this->_colPos] = 'v';
            break;

        case '\?':
            this->_map[this->_rowPos][this->_colPos] = '^';
            break;
    }
}
// -------------------------------------------------------------------------------------------------
void MapDisplayer::turnRight()
{
    switch(this->_map[this->_rowPos][this->_colPos])
    {
        case '<':
            this->_map[this->_rowPos][this->_colPos] = '%';
            break;

        case '>':
            this->_map[this->_rowPos][this->_colPos] = '\\';
            break;

        case 'v':
            this->_map[this->_rowPos][this->_colPos] = '/';
            break;

        case '^':
            this->_map[this->_rowPos][this->_colPos] = '\?';
            break;

        case '%':
            this->_map[this->_rowPos][this->_colPos] = '^';
            break;

        case '\\':
            this->_map[this->_rowPos][this->_colPos] = 'v';
            break;

        case '/':
            this->_map[this->_rowPos][this->_colPos] = '<';
            break;

        case '\?':
            this->_map[this->_rowPos][this->_colPos] = '>';
            break;
    }
}
// -------------------------------------------------------------------------------------------------