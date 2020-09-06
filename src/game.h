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
    /**
   * Game Constructor
   * @param grid_width set width of map
   * @param grid_height set height of map
   * @param filename set path to map file
   */
    Game(std::size_t grid_width, std::size_t grid_height, std::string filename);

    /**
   * Initialize all ghosts with different colours
   */
    void Initialize();

    /**
   * Start game loop
   * @param controller used to get input from keyboard for pacman movement
   * @param renderer used to render map, pacman and ghosts
   * @param target_frame_duration set the expected duration for one frame in [ms]
   */
    void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

    /**
   * Get current score of game
   * @return current score
   */
    int GetScore() const;

private:

    /**
   * Update current frame, Move pacman and ghosts and Check collision between pacman and ghosts
   */
    void Update();

    PacMan pacman;
    std::vector<Ghost> ghosts;
    Map map;

    int frame_count{0};
    bool running = true;
    int score{0};
    size_t grid_width;
    size_t grid_height;

};

#endif // GAME_H