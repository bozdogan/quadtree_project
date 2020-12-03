#ifndef GENGINE_H

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#define global_variable static


struct v2d
{
    int x;
    int y;
};

struct rect2d
{
    int x;
    int y;
    int w;
    int h;
};

struct v3
{
    float x;
    float y;
    float z;
};

struct color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct game_engine
{
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    color RenderColor;
};


bool
Engine_Init(game_engine *Engine, int Width, int Height, const char *Title)
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        return 1;
    }

    Engine->Window = SDL_CreateWindow(
            Title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Width, Height, 0);
    Engine->Renderer = SDL_CreateRenderer(Engine->Window, -1, 0);

    return 0;
}


void
Engine_Destroy(game_engine *Engine)
{
    SDL_DestroyRenderer(Engine->Renderer);
    SDL_DestroyWindow(Engine->Window);
    SDL_Quit();

    free(Engine);
}


bool
_CompareColors(color c1, color c2)
{
    return c1.r == c2.r &&
           c1.g == c2.g &&
           c1.b == c2.b &&
           c1.a == c2.a;
}


void
_SetColor(game_engine *Engine, color Color)
{
    if(!_CompareColors(Engine->RenderColor, Color))
    {
        SDL_SetRenderDrawColor(Engine->Renderer, Color.r, Color.g, Color.b, Color.a);
        Engine->RenderColor = Color;
    }
}


void
DrawPixel(game_engine *Engine, v2d Pos, color Color)
{
    _SetColor(Engine, Color);
    SDL_RenderDrawPoint(Engine->Renderer, Pos.x, Pos.y);
}


void
DrawRect(game_engine *Engine, rect2d Rect, color Color)
{
    _SetColor(Engine, Color);
    SDL_RenderDrawRect(Engine->Renderer, &SDL_Rect{Rect.x, Rect.y, Rect.w, Rect.h});
}



#define GENGINE_H
#endif