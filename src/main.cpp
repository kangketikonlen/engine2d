#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Program started\n";

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::cout << "SDL initialized\n";

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::cout << "Window created\n";

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
        SDL_Delay(16);
    }

    std::cout << "Shutting down\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
