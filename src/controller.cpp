#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "pacman.h"

void Controller::ChangeDirection(PacMan &pacman, PacMan::Direction input) const
{
    pacman.direction = input;
    //return;
}

void Controller::HandleInput(bool &running, PacMan &pacman) const 
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) 
        {
            running = false;
        } 
        else if (e.type == SDL_KEYDOWN) 
        {
            switch (e.key.keysym.sym) 
            {
                case SDLK_UP:
                ChangeDirection(pacman, PacMan::Direction::kUp);
                break;

                case SDLK_DOWN:
                ChangeDirection(pacman, PacMan::Direction::kDown);
                break;

                case SDLK_LEFT:
                ChangeDirection(pacman, PacMan::Direction::kLeft);
                break;

                case SDLK_RIGHT:
                ChangeDirection(pacman, PacMan::Direction::kRight);
                break;
            }
        }
    }
}