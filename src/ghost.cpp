#include "ghost.h"
#include <cmath>
#include <iostream>

void Ghost::Initialize()
{
    pos_x = random_w(engine);
    pos_y = random_h(engine);
}

void Ghost::Update()
{
    UpdatePos();
}

void Ghost::UpdatePos()
{
    direction = Direction(random_direction(engine));
    switch (direction)
    {
    case Direction::kUp:
        pos_y -= speed;
        break;

    case Direction::kDown:
        pos_y += speed;
        break;

    case Direction::kLeft:
        pos_x -= speed;
        break;

    case Direction::kRight:
        pos_x += speed;
        break;
    }

    // Wrap the PacMan around to the beginning if going off of the screen.
    pos_x = fmod(pos_x + grid_width, grid_width);
    pos_y = fmod(pos_y + grid_height, grid_height);
} 