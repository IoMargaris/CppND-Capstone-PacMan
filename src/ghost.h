#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include "SDL.h"
#include <agent.h>
#include <random>

class Ghost : public Agent
{
public:
    Ghost(int grid_width, int grid_height)
        : Agent{grid_width, grid_height},
          engine(dev()),
          random_w(0, static_cast<int>(grid_width)),
          random_h(0, static_cast<int>(grid_height)),
          random_direction(0, 4)
    {
        Initialize();
    }

    void Initialize() override;
    void Update(Map &map, int &score) override;

private:
    void UpdatePos(float new_pos_x, float new_pos_y);
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    std::uniform_int_distribution<int> random_direction;

};

#endif // GHOST_H 