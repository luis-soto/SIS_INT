#ifndef MAP_H
#define MAP_H

// Class that define the map
class Map
{
    private:
        char** _map;
        int _rows;
        int _cols;

    public:
    Map();

    ~Map()
    {
        
    }

    int getRows() const
    {
        return this->_rows;
    }

    int getCols() const
    {
        return this->_cols;
    }

    char getItemByPos(int r, int c) const
    {
        char ret;
        if((0 <= r) && (0 <= c) && (this->_rows > r) && (this->_cols > c))
        {
            ret = this->_map[r][c];
        }
        else
        {
            ret = '*';
        }
        return ret;
    }
};

#endif // MAP_H