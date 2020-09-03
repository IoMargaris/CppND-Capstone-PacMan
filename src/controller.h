#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pacman.h"

class Controller 
{
public:
    void HandleInput(bool &running, PacMan &pacman) const;

private:
    void ChangeDirection(PacMan &pacman, PacMan::Direction input) const;
};

#endif