#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main(int argc, char **argv) 
{
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{560};
    constexpr std::size_t kScreenHeight{620};
    constexpr std::size_t kGridWidth{28};
    constexpr std::size_t kGridHeight{31};

    std::string filename;
    if (argc == 2)
    {
        filename = argv[1];
        std::cout << "User defined map file from path " << filename << "\n";
    }
    else
    {
        filename = "../map/map.txt";
        std::cout << "No map file given, using default map file from path " << filename << "\n";
    }

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight, filename);

    game.Run(controller, renderer, kMsPerFrame);
    
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    //std::cout << "Size: " << game.GetSize() << "\n";
    return 0;
}