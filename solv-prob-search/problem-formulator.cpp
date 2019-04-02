#include "problem-formulator.h"
#include <iostream>

Direction All[] = {Direction::NW, Direction::N, Direction::NE, Direction::E, Direction::SE,
                   Direction::S, Direction::SW, Direction::W};

// -------------------------------------------------------------------------------------------------
ProblemFormulator::ProblemFormulator()
{
    this->initialState = new State;
    this->goalState = new State;
    this->map = new Map();
    this->graphModel = new Graph(this->map->GetRows(), this->map->GetCols());
    this->GenerateGraph();
}

// -------------------------------------------------------------------------------------------------
void ProblemFormulator::GenerateGraph()
{
    for(int x; x < this->map->GetRows(); x++)
    {
        for(int y = 0; y < this->map->GetCols(); y++)
        {
            char ch = this->map->GetItemByPos(x,y);
            if( '*' != ch)
            {
                if('.' != ch)
                {
                    if('x' != ch)
                    {
                        this->initialState->x = x;
                        this->initialState->y = y;
                        switch(ch)
                        {
                            case '<':
                                this->initialState->dir = Direction::W;
                                break;

                            case '>':
                                this->initialState->dir = Direction::E;
                                break;

                            case 'v':
                                this->initialState->dir = Direction::S;
                                break;

                            case '^':
                                this->initialState->dir = Direction::N;
                                break;

                            case '%':
                                this->initialState->dir = Direction::NW;
                                break;

                            case '\\':
                                this->initialState->dir = Direction::SE;
                                break;

                            case '/':
                                this->initialState->dir = Direction::SW;
                                break;

                            case '\?':
                                this->initialState->dir = Direction::NE;
                                break;
                        }
                    }
                    else
                    {
                        this->goalState->x = x;
                        this->goalState->y = y;
                        this->goalState->dir = Direction::DEFAULT;
                    }
                }

                for(const auto dir : All)
                {
                    switch(dir)
                    {
                        case Direction::NW:
                            if('*' != this->map->GetItemByPos(x-1,y-1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x-1, y-1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::W);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::N);
                            break;

                        case Direction::N:
                            if('*' != this->map->GetItemByPos(x-1,y))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x-1, y,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::NW);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::NE);
                            break;

                        case Direction::NE:
                            if('*' != this->map->GetItemByPos(x-1,y+1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x-1, y+1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::N);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::E);
                            break;

                        case Direction::E:
                            if('*' != this->map->GetItemByPos(x,y+1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x, y+1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::NE);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::SE);
                            break;

                        case Direction::SE:
                            if('*' != this->map->GetItemByPos(x+1,y+1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x+1, y+1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::E);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::S);
                            break;
                            
                        case Direction::S:
                            if('*' != this->map->GetItemByPos(x+1,y))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x+1, y,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::SW);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::SE);
                            break;

                        case Direction::SW:
                            if('*' != this->map->GetItemByPos(x+1,y-1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x+1, y-1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::W);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::S);
                            break;

                        case Direction::W:
                            if('*' != this->map->GetItemByPos(x,y-1))
                            {
                                this->graphModel->JoinEdge(x, y, dir, x, y-1,dir);
                            }
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::SW);
                            this->graphModel->JoinEdge(x, y, dir, x, y,Direction::NW);
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

int main()
{
    ProblemFormulator problemFormulator;
    cout << "Apparently implementation is OK..." << endl;
    return 0;
}