#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include <random>
#include "SDL.h"
#include "map.h"
#include "pacman.h"
#include <agent.h>

// Forward Declaration
class PacMan;

enum class Mode{ kChase, kScatter, kFrighten, kDeath };
enum class Colour{ kRed = 0, kBlue = 1, kPink = 2, kYellow = 3 };

class Ghost : public Agent
{
public:
    /*
     * Ghost Constructor
     * @param grid_width set width of map
     * @param grid_height set height of map
     * @param colour set ghost colour
     */
    Ghost(size_t grid_width, size_t grid_height, Colour colour)
        : Agent{grid_width, grid_height},
          ghost_colour(colour)
    {
        Initialize();
    }

    // Classical Behaviour

    /*
     * Initialize ghost position, current direction, mode and previous mode
     */
    void Initialize() override;

    /*
     * Move ghost under different mode
     * @param pacman reference of a pacman instance
     * @param map reference of a map instance
     */
    void Move(PacMan const &pacman, Map const &map);

    /*
     * Get target for ghost with different colour under different modes
     * @param pacman reference of a pacman instance
     */
    void GetTarget(PacMan const &pacman);

    /*
     * Get next valid direction for corner situations
     * @param map reference of a map instance
     */
    void CornerHandle(Map const &map);

    /*
     * Get next valid direction under single line, junctions and corner situation
     * @param map reference of a a map instance
     */
    void MoveTowardTarget(Map const &map);

    /*
     * Move dead ghost to pen
     * @param map reference of a map instance
     */
    void MoveTowardPen(Map const &map);

    /*
     * Move dead ghost to pen, when ghost is near the pen
     * @param map reference of a map instance
     */
    void MoveInPen(Map const &map);

    /*
     * Update ghost position with current direction. If movement is valid, position is updated
     * @param map reference of a map instance
     */
    void Update(Map const &map);


    // Getters / Setters

    /*
     * Check if ghost is eaten by pacman under Mode::kFrighten
     * @return true if ghost is eaten
     */
    bool IsEaten() const { return eaten; }

    /*
     * Get colour of ghost
     * @return colour of ghost
     */
    Colour GetColour() const { return ghost_colour; }

    /*
     * Get current mode of ghost
     * @return current mode of ghost
     */
    Mode GetMode() const { return mode; }

    /*
     * Set ghost mode as Mode::kDeath when ghost is eaten by pacman
     */
    void SetDeath();

    /*
     * Set ghost mode as Mode::kFrighten when pacman eats pill
     */
    void SetFrighten(Map const &map);
    

private:
    // Classical Behaviour

    /*
     * Check if next tile is a wall, when ghost moves in that direction
     * @param dir reference to a chosen direction instance
     * @param map reference to a map instance
     */
    bool IsWall(Direction const dir, Map const &map);

    /*
     * Get status of next tile, when ghost moves in given direction
     * @param dir reference to a chosen direction instance
     * @param map reference to a map instance
     * @return status of next tile
     */
    Status GetNextStatus(Direction const dir, Map const &map);

    /*
     * Get status of current tile
     * @param x position in x-direction
     * @param y position in y-direction
     * @param map reference to a map instance
     */
    Status GetStatus(float x, float y, Map const &map);

    /*
     * Check how many junction exist from current tile
     * @param map reference to a map instance
     * @return number of junctions
     */
    int CheckJuncs(Map const &map);

    /*
     * Check if current ghost position at center of tile
     * @return true if ghost position at center of tile
     */
    bool IsAtCenter();

    /*
     * Calculate distance between ghost and target
     * @return euclidean distance between ghost position and target
     */
    float CalcDistance(int x, int y);

    /*
     * Check if current ghost position is in pen
     * @return true if current ghost position is in pen
     */
    bool InPen();

    /*
     * Resume stored previous mode if pacman no more powered is
     */
    void ResumePrevMode();
    
    // Getters / Setters

    /*
     * Get current ghost postion in x-direction
     * @return current ghost position in x-direction
     */
    float GetGhostX() const { return pos_x; }

    /*
     * Get current ghost postion in y-direction
     * @return current ghost position in y-direction
     */
    float GetGhostY() const { return pos_y; }

    /*
     * Get current tile in x-direction of ghost postion
     * @return current tile in x-direction of ghost position 
     */
    int GetGhostBlockX() const { return static_cast<int>(std::floor(GetGhostX())); }

    /*
     * Get current tile in y-direction of ghost postion 
     * @return current tile in y-direction of ghost position
     */
    int GetGhostBlockY() const { return static_cast<int>(std::floor(GetGhostY())); }

    /*
     * Get current speed
     * @return current speed
     */
    float GetSpeed() const { return speed; };

    /*
     * Set speed 
     */
    void SetSpeed();

    Mode mode = Mode::kChase;
    Mode prev_mode = Mode::kChase;
    Colour ghost_colour = Colour::kRed;
    SDL_Point target;
    bool eaten;

};

#endif // GHOST_H 