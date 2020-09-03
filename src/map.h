#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>

enum class Status{ kFree, kFood, kWall };

class Map
{
public:
    Map(int grid_width, int grid_height);
    ~Map();

    void Initialize();
    void Print();
    int ParseStatus(Status status);
    Status GetMapElement(int pos_x, int pos_y) const;
    void SetMapElement(int pos_x, int pos_y, Status status);

private:
    std::vector<std::vector<Status>> map;
    int grid_width;
    int grid_height;
    std::ifstream file;

};

#endif // MAP_H 