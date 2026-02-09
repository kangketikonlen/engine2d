#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// -------------------- Math --------------------
struct Vec2
{
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float x_, float y_) : x(x_), y(y_) {}
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
};

// -------------------- Entity --------------------
struct Entity
{
    Vec2 position;
    Vec2 velocity;
    SDL_Texture* texture; // borrowed
    int w, h;
};

// -------------------- Texture Manager --------------------
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

// -------------------- Collision --------------------
bool AABBIntersect(const SDL_Rect& a, const SDL_Rect& b)
{
    return (
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y
    );
}

// -------------------- Scene Init --------------------
void initScene(std::vector<Entity>& entities,
               std::vector<SDL_Rect>& walls,
               SDL_Texture* playerTex,
               int w, int h)
{
    entities.clear();
    walls.clear();

    // Player
    entities.push_back({ Vec2(0, 60), Vec2(0, 0), playerTex, w, h });

    // Simple level (walls)
    walls.push_back({ -300, -200, 600, 40 });   // top
    walls.push_back({ -300,  200, 600, 40 });   // bottom
    walls.push_back({ -300, -200, 40, 440 });   // left
    walls.push_back({  260, -200, 40, 440 });   // right

    // Inner obstacle
    walls.push_back({ -60, -60, 120, 120 });
}

// -------------------- Main --------------------
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int screenW = 800;
    const int screenH = 600;

    SDL_Window* window = SDL_CreateWindow(
        "engine2d - Day 14 Mini Demo",
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
    std::vector<SDL_Rect> walls;
    initScene(entities, walls, playerTex, texW, texH);

    Uint32 lastTicks = SDL_GetTicks();
    const float speed = 200.0f;

    Vec2 cameraPos(0, 0);
    bool running = true;
    bool debugDraw = false;
    SDL_Event event;

    while (running)
    {
        // -------- Events --------
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                initScene(entities, walls, playerTex, texW, texH);
            }

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.scancode == SDL_SCANCODE_F1)
            {
                debugDraw = !debugDraw;
            }
        }

        // -------- Timing --------
        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        // -------- Player Input --------
        Entity& player = entities[0];
        player.velocity = Vec2(0, 0);

        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) player.velocity.y -= speed;
        if (keys[SDL_SCANCODE_S]) player.velocity.y += speed;
        if (keys[SDL_SCANCODE_A]) player.velocity.x -= speed;
        if (keys[SDL_SCANCODE_D]) player.velocity.x += speed;

        // -------- Collision Resolution --------
        // Move X
        player.position.x += player.velocity.x * dt;
        SDL_Rect playerBoxX{
            (int)player.position.x,
            (int)player.position.y,
            player.w, player.h
        };

        for (const SDL_Rect& wall : walls)
        {
            if (AABBIntersect(playerBoxX, wall))
            {
                if (player.velocity.x > 0)
                    player.position.x = wall.x - player.w;
                else if (player.velocity.x < 0)
                    player.position.x = wall.x + wall.w;
            }
        }

        // Move Y
        player.position.y += player.velocity.y * dt;
        SDL_Rect playerBoxY{
            (int)player.position.x,
            (int)player.position.y,
            player.w, player.h
        };

        for (const SDL_Rect& wall : walls)
        {
            if (AABBIntersect(playerBoxY, wall))
            {
                if (player.velocity.y > 0)
                    player.position.y = wall.y - player.h;
                else if (player.velocity.y < 0)
                    player.position.y = wall.y + wall.h;
            }
        }

        // -------- Camera --------
        cameraPos.x = player.position.x - screenW * 0.5f;
        cameraPos.y = player.position.y - screenH * 0.5f;

        // -------- Rendering --------
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);

        // Walls
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        for (const SDL_Rect& wall : walls)
        {
            SDL_Rect screenWall{
                wall.x - (int)cameraPos.x,
                wall.y - (int)cameraPos.y,
                wall.w, wall.h
            };
            SDL_RenderFillRect(renderer, &screenWall);
        }

        // Player
        SDL_Rect playerScreen{
            (int)(player.position.x - cameraPos.x),
            (int)(player.position.y - cameraPos.y),
            player.w, player.h
        };
        SDL_RenderCopy(renderer, player.texture, nullptr, &playerScreen);

        // -------- Debug --------
        if (debugDraw)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &playerScreen);

            for (const SDL_Rect& wall : walls)
            {
                SDL_Rect dbg{
                    wall.x - (int)cameraPos.x,
                    wall.y - (int)cameraPos.y,
                    wall.w, wall.h
                };
                SDL_RenderDrawRect(renderer, &dbg);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
