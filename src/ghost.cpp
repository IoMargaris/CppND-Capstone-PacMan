#include <cmath>
#include <iostream>
#include <vector>

#include "ghost.h"
#include "map.h"

void Ghost::Initialize()
{
    switch (ghost_colour)
    {
    case Colour::kRed:
        pos_x = 13.5f;
        pos_y = 19.0f;
        CurrentDirection = Direction::kLeft;
        mode = Mode::kScatter;
        prev_mode = Mode::kScatter;
        break;
    case Colour::kBlue:
        pos_x = 11.5f;
        pos_y = 16.0f;
        CurrentDirection = Direction::kRight;
        mode = Mode::kChase;
        prev_mode = Mode::kChase;
        break;
    case Colour::kYellow:
        pos_x = 15.0f;
        pos_y = 15.0f;
        CurrentDirection = Direction::kDown;
        mode = Mode::kScatter;
        prev_mode = Mode::kScatter;
        break;
    case Colour::kPink:
        pos_x = 13.0f;
        pos_y = 15.5f;
        CurrentDirection = Direction::kUp;
        mode = Mode::kChase;
        prev_mode = Mode::kChase;
        break;
    default:
        break;
    }
    eaten = false;
}

void Ghost::getTarget(PacMan pacman)
{
    switch (mode)
    {
    case Mode::kChase:
        switch (ghost_colour)
        {
        case Colour::kRed:
            target = {pacman.GetPacBlockX(),
                      pacman.GetPacBlockY()};
            break;
        case Colour::kBlue:
            switch (pacman.CurrentDirection)
            {
            case Direction::kLeft:
                target = {
                    pacman.GetPacBlockX() - 2,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kRight:
                target = {
                    pacman.GetPacBlockX() + 2,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kUp:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() - 2};
                break;
            case Direction::kDown:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() + 2};
                break;
            default:
                target = {pacman.GetPacBlockX(),
                          pacman.GetPacBlockY()};
                break;
            }
            break;
        case Colour::kYellow:
            target = {0, 0};
            break;
        case Colour::kPink:
            switch (pacman.CurrentDirection)
            {
            case Direction::kLeft:
                target = {
                    pacman.GetPacBlockX() - 4,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kRight:
                target = {
                    pacman.GetPacBlockX() + 4,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kUp:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() - 4};
                break;
            case Direction::kDown:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() + 4};
                break;
            default:
                target = {pacman.GetPacBlockX(),
                          pacman.GetPacBlockY()};
                break;
            }
            break;
        }
        break;
    case Mode::kScatter:
        switch (ghost_colour)
        {
        case Colour::kRed:
            target = {20, 0};
            break;
        case Colour::kBlue:
            target = {5, 0};
            break;
        case Colour::kYellow:
            target = {5, 5};
            break;
        case Colour::kPink:
            target = {0, 20};
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Ghost::SetSpeed()
{
    if (mode == Mode::kFrighten)
    {
        speed = 0.05f;
    }
    else if (mode == Mode::kDeath)
    {
        speed = 0.2f;
    }
    else
    {
        speed = 0.1f;
    }
}

int Ghost::CheckJuncs(Map &map)
{
    int exit = 0;
    if (!IsWall(Direction::kLeft, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kRight, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kUp, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kDown, map))
    {
        exit++;
    }
    return exit;
}

bool Ghost::IsAtCenter()
{
    return (static_cast<int>(GetGhostX() * 10.0f) % 10 == 0 || static_cast<int>(GetGhostX() * 10.0f) % 10 == 9) &&
           (static_cast<int>(GetGhostY() * 10.0f) % 10 == 0 || static_cast<int>(GetGhostY() * 10.0f) % 10 == 9);
}

float Ghost::CalcDistance(int x, int y)
{
    return std::sqrt(std::pow(target.x - x, 2) + std::pow(target.y - y, 2));
}
void Ghost::MoveTowardTarget(Map &map)
{
    float distance = 999.0f;
    Direction tempDir = CurrentDirection;
    if (CheckJuncs(map) >= 3 && IsAtCenter())
    {
        if (CurrentDirection != Direction::kDown && !IsWall(Direction::kUp, map))
        {
            float d = CalcDistance(GetGhostBlockX(), GetGhostBlockY() - 1);
            if (d < distance)
            {
                tempDir = Direction::kUp;
                distance = d;
            }
        }

        if (CurrentDirection != Direction::kLeft && !IsWall(Direction::kRight, map))
        {
            float d = CalcDistance(GetGhostBlockX() + 1, GetGhostBlockY());
            if (d < distance)
            {
                tempDir = Direction::kRight;
                distance = d;
            }
        }

        if (CurrentDirection != Direction::kRight && !IsWall(Direction::kLeft, map))
        {
            float d = CalcDistance(GetGhostBlockX() - 1, GetGhostBlockY());
            if (d < distance)
            {
                tempDir = Direction::kLeft;
                distance = d;
            }
        }
        if (CurrentDirection != Direction::kUp && !IsWall(Direction::kDown, map))
        {
            float d = CalcDistance(GetGhostBlockX(), GetGhostBlockY() - 1);
            if (d < distance)
            {
                tempDir = Direction::kDown;
                distance = d;
            }
        }
        CurrentDirection = tempDir;
    }
    else
    {
        CornerHandle(map);
    }
}

void Ghost::CornerHandle(Map &map)
{
    if (IsAtCenter())
    {
        if (IsWall(CurrentDirection, map))
        {
            if (!IsWall(Direction::kLeft, map) && CurrentDirection != Direction::kRight)
            {
                CurrentDirection = Direction::kLeft;
            }
            else if (!IsWall(Direction::kUp, map) && CurrentDirection != Direction::kDown)
            {
                CurrentDirection = Direction::kUp;
            }
            else if (!IsWall(Direction::kRight, map) && CurrentDirection != Direction::kLeft)
            {
                CurrentDirection = Direction::kRight;
            }
            else if (!IsWall(Direction::kDown, map) && CurrentDirection != Direction::kUp)
            {
                CurrentDirection = Direction::kDown;
            }
        }
    }
}

void Ghost::SetFrighten(Map &map)
{
    mode = Mode::kFrighten;
    CornerHandle(map);
}

void Ghost::ResumePrevMode()
{
    mode = prev_mode;
    eaten = false;
}

void Ghost::SetDeath()
{
    eaten = true;
    mode = Mode::kDeath;
}

void Ghost::Update(Map &map)
{
    SetSpeed();
    
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
    }

    Status status = GetNextStatus(CurrentDirection, map);

    switch (status)
    {
    case Status::kFree:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kFood:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kSpecial:
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

bool Ghost::IsWall(Direction dir, Map &map)
{
    return GetNextStatus(dir, map) == Status::kWall;
}

Status Ghost::GetNextStatus(Direction dir, Map &map)
{
    switch (dir)
    {
    case Direction::kLeft:
        return GetStatus(GetGhostX() - GetSpeed(), GetGhostY(), map);
        break;
    case Direction::kRight:
        return GetStatus(GetGhostX() + GetSpeed(), GetGhostY(), map);
        break;
    case Direction::kUp:
        return GetStatus(GetGhostX(), GetGhostY() - GetSpeed(), map);
        break;
    case Direction::kDown:
        return GetStatus(GetGhostX(), GetGhostY() + GetSpeed(), map);
        break;
    default:
        std::cout << "Error: Unknown Direction\n";
        break;
    }
}

Status Ghost::GetStatus(float x, float y, Map &map)
{
    int block_x = static_cast<int>(std::floor(fmod(x + grid_width, grid_width)));
    int block_y = static_cast<int>(std::floor(fmod(y + grid_height, grid_height)));
    return map.GetMapElement(block_x, block_y);
}