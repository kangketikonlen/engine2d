#include <SDL2/SDL.h>
#include <iostream>

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator*(float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 5",
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

    // --- State ---
    Vec2 position(400.0f, 300.0f);
    Vec2 velocity(0.0f, 0.0f);
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

        // --- Input ---
        velocity = Vec2(0.0f, 0.0f);
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) velocity.x += speed;

        // --- Movement ---
        position += velocity * deltaTime;

        // --- Rendering ---
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            rectSize,
            rectSize
        };

        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderFillRect(renderer, &rect);
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
