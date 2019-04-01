#include "map.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// -------------------------------------------------------------------------------------------------
Map::Map()
{
    ifstream mapFile("./map.txt");

    if(!mapFile)
    {
        cerr << "Unable to open file map.txt" << endl;
        exit(1);
    }
    else
    {
        string line;
        char ch;

        getline(mapFile,line);
        this->Rows = stoi(line);
        getline(mapFile,line);
        this->Cols = stoi(line);

        this->map = new char*[Rows]();
            
        for(int idx = 0; idx < Rows; idx++)
        {
            this->map[idx] = new char[Cols]();
        }

        int r = 0;
        int c = 0;

        while(mapFile.get(this->map[r][c]))
        {
            if('\n' != this->map[r][c])
            {
                c++;
                if(this->Cols <= c)
                {
                    r++;
                    c = 0;
                    if(this->Rows <= r)
                    {
                        break;
                    }
                }
            }
        }

        mapFile.close();
    }
}