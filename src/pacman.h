#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include <cmath>
#include "SDL.h"
#include "agent.h"

class PacMan : public Agent
{
public:

    PacMan(size_t grid_width, size_t grid_height)
        : Agent{grid_width, grid_height} {
            Initialize();
        }

    // Classical Behaviour
    void Initialize() override;
    void Update(Map &map, int &score) override;

    // Getter / Setter
    float GetPacX() const { return pos_x; }
    float GetPacY() const { return pos_y; }
    int GetPacBlockX() const { return static_cast<int>(std::floor(GetPacX())); }
    int GetPacBlockY() const { return static_cast<int>(std::floor(GetPacY())); }

private:
    // Classival Behaviour
    void UpdatePos(float new_pos_x, float new_pos_y);

};

#endif 