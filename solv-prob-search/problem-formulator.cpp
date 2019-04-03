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
Direction DetermineDirection(char ch)
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
                        this->initialState->SetX(x);
                        this->initialState->SetY(x);
                        this->initialState->SetDir(DetermineDirection(ch));
                    }
                    else
                    {
                        this->goalState->SetX(x);
                        this->goalState->SetY(y);
                        this->goalState->SetDir(Direction::DEFAULT);
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

// -------------------------------------------------------------------------------------------------
int main()
{
    ProblemFormulator problemFormulator;
    cout << "Apparently implementation is OK..." << endl;
    return 0;
}