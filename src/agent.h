#ifndef AGENT_H
#define AGENT_H

// An abstract base class that PacMan and the ghosts will inherit from
class Agent
{
public:
    enum class Direction{ kUp, kDown, kLeft, kRight };

    Agent(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}
    
    // These two pure virtual functions will be implemented by the derived classes: PacMan & Ghost
    virtual void Initialize() = 0;
    virtual void Update() = 0;

    Direction direction = Direction::kUp;
    const float speed{0.1f};
    float pos_x;
    float pos_y;
    bool alive{true};
    int grid_width;
    int grid_height;

};
#endif // AGENT_H 