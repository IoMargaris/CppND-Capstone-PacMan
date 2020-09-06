#include <cmath>
#include <iostream>
#include "pacman.h"
#include "map.h"

void PacMan::Initialize()
{
  pos_x = 13.0f;
  pos_y = 17.0f;
}

void PacMan::Move(Map &map, int &score, int frame_counter)
{
    if (powered)
    {
        powered_end_frame++;
        if (powered_end_frame - powered_start_frame > powered_periode)
        {
            powered = false;
        }
    }

    float new_pos_x = pos_x;
    float new_pos_y = pos_y;

    switch (CurrentDirection)
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
        score += 10;
        break;
    case Status::kSpecial:
        map.SetMapElement(block_x, block_y, Status::kFree);
        map.DecreaseTotalFood();
        UpdatePos(new_pos_x, new_pos_y);
        score += 50;
        powered = true;
        powered_start_frame = frame_counter;
        powered_end_frame = frame_counter;
        break;
    case Status::kWall:
        break;
    default:
        break;
    }

}

bool PacMan::CheckCollision(Ghost &ghost, bool &running, int &score)
{
  int p_x = static_cast<int>(pos_x);
  int p_y = static_cast<int>(pos_y);
  int g_x = static_cast<int>(ghost.pos_x);
  int g_y = static_cast<int>(ghost.pos_y);

  if (p_x == g_x && p_y == g_y)
  {
    if (IsPowered())
    {
      ghost.SetDeath();
      score += 200;
    }
    else
    {
      if (!ghost.IsEaten())
      {
        SetDeath();
        running = false;
      }
    }
  }
}
