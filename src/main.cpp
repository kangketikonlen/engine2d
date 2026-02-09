#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}

    Vec2 operator+(const Vec2& o) const { return Vec2(x + o.x, y + o.y); }
    Vec2 operator-(const Vec2& o) const { return Vec2(x - o.x, y - o.y); }
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
};

bool AABBIntersect(const SDL_Rect& a, const SDL_Rect& b)
{
    return (
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y
    );
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int screenW = 800;
    const int screenH = 600;

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 8 (Collision)",
        100, 100, screenW, screenH,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* playerTexture =
        IMG_LoadTexture(renderer, "assets/player.png");

    int texW = 0, texH = 0;
    SDL_QueryTexture(playerTexture, nullptr, nullptr, &texW, &texH);

    // --- Timing ---
    Uint32 lastTicks = SDL_GetTicks();
    const float speed = 200.0f;

    // --- World state ---
    Vec2 playerPos(0.0f, 0.0f);
    Vec2 velocity(0.0f, 0.0f);

    // Static obstacle (world space)
    SDL_Rect obstacleWorld{
        200, 150, 100, 100
    };

    // Camera
    Vec2 cameraPos(0.0f, 0.0f);

    bool running = true;
    SDL_Event event;

    while (running)
    {
        // --- Events ---
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // --- Delta time ---
        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        // --- Input ---
        velocity = Vec2(0, 0);
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) velocity.x += speed;

        playerPos += velocity * dt;

        // --- Camera follows player ---
        cameraPos.x = playerPos.x - screenW * 0.5f;
        cameraPos.y = playerPos.y - screenH * 0.5f;

        // --- Build bounding boxes (world space) ---
        SDL_Rect playerWorld{
            static_cast<int>(playerPos.x),
            static_cast<int>(playerPos.y),
            texW,
            texH
        };

        bool colliding = AABBIntersect(playerWorld, obstacleWorld);

        // --- Rendering ---
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Convert world → screen
        SDL_Rect playerScreen{
            static_cast<int>(playerWorld.x - cameraPos.x),
            static_cast<int>(playerWorld.y - cameraPos.y),
            playerWorld.w,
            playerWorld.h
        };

        SDL_Rect obstacleScreen{
            static_cast<int>(obstacleWorld.x - cameraPos.x),
            static_cast<int>(obstacleWorld.y - cameraPos.y),
            obstacleWorld.w,
            obstacleWorld.h
        };

        // Draw obstacle (red if colliding)
        if (colliding)
            SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
        else
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

        SDL_RenderFillRect(renderer, &obstacleScreen);

        // Draw player
        SDL_RenderCopy(renderer, playerTexture, nullptr, &playerScreen);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
