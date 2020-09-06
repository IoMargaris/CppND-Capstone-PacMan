#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pacman.h"

class Controller 
{
public:
    /*
     * Get keyboard input and set current direction of pacman
     * @param running indicate whether game is running
     * @param pacman reference to a PacMan instance
     */
    void HandleInput(bool &running, PacMan &pacman) const;

private:

    /*
     * Change current direction of pacman based on keyboard
     * @param pacman reference to a PacMan instance
     * @param input keyboard input direction
     */
    void ChangeDirection(PacMan &pacman, Agent::Direction input) const;
};

#endif