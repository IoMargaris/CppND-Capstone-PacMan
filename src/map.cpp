#include <iostream>
#include <sstream>
#include "map.h"

Map::Map(int grid_width, int grid_height)
    : grid_width(grid_width), grid_height(grid_height)
{
    map.resize(grid_width, std::vector<Status>(grid_height));
    file.open("../map/map.txt");
}

Map::~Map()
{
    file.close();
}

void Map::Initialize()
{
    std::string line;
    char word;
    char c;
    int row = 0;
    while (std::getline(file, line))
    {
        int col = 0;
        std::stringstream ss(line);
        while (ss >> word >> c)
        {
            switch (word)
            {
            case 'u':
                SetMapElement(col, row, Status::kFree);
                col++;
                break;
            case 'o':
                SetMapElement(col, row, Status::kFood);
                IncreaseTotalFood();
                col++;
                break;
            case 'O':
                SetMapElement(col, row, Status::kSpecial);
                IncreaseTotalFood();
                col++;
                break;
            case 'W':
                SetMapElement(col, row, Status::kWall);
                col++;
                break;
            default:
                break;
            }
        }

        row++;
    }
}

void Map::Print()
{
    for (int i = 0; i < grid_width; i++)
    {
        for (int j = 0; j < grid_height; j++) 
        {
            std::cout << ParseStatus(GetMapElement(i, j)) << ' ';
        }
        std::cout << "\n";
    }
}

char Map::ParseStatus(Status status)
{
    switch (status)
    {
    case Status::kFree:
        return 'u';
        break;
    case Status::kFood:
        return 'o';
        break;
    case Status::kSpecial:
        return 'O';
    case Status::kWall:
        return 'W';
        break;
    default:
        break;
    }
}

Status Map::GetMapElement(int i, int j) const
{
    return map[i][j];
}

void Map::SetMapElement(int i, int j, Status status)
{
    map[i][j] = status;
} 