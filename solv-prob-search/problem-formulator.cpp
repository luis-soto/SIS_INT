#include "problem-formulator.h"

Direction All[] = {Direction::NW, Direction::N, Direction::NE, Direction::E, Direction::SE,
                   Direction::S, Direction::SW, Direction::W};

// -------------------------------------------------------------------------------------------------
ProblemFormulator::ProblemFormulator()
{
    this->_initialState = new State;
    this->_goalState = new State;
    this->_map = new Map();
    this->_graphModel = new Graph(this->_map->getRows(), this->_map->getCols());
    this->generateGraph();
}

// -------------------------------------------------------------------------------------------------
Direction determineDirection(char ch)
{
    Direction dir;
    
    switch(ch)
    {
        case '<':
            dir = Direction::W;
            break;

        case '>':
            dir = Direction::E;
            break;

        case 'v':
            dir = Direction::S;
            break;

        case '^':
            dir = Direction::N;
            break;

        case '%':
            dir = Direction::NW;
            break;

        case '\\':
            dir = Direction::SE;
            break;

        case '/':
            dir = Direction::SW;
            break;

        case '\?':
            dir = Direction::NE;
            break;
    }

    return dir;
}

// -------------------------------------------------------------------------------------------------
void ProblemFormulator::generateGraph()
{
    for(int x = 0; x < this->_map->getRows(); x++)
    {
        for(int y = 0; y < this->_map->getCols(); y++)
        {
            char ch = this->_map->getItemByPos(x,y);
            if( '*' != ch)
            {
                if('.' != ch)
                {
                    if('x' != ch)
                    {
                        this->_initialState->setX(x);
                        this->_initialState->setY(y);
                        this->_initialState->setDir(determineDirection(ch));
                    }
                    else
                    {
                        this->_goalState->setX(x);
                        this->_goalState->setY(y);
                        this->_goalState->setDir(Direction::DEFAULT);
                    }
                }

                for(const auto dir : All)
                {
                    switch(dir)
                    {
                        case Direction::NW:
                            if('*' != this->_map->getItemByPos(x-1,y-1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x-1, y-1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::W);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::N);
                            break;

                        case Direction::N:
                            if('*' != this->_map->getItemByPos(x-1,y))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x-1, y,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::NW);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::NE);
                            break;

                        case Direction::NE:
                            if('*' != this->_map->getItemByPos(x-1,y+1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x-1, y+1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::N);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::E);
                            break;

                        case Direction::E:
                            if('*' != this->_map->getItemByPos(x,y+1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x, y+1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::NE);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::SE);
                            break;

                        case Direction::SE:
                            if('*' != this->_map->getItemByPos(x+1,y+1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x+1, y+1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::E);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::S);
                            break;
                            
                        case Direction::S:
                            if('*' != this->_map->getItemByPos(x+1,y))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x+1, y,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::SW);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::SE);
                            break;

                        case Direction::SW:
                            if('*' != this->_map->getItemByPos(x+1,y-1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x+1, y-1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::W);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::S);
                            break;

                        case Direction::W:
                            if('*' != this->_map->getItemByPos(x,y-1))
                            {
                                this->_graphModel->joinEdge(x, y, dir, x, y-1,dir);
                            }
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::SW);
                            this->_graphModel->joinEdge(x, y, dir, x, y,Direction::NW);
                            break;
                    }
                }
            }
            else
            {
                // (x, y) is not a reachable coordinate
            }
            
        }
    }
}