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
    int word;
    int row = 0;
    while (std::getline(file, line))
    {
        int col = 0;
        std::stringstream ss(line);
        while (ss >> word)
        {
            switch (word)
            {
            case 0:
                SetMapElement(row, col, Status::kFree);
                col++;
                break;
            case 1:
                SetMapElement(row, col, Status::kFood);
                col++;
                break;
            case 2:
                SetMapElement(row, col, Status::kWall);
                col++;
                break;
            default:
                break;
            }
        }
        //std::cout << "\n";
        row++;
    }
}

void Map::Print()
{
    for (int i = 0; i < grid_width; i++)
    {
        for (int j = 0; j < grid_width; j++) 
        {
            std::cout << ParseStatus(GetMapElement(i, j));
        }
        std::cout << "\n";
    }
}

int Map::ParseStatus(Status status)
{
    switch (status)
    {
    case Status::kFree:
        return 0;
        break;
    case Status::kFood:
        return 1;
        break;
    case Status::kWall:
        return 2;
        break;
    default:
        break;
    }
}

Status Map::GetMapElement(int pos_x, int pos_y) const
{
    return map[pos_x][pos_y];
}

void Map::SetMapElement(int pos_x, int pos_y, Status status)
{
    // map[pos_x][pos_y] = status;
    map.at(pos_x).at(pos_y) = status;
} 