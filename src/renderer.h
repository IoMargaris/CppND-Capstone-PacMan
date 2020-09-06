#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "pacman.h"
#include "ghost.h"
#include "map.h"

class Renderer 
{
public:
    /*
     * Renderer Constructor
     * @param screen_width set width of screen
     * @param screen_height set height of screen
     * @param grid_width set width of map
     * @param grid_height set height of map
     */
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
            const std::size_t grid_width, const std::size_t grid_height);

    /*
     * Renderer Destructor
     */
    ~Renderer();

    /*
     * Render map, pacman and ghosts with different colour under different mode
     * @param pacman reference to a pacman
     * @param ghost reference to ghosts stored in a std::vector
     * @param map reference to a map instance
     */
    void Render(PacMan const &pacman, std::vector<Ghost> &ghost, Map const &map);

    /*
    * Update window title with current score and fps count
    * @param score indicate current score in game
    * @param fps indicate current frame per second in game
    */
    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif