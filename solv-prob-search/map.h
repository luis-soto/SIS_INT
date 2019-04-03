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
        char ret;
        if((0 <= r) && (0 <= c) && (this->Rows > r) && (this->Cols > c))
        {
            ret = this->map[r][c];
        }
        else
        {
            ret = '*';
        }
        return ret;
    }
};

#endif // MAP_H