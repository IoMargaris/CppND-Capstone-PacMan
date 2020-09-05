#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include <random>
#include "SDL.h"
#include "map.h"
#include "pacman.h"
#include <agent.h>

enum class Mode{ kChase, kScatter, kFrighten, kLeave, kDeath, kPen };
enum class Colour{ kRed = 0, kBlue = 1, kPink = 2, kYellow = 3 };

class Ghost : public Agent
{
public:
    // Constructor / Destructor
    Ghost(size_t grid_width, size_t grid_height, Colour colour)
        : Agent{grid_width, grid_height},
          ghost_colour(colour)
    {
        Initialize();
    }

    // Classical Behaviour
    void Initialize() override;
    void Reset();
    void getTarget(PacMan pacman);
    void CornerHandle(Map &map);
    void MoveTowardTarget(Map &map);
    void Update(Map &map, int &score) override;

    // Getters / Setters
    Colour GetColour() const { return ghost_colour; }

private:
    // Classical Behaviour
    void UpdatePos(float new_pos_x, float new_pos_y);
    bool IsWall(Direction dir, Map &map);
    Status GetNextStatus(Direction dir, Map &map);
    Status GetStatus(float x, float y, Map &map);
    int CheckJuncs(Map &map);
    bool IsAtCenter();
    float CalcDistance(int x, int y);

    // Getter / Setter
    float GetGhostX() const { return pos_x; }
    float GetGhostY() const { return pos_y; }
    int GetGhostBlockX() const { return static_cast<int>(std::floor(GetGhostX())); }
    int GetGhostBlockY() const { return static_cast<int>(std::floor(GetGhostY())); }
    float GetSpeed() const { return speed; };
    void SetSpeed();

    Mode mode = Mode::kChase;
    Colour ghost_colour = Colour::kRed;
    SDL_Point target;
    bool eaten;

};

#endif // GHOST_H 