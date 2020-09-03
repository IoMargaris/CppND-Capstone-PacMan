#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "pacman.h"
#include "ghost.h"
#include "map.h"

class Game 
{
public:
    Game(std::size_t grid_width, std::size_t grid_height);

    void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

    int GetScore() const;
    int GetSize() const;

private:
    PacMan pacman;
    Ghost ghost;
    Map map;

    int frame_count = 0;
    bool running = true;
    int score{0};

    void Update();
};

#endif