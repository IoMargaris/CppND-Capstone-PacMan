#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include <cmath>
#include "SDL.h"
#include <agent.h>
#include <ghost.h>

// Forward declaration 
class Ghost;

class PacMan : public Agent
{
public:

    /*
    * PacMan Constuctor
    * @param grid_width set width of map
    * @param grid_width set height of map
    */
    PacMan(size_t grid_width, size_t grid_height)
        : Agent{grid_width, grid_height} {
            Initialize();
        }

    // Classical Behaviour

    /**
     * Initialize postion of pacman
     */
    void Initialize() override;

    /*
    * Move pacman with current direction, which can be updated with controller input
    * Consider whether pacman is powered during effect of special food pacman has eaten
    * Accumlate score if food or special food is eaten by pacman
    * @param map reference to a map instance
    * @param score reference to game score
    * @param frame_counter set initial timestamp when pacman is powered
    */
    void Move(Map &map, int &score, int frame_counter);

    /*
    * Check if collision encounters between pacman and ghost
    * When yes, if pacman is powered, set ghost to be eaten and pacman increase score
    * Otherwise, set pacman as dead
    * @return true if collsion enconters between pacman and ghost
    */
    bool CheckCollision(Ghost &ghost, bool &running, int &score);

    // Getter / Setter

    /*
     * Get current postion of pacman in x-direction
     * @return current postion of pacman in x-direction
     */
    float GetPacX() const { return pos_x; }

    /*
     * Get current postion of pacman in y-direction
     * @return current postion of pacman in y-direction
     */
    float GetPacY() const { return pos_y; }

    /*
    * Get current tile in x-direction, where current pacman in x-direction locates
    * @return current tile in x-direction, where current pacman in x-direction locates
    */
    int GetPacBlockX() const { return static_cast<int>(std::floor(GetPacX())); }

    /*
   * Get current tile in y-direction, where current pacman in y-direction locates
   * @return current tile in y-direction, where current pacman in y-direction locates
   */
    int GetPacBlockY() const { return static_cast<int>(std::floor(GetPacY())); }

    /*
     * Check if pacman is powered
     * @return true if pacman is powered
     */
    bool IsPowered() const { return powered; }

    /*
     * Set pacman to dead
     */
    bool SetDeath() { alive = false; }

    /*
     * Check if pacman is alive
     * @return true if pacman is alive
     */
    bool IsAlive() const { return alive; }

private:
    // Classival Behaviour
    bool powered{false};
    int powered_start_frame;
    int powered_end_frame;
    static constexpr int powered_periode = 10 * 60;
    bool alive{true};

};

#endif 