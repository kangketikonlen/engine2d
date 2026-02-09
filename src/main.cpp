#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

struct Vec2
{
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
};

struct Entity
{
    Vec2 position;
    Vec2 velocity;
    SDL_Texture* texture;
    int w, h;
};

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int screenW = 800;
    const int screenH = 600;

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 10 (Entities)",
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

    // --- Entities ---
    std::vector<Entity> entities;

    // Player
    entities.push_back({
        Vec2(0, 0),
        Vec2(0, 0),
        playerTexture,
        texW, texH
    });

    // Static objects (clones for demo)
    entities.push_back({
        Vec2(200, 100),
        Vec2(0, 0),
        playerTexture,
        texW, texH
    });

    entities.push_back({
        Vec2(-150, -50),
        Vec2(0, 0),
        playerTexture,
        texW, texH
    });

    bool running = true;
    SDL_Event event;

    Vec2 cameraPos(0, 0);

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

        // --- Input controls only first entity (player) ---
        Entity& player = entities[0];
        player.velocity = Vec2(0, 0);

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) player.velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) player.velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) player.velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) player.velocity.x += speed;

        // --- Update all entities ---
        for (Entity& e : entities)
        {
            e.position += e.velocity * dt;
        }

        // --- Camera follows player ---
        cameraPos.x = player.position.x - screenW * 0.5f;
        cameraPos.y = player.position.y - screenH * 0.5f;

        // --- Rendering ---
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        for (const Entity& e : entities)
        {
            SDL_Rect dst{
                static_cast<int>(e.position.x - cameraPos.x),
                static_cast<int>(e.position.y - cameraPos.y),
                e.w, e.h
            };

            SDL_RenderCopy(renderer, e.texture, nullptr, &dst);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
