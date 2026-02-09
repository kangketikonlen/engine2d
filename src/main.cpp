#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}

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
        "Engine2D - Day 9 (Collision Resolution)",
        100, 100, screenW, screenH,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* playerTexture =
        IMG_LoadTexture(renderer, "assets/player.png");

    int texW = 0, texH = 0;
    SDL_QueryTexture(playerTexture, nullptr, nullptr, &texW, &texH);

    Uint32 lastTicks = SDL_GetTicks();
    const float speed = 200.0f;

    Vec2 playerPos(0.0f, 0.0f);
    Vec2 velocity(0.0f, 0.0f);

    SDL_Rect obstacle{
        200, 150, 120, 120
    };

    Vec2 cameraPos(0.0f, 0.0f);

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        velocity = Vec2(0, 0);
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) velocity.x += speed;

        // --- Move on X ---
        playerPos.x += velocity.x * dt;

        SDL_Rect playerX{
            static_cast<int>(playerPos.x),
            static_cast<int>(playerPos.y),
            texW, texH
        };

        if (AABBIntersect(playerX, obstacle))
        {
            if (velocity.x > 0)
                playerPos.x = obstacle.x - texW;
            else if (velocity.x < 0)
                playerPos.x = obstacle.x + obstacle.w;
        }

        // --- Move on Y ---
        playerPos.y += velocity.y * dt;

        SDL_Rect playerY{
            static_cast<int>(playerPos.x),
            static_cast<int>(playerPos.y),
            texW, texH
        };

        if (AABBIntersect(playerY, obstacle))
        {
            if (velocity.y > 0)
                playerPos.y = obstacle.y - texH;
            else if (velocity.y < 0)
                playerPos.y = obstacle.y + obstacle.h;
        }

        // --- Camera ---
        cameraPos.x = playerPos.x - screenW * 0.5f;
        cameraPos.y = playerPos.y - screenH * 0.5f;

        // --- Rendering ---
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_Rect obstacleScreen{
            static_cast<int>(obstacle.x - cameraPos.x),
            static_cast<int>(obstacle.y - cameraPos.y),
            obstacle.w, obstacle.h
        };

        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
        SDL_RenderFillRect(renderer, &obstacleScreen);

        SDL_Rect playerScreen{
            static_cast<int>(playerPos.x - cameraPos.x),
            static_cast<int>(playerPos.y - cameraPos.y),
            texW, texH
        };

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
