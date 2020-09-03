#include <cmath>
#include <iostream>
#include "ghost.h"
#include "map.h"

void Ghost::Initialize()
{
    // pos_x = random_w(engine);
    // pos_y = random_h(engine);
    pos_x = 20;
    pos_y = 20;
}

void Ghost::Update(Map &map, int &score)
{
    float new_pos_x = pos_x;
    float new_pos_y = pos_y;

    direction = Direction(random_direction(engine));
    switch (direction)
    {
    case Direction::kUp:
        new_pos_y -= speed;
        break;

    case Direction::kDown:
        new_pos_y += speed;
        break;

    case Direction::kLeft:
        new_pos_x -= speed;
        break;

    case Direction::kRight:
        new_pos_x += speed;
        break;
    }
    
    Status status = map.GetMapElement(static_cast<int>(new_pos_x),
                                      static_cast<int>(new_pos_y));
    // std::cout << map.ParseStatus(status) << std::endl;
    switch (status)
    {
    case Status::kFree:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kFood:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kWall:
        break;
    default:
        break;
    }
}

void Ghost::UpdatePos(float new_pos_x, float new_pos_y)
{
    // Wrap the PacMan around to the beginning if going off of the screen.
    pos_x = fmod(new_pos_x + grid_width, grid_width);
    pos_y = fmod(new_pos_y + grid_height, grid_height);
}