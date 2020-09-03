#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL.h"
#include "agent.h"

class PacMan : public Agent
{
public:

    PacMan(int grid_width, int grid_height)
        : Agent{grid_width, grid_height} {
            Initialize();
        }

    void Initialize() override;
    void Update(Map &map, int &score) override;

private:
    void UpdatePos(float new_pos_x, float new_pos_y);

};

#endif 