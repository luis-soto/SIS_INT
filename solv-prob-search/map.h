#ifndef MAP_H
#define MAP_H

// Class that define the map
class Map
{
    private:
        char **map;
        int Rows;
        int Cols;

    public:
    Map();

    ~Map()
    {
        
    }

    void Display();

    int GetRows() const
    {
        return this->Rows;
    }

    int GetCols() const
    {
        return this->Cols;
    }

    char GetItemByPos(int r, int c) const
    {
        return this->map[r][c];
    }
};

#endif // MAP_H