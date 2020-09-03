#include "pacman.h"
#include <cmath>
#include <iostream>

void PacMan::Initialize()
{
  pos_x = static_cast<int>(grid_width / 2);
  pos_y = static_cast<int>(grid_height / 2);
}

void PacMan::Update()
{
  UpdatePos();
}

void PacMan::UpdatePos()
{
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