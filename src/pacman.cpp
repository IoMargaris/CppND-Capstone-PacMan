#include <cmath>
#include <iostream>
#include "pacman.h"
#include "map.h"

void PacMan::Initialize()
{
  pos_x = static_cast<int>(grid_width / 2);
  pos_y = static_cast<int>(grid_height / 2);
}

void PacMan::Update(Map &map, int &score)
{
    float new_pos_x = pos_x;
    float new_pos_y = pos_y;

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
    default:
        break;
    }

    int block_x = static_cast<int>(fmod(new_pos_x + grid_width, grid_width));
    int block_y = static_cast<int>(fmod(new_pos_y + grid_height, grid_height));
    Status status = map.GetMapElement(block_x, block_y);

    switch (status)
    {
    case Status::kFree:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kFood:
        map.SetMapElement(block_x, block_y, Status::kFree);
        map.DecreaseTotalFood();
        UpdatePos(new_pos_x, new_pos_y);
        score++;
        break;
    case Status::kWall:
        break;
    default:
        break;
    }

}

void PacMan::UpdatePos(float new_pos_x, float new_pos_y)
{
  // Wrap the PacMan around to the beginning if going off of the screen.
  pos_x = fmod(new_pos_x + grid_width, grid_width);
  pos_y = fmod(new_pos_y + grid_height, grid_height);

} 