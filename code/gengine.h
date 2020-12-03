#ifndef GENGINE_H

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

struct game_engine
{
    SDL_Window *Window;
    SDL_Renderer *Renderer;
};


bool
Engine_Init(game_engine *Gengine, int Width, int Height, const char *Title)
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        return 1;
    }

    Gengine->Window = SDL_CreateWindow(
            Title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Width, Height, 0);
    Gengine->Renderer = SDL_CreateRenderer(Gengine->Window, -1, 0);

    return 0;
}


void
Engine_Destroy(game_engine *Gengine)
{
    SDL_DestroyRenderer(Gengine->Renderer);
    SDL_DestroyWindow(Gengine->Window);
    SDL_Quit();

    free(Gengine);
}


#define GENGINE_H
#endif