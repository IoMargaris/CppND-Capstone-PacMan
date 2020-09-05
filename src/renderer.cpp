#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, screen_width,
                                    screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) 
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) 
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() 
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(PacMan const &pacman, std::vector<Ghost> &ghosts, Map const &map) 
{
    SDL_Rect block;
    SDL_Point point;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render map
    for (int i = 0; i < grid_width; i++)
    {
        for (int j = 0; j < grid_height; j++)
        {
            block.x = i * block.w;
            block.y = j * block.h;
            switch (map.GetMapElement(i, j))
            {
            case Status::kFree:
                SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF); // Black
                SDL_RenderFillRect(sdl_renderer, &block);
                break;
            case Status::kFood:
                SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xB1, 0x6A, 0xFF); // Jade

                for (int l = i * block.w + block.w / 4; l < i * block.w + 3 * block.w / 4; l++)
                {
                    for (int m = j * block.h + block.h / 4; m < j * block.h + 3 * block.h / 4; m++)
                    {
                        point.x = l;
                        point.y = m;
                        SDL_RenderDrawPoint(sdl_renderer, point.x, point.y);
                    }
                }
                break;
            case Status::kSpecial:
                SDL_SetRenderDrawColor(sdl_renderer, 0x89, 0xC4, 0xF4, 0xFF); // Jordy Blue
                for (int l = i * block.w + block.w / 4; l < i * block.w + 3 * block.w / 4; l++)
                {
                    for (int m = j * block.h + block.h / 4; m < j * block.h + 3 * block.h / 4; m++)
                    {
                        point.x = l;
                        point.y = m;
                        SDL_RenderDrawPoint(sdl_renderer, point.x, point.y);
                    }
                }
                break;
            case Status::kWall:
                SDL_SetRenderDrawColor(sdl_renderer, 0x2C, 0x3E, 0x50, 0xFF); //  Madison
                SDL_RenderFillRect(sdl_renderer, &block);
                break;
            default:
                break;
            }
        }
    }

    // Render PacMan
    block.x = static_cast<int>(pacman.pos_x) * block.w;
    block.y = static_cast<int>(pacman.pos_y) * block.h;
    if (pacman.alive) 
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0x00); // Yellow
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render Ghost
    for(Ghost const &ghost : ghosts)
    {
        block.x = static_cast<int>(ghost.pos_x) * block.w;
        block.y = static_cast<int>(ghost.pos_y) * block.h;

        if (ghost.IsEaten())
        {
            SDL_SetRenderDrawColor(sdl_renderer, 0x83, 0x83, 0x83, 0xFF); // Dark Gray
        }
        else if (ghost.GetMode() == Mode::kFrighten)
        {
            SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x99, 0xFF); // Dark Blue
        }
        else
        {
            switch (ghost.GetColour())
            {
            case Colour::kRed:
               SDL_SetRenderDrawColor(sdl_renderer, 0xFA, 0x80, 0x72, 0xFF); // Salmon
                break;
            case Colour::kBlue:
                SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xBF, 0xFF, 0xFF); // Deep Skyblue
                break;
            case Colour::kYellow:
                SDL_SetRenderDrawColor(sdl_renderer, 0xF0, 0xE6, 0x8C, 0xFF); // khaki
                break;
            case Colour::kPink:
                SDL_SetRenderDrawColor(sdl_renderer, 0xDB, 0x70, 0x93, 0xFF); // Pale violetred
                break;
            default:
                break;
            }
        } 
    
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) 
{
  std::string title{"PacMan Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
