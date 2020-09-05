#ifndef AGENT_H
#define AGENT_H

#include "map.h"

// An abstract base class
class Agent
{
public:
    enum class Direction{ kUp, kDown, kLeft, kRight };

    Agent(size_t grid_width, size_t grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}
    
    // These two pure virtual functions will be implemented by the derived classes
    virtual void Initialize() = 0;

    Direction CurrentDirection = Direction::kRight;
    float speed{0.1f};
    float pos_x;
    float pos_y;
    bool alive{true};
    size_t grid_width;
    size_t grid_height;

};
#endif // AGENT_H 