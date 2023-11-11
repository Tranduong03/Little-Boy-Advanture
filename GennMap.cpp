#include "GenMap.h"
#include "stdrand.h"
Map* Map::CurrentMap = nullptr;

Map::Map()
{
    map = nullptr;
    cols = 0;
    rows = 0;
    Boom = 0;
}

Map::Map(int col, int row, int level)
{
    cols = col;
    rows = row;

    map = new pixel * [rows + 2];
    for (int i = 0; i <= rows + 1; i++)
    {
        map[i] = new pixel[cols + 2];
        for (int j = 0; j <= cols + 1; j++)
        {
            if ((i > 0 && j > 0) && (i < rows + 1 && j < cols + 1))
            {
                map[i][j].data = 0;
            }
            else map[i][j].data = -1;
            map[i][j].status = false; // ô chưa được chưa mở
        }
    }
    
    setMap(level);

}

// void Map::NewMap(int col, int rows, int level) {
//     if (map != nullptr) {
//         clean();
//     }

//     map = new pixel * [rows + 2];
//     for (int i = 0; i <= rows + 1; i++)
//     {
//         map[i] = new pixel[cols + 2];
//         for (int j = 0; j <= cols + 1; j++)
//         {
//             if ((i > 0 && j > 0) && (i < rows + 1 && j < cols + 1))
//             {
//                 map[i][j].data = 0;
//             }
//             else map[i][j].data = -1;
//             map[i][j].status = false; // ô chưa được chưa mở
//         }
//     }

//     setMap(level);
// }
// void Map::clean() {
//     if (map != nullptr) {
//         for (int i = 0; i <= rows + 1; i++) {
//             delete[] map[i];
//         }
//         delete[] map;
//     }

//     map = nullptr;
//     cols = 0;
//     rows = 0;
//     Boom = 0;
// }
int Map::countBoomOnPixel(int i, int j) {
    int count = 0;

    if (map[i - 1][j - 1].data == BOOM) count++;
    if (map[i - 1][j].data == BOOM) count++;
    if (map[i - 1][j + 1].data == BOOM) count++;
    if (map[i][j - 1].data == BOOM) count++;
    if (map[i][j + 1].data == BOOM) count++;
    if (map[i + 1][j - 1].data == BOOM) count++;
    if (map[i + 1][j].data == BOOM) count++;
    if (map[i + 1][j + 1].data == BOOM) count++;

    return count;
}

void Map::setMap(int m_level)
{
    _Random();

    /*Tạo số lượng boom cho map*/
    switch (m_level)
    {
    case 0: // Easy
        Boom = 20;
        break;
    case 1: // Medium
        Boom = 30;
        break;
    case 2: // Hard
        Boom = 35;
        break;
    case 3: // Try Hard
        Boom = 50;
        break;
    }
    /*Đặt boom*/
    for (int i = 0; i < Boom; i++)
    {
        int x = _rand(rows + 1) + 1;
        int y = _rand(cols + 1) + 1;
        while (map[x][y].data == BOOM || x == rows + 1 || y == cols + 1)
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
                map[i][j].data = countBoomOnPixel(i, j);
            }
        }
    }
}

void Map::printMap(int m_level)
{
    Boom = 0;
    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < cols + 1; j++)
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
        delete[] map[i];
    }
    delete[] map;
}

void Map::DrawPixel() {
    int sizePixel = PixelSIZE;
    int wStart = (SCR_W - sizePixel * rows)/2;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (map[i][j].status == false) {
                TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 10, sizePixel);
            }
            else {
                switch (map[i][j].data) {
                    case 0:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 0, sizePixel);
                        break;
                    case 1:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 1, sizePixel);
                        break;
                    case 2:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 2, sizePixel);
                        break;
                    case 3:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 3, sizePixel);
                        break;
                    case 4:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 4, sizePixel);
                        break;
                    case 5:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 5, sizePixel);
                        break;
                    case 6:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 6, sizePixel);
                        break;
                    case 7:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 7, sizePixel);
                        break;
                    case 8:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 8, sizePixel);
                        break;
                    case 9:
                        TextureManager::GetInstance()->DrawFrame("pixel", wStart + sizePixel * (i - 1), 10 + sizePixel * (j - 1), 50, 50, 0, 9, sizePixel);
                        break;
                    default: break;
                }
            }
        }
    }
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
