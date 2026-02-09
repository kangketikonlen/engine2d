#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}

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
    // --- SDL core ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // --- SDL_image ---
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 6",
        100, 100,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
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
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // --- Load texture ---
    SDL_Texture* playerTexture =
        IMG_LoadTexture(renderer, "assets/player.png");

    if (!playerTexture)
    {
        std::cerr << "Failed to load texture: "
                  << IMG_GetError() << std::endl;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // --- Timing ---
    const float targetFPS = 60.0f;
    const Uint32 targetFrameMs = static_cast<Uint32>(1000.0f / targetFPS);
    Uint32 lastTicks = SDL_GetTicks();

    // --- State ---
    Vec2 position(400.0f, 300.0f);
    Vec2 velocity(0.0f, 0.0f);
    const float speed = 200.0f;

    // Query texture size
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(playerTexture, nullptr, nullptr, &texW, &texH);

    bool running = true;
    SDL_Event event;

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

        SDL_Rect dst{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            texW,
            texH
        };

        SDL_RenderCopy(renderer, playerTexture, nullptr, &dst);
        SDL_RenderPresent(renderer);

        // --- Frame limiting ---
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < targetFrameMs)
        {
            SDL_Delay(targetFrameMs - frameTime);
        }
    }

    // --- Cleanup ---
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
