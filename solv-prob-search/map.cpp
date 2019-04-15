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
        this->_rows = stoi(line);
        getline(mapFile,line);
        this->_cols = stoi(line);

        this->_map = new char*[this->_rows]();

        for(int idx = 0; idx < this->_rows; idx++)
        {
            this->_map[idx] = new char[this->_cols]();
        }

        int r = 0;
        int c = 0;

        while(mapFile.get(this->_map[r][c]))
        {
            if('\n' != this->_map[r][c])
            {
                c++;
                if(this->_cols <= c)
                {
                    r++;
                    c = 0;
                    if(this->_rows <= r)
                    {
                        break;
                    }
                }
            }
        }

        mapFile.close();
    }
}
