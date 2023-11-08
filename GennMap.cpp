#include "GenMap.h"

Map::Map()
{
	map = nullptr;
    cols = 0;
    rows = 0;
    Boom = 0;
}

Map::Map(int col, int row)
{
    cols = col;
    rows = row;

	map = new pixel*[rows+2];
    for (int i = 0; i <= rows+1; i++)
    {
        map[i] = new pixel[cols+2];
        for (int j = 0; j <= cols+1; j++)
        {
            if ( (i > 0 && j > 0) && (i < rows+1 && j < cols+1) ) 
            {
                map[i][j].data = 0;
            }
            else map[i][j].data = -1;
            map[i][j].status = false; // ô chưa được chưa mở
        }
    }
}

int Map::countBoomOnPixel(int i, int j) {
    int count = 0;

    if (map[i-1][j-1].data  == BOOM ) count++;
    if (map[i-1][j].data    == BOOM ) count++;
    if (map[i-1][j+1].data  == BOOM ) count++;
    if (map[i][j-1].data    == BOOM ) count++;
    if (map[i][j+1].data    == BOOM ) count++;
    if (map[i+1][j-1].data  == BOOM ) count++;
    if (map[i+1][j].data    == BOOM ) count++;
    if (map[i+1][j+1].data  == BOOM ) count++;

    return count;
}

void Map::setMap(int m_level)
{
    _Random();

    /*Tạo số lượng boom cho map*/
    switch (m_level)
    {
    case 0: // Easy
        Boom = 25;
        break;
    case 1: // Medium
        Boom = 30;
        break;
    case 2: // Hard
        Boom = 40;
        break;
    case 3: // Try Hard
        Boom = 55;
        break;
    } 
    
    /*Đặt boom*/
    for (int i = 0; i < Boom; i++)
    {
        int x = _rand(rows + 1) + 1;
        int y = _rand(cols + 1) + 1;
        while (map[x][y].data == BOOM || x==rows+1 || y == cols+1)
        {
            x = _rand(rows + 1) + 1;
            y = _rand(cols + 1) + 1;
        }
        map[x][y].data = BOOM;
    }

    /*Set Map*/
    for (int i = 1; i <= rows; i++) 
    {
        for (int j = 1; j <= cols; j++) 
        {
            if (map[i][j].data != BOOM)
            {
                map[i][j].data = countBoomOnPixel(i,j);
            }
        }
    }
}

void Map::printMap(int m_level)
{
    Boom = 0;
    for (int i = 1; i < rows+1; i++)
    {
        for (int j = 1; j < cols+1; j++)
        {
            if (map[i][j].data == BOOM) Boom++;
            std::cout << map[i][j].data << " ";
        }
        std::cout << std::endl;
    }
}

Map::~Map()
{
	for (int i = 0; i < rows; i++)
	{
		delete [] map[i];
	}
	delete [] map;
}

// int main() {

//     int level = 0;
//     int row = 12, col = 20;
//     Map m(col, row);

//     m.setMap(level);

//     m.printMap(level);
//     std::cout << "So boom cua map la: " << m.getBoom();

//     return 0;
// }