#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>

enum class Status{ kFree, kFood, kSpecial, kWall };

class Map
{
public:
    /*
     * Map Constructor
     * @param grid_width set width of map
     * @param grid_height set height of map
     * @param filename set path to map file
     */
    Map(size_t grid_width, size_t grid_height, std::string filename);

    /*
     * Map Destructor
     */
    ~Map();

    // Classical Behaviour

    /*
     * Initialize map by parsing information from given map file
     */
    void Initialize();

    /*
     * Print map in console
     */
    void Print();

    /*
     * Parse status as a char
     * @param status reference to a status instance
     * @return a char for corresponding status, possible char 'W': Wall, 'o': Food, 'S': Special, 'u': Free
     */
    char ParseStatus(Status const &status) const;


    // Getter / Setters

    /*
     * Get status stored in map[i][j]
     * @param status reference to a status instance
     */
    Status GetMapElement(int i, int j) const;

    /*
     * Assign status of map[i][j]
     */
    void SetMapElement(int i, int j, Status status);

    /*
     * Get current total food on map
     * @return total food on map
     */
    int GetCurrentTotalFood() const { return total_food; }

    /*
     * Decrease total food when pacman eats food
     */
    void DecreaseTotalFood() { total_food--; }

    /*
     * Increase total food during initialization of map
     */
    void IncreaseTotalFood() { total_food++; }
    

private:
    std::vector<std::vector<Status>> map;
    size_t grid_width;
    size_t grid_height;
    std::ifstream file;

    int total_food = 0;

};

#endif // MAP_H 