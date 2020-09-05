#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() 
{
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{560};
    constexpr std::size_t kScreenHeight{620};
    constexpr std::size_t kGridWidth{28};
    constexpr std::size_t kGridHeight{31};


    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);

    game.Run(controller, renderer, kMsPerFrame);
    
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    //std::cout << "Size: " << game.GetSize() << "\n";
    return 0;
}