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
        "Engine2D - Day 3",
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

    // --- Timing ---
    const float targetFPS = 60.0f;
    const Uint32 targetFrameMs = static_cast<Uint32>(1000.0f / targetFPS);

    Uint32 lastTicks = SDL_GetTicks();

    // --- Input state ---
    float x = 0.0f;
    float y = 0.0f;
    const float speed = 200.0f; // units per second

    while (running)
    {
        Uint32 frameStart = SDL_GetTicks();

        // --- Events (pressed / released) ---
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // --- Delta time ---
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        // --- Keyboard state (held keys) ---
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) y -= speed * deltaTime;
        if (keys[SDL_SCANCODE_S]) y += speed * deltaTime;
        if (keys[SDL_SCANCODE_A]) x -= speed * deltaTime;
        if (keys[SDL_SCANCODE_D]) x += speed * deltaTime;

        // --- Debug output ---
        std::cout << "\rPosition: (" << x << ", " << y << ")   " << std::flush;

        // --- Frame limiting ---
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < targetFrameMs)
        {
            SDL_Delay(targetFrameMs - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
