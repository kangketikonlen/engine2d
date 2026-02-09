#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

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
    SDL_Texture* texture; // borrowed
    int w, h;
};

struct TextureManager
{
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> cache;

    explicit TextureManager(SDL_Renderer* r) : renderer(r) {}

    SDL_Texture* load(const std::string& path)
    {
        if (cache.count(path))
            return cache[path];

        SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
        if (!tex)
        {
            std::cerr << "Texture load failed: " << path << "\n";
            return nullptr;
        }

        cache[path] = tex;
        return tex;
    }

    ~TextureManager()
    {
        for (auto& p : cache)
            SDL_DestroyTexture(p.second);
    }
};

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int screenW = 800;
    const int screenH = 600;

    SDL_Window* window = SDL_CreateWindow(
        "Engine2D - Day 11 (Assets)",
        100, 100, screenW, screenH,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextureManager textures(renderer);

    SDL_Texture* playerTex = textures.load("assets/player.png");

    int texW = 0, texH = 0;
    SDL_QueryTexture(playerTex, nullptr, nullptr, &texW, &texH);

    std::vector<Entity> entities;

    entities.push_back({ Vec2(0, 0), Vec2(0, 0), playerTex, texW, texH });
    entities.push_back({ Vec2(200, 100), Vec2(0, 0), playerTex, texW, texH });
    entities.push_back({ Vec2(-150, -50), Vec2(0, 0), playerTex, texW, texH });

    Uint32 lastTicks = SDL_GetTicks();
    const float speed = 200.0f;

    Vec2 cameraPos(0, 0);
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

        Entity& player = entities[0];
        player.velocity = Vec2(0, 0);

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) player.velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) player.velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) player.velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) player.velocity.x += speed;

        for (Entity& e : entities)
            e.position += e.velocity * dt;

        cameraPos.x = player.position.x - screenW * 0.5f;
        cameraPos.y = player.position.y - screenH * 0.5f;

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
