#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>

enum class Status{ kFree, kFood, kSpecial, kWall };

class Map
{
public:
    // Constructor / Destructor
    Map(int grid_width, int grid_height);
    ~Map();

    // Classical Behaviour
    void Initialize();
    void Print();
    char ParseStatus(Status status);
    void DecreaseTotalFood() { total_food--; }
    void IncreaseTotalFood() { total_food++; }

    // Getter / Setters
    Status GetMapElement(int i, int j) const;
    void SetMapElement(int i, int j, Status status);
    int GetCurrentTotalFood() const { return total_food; }
    

private:
    std::vector<std::vector<Status>> map;
    int grid_width;
    int grid_height;
    std::ifstream file;

    int total_food = 0;

};

#endif // MAP_H 