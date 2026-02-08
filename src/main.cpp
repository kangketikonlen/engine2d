#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 2 Timing and FPS",
        100, 100,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // --- Timing setup ---
    const float targetFPS = 60.0f;
    const float targetFrameTime = 1.0f / targetFPS;

    Uint32 lastTicks = SDL_GetTicks();
    float fpsTimer = 0.0f;
    int frameCount = 0;

    while (running)
    {
        Uint32 frameStart = SDL_GetTicks();

        // --- Events ---
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // --- Timing ---
        Uint32 frameEnd = SDL_GetTicks();
        float deltaTime = (frameEnd - lastTicks) / 1000.0f;
        lastTicks = frameEnd;

        // --- FPS calculation ---
        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0f)
        {
            float fps = frameCount / fpsTimer;
            std::cout << "FPS: " << fps << std::endl;

            fpsTimer = 0.0f;
            frameCount = 0;
        }

        // --- Frame limiting ---
        Uint32 frameDuration = frameEnd - frameStart;
        Uint32 targetFrameMs = static_cast<Uint32>(1000.0f / targetFPS);

        if (frameDuration < targetFrameMs)
        {
            SDL_Delay(targetFrameMs - frameDuration);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
