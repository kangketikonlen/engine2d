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
        "Engine2D - Day 4",
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

    // --- Renderer ---
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // --- Timing ---
    const float targetFPS = 60.0f;
    const Uint32 targetFrameMs = static_cast<Uint32>(1000.0f / targetFPS);
    Uint32 lastTicks = SDL_GetTicks();

    // --- Object state ---
    float x = 400.0f;
    float y = 300.0f;
    const float speed = 200.0f;

    const int rectSize = 50;

    while (running)
    {
        Uint32 frameStart = SDL_GetTicks();

        // --- Events ---
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // --- Delta time ---
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        // --- Input (held keys) ---
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) y -= speed * deltaTime;
        if (keys[SDL_SCANCODE_S]) y += speed * deltaTime;
        if (keys[SDL_SCANCODE_A]) x -= speed * deltaTime;
        if (keys[SDL_SCANCODE_D]) x += speed * deltaTime;

        // --- Rendering ---
        // Clear screen (dark gray)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw rectangle (white)
        SDL_Rect rect{
            static_cast<int>(x),
            static_cast<int>(y),
            rectSize,
            rectSize
        };

        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Present frame
        SDL_RenderPresent(renderer);

        // --- Frame limiting ---
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < targetFrameMs)
        {
            SDL_Delay(targetFrameMs - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
