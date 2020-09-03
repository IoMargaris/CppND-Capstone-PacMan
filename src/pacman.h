#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL.h"

class PacMan
{
public:
    enum class Direction{ kUp, kDown, kLeft, kRight };

    PacMan(int grid_width, int grid_height)
        : grid_width(grid_width),
        grid_height(grid_height),
        pos_x(grid_width / 2),
        pos_y(grid_height / 2) {}

    void Update();

    // Initial direction is Up
    Direction direction = Direction::kUp;

    const float speed{0.1f};
    bool alive{true};
    float pos_x;
    float pos_y;

private:
    void UpdatePos();
    int grid_width;
    int grid_height;
};

#endif 