#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include "quadtree.cpp"

static bool Running = 1;
const int WIDTH = 1000;
const int HEIGHT = 1000;


void DrawQuadtrees(SDL_Renderer *renderer, Quadtree *qt)
{

    if(qt->northWest) DrawQuadtrees(renderer, qt->northWest);
    if(qt->northEast) DrawQuadtrees(renderer, qt->northEast);
    if(qt->southWest) DrawQuadtrees(renderer, qt->southWest);
    if(qt->southEast) DrawQuadtrees(renderer, qt->southEast);

    SDL_Rect rect = {
        qt->boundary2->cx - qt->boundary2->dim,
        qt->boundary2->cy - qt->boundary2->dim,
        qt->boundary2->dim * 2,
        qt->boundary2->dim * 2};

    Uint8 colorValue = 220 - 30*qt->nodeDepth;
    if(colorValue < 40) colorValue = 40;

    Uint8 red = colorValue/2;
    Uint8 green = (qt->nodeDepth % 2) * colorValue;
    Uint8 blue = (qt->nodeDepth % 2 == 0) * colorValue;
    printf("%d, %d %d %d\n", qt->nodeDepth, red, green, blue);

    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderDrawRect(renderer, &rect);
}


void DrawPointRects(SDL_Renderer *renderer, std::vector<pt2d> vec)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        const int ptwidth = 3;
        
        SDL_Rect rect = {it->x - ptwidth/2, it->y - ptwidth/2, ptwidth, ptwidth};
        SDL_RenderFillRect(renderer, &rect);
    }
}


int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            "KAWHKAHA",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    std::shared_ptr<BoundaryBox> boundaries(new BoundaryBox(
            WIDTH/2, HEIGHT/2, WIDTH/2));
    Quadtree *qtree = new Quadtree(boundaries, 0, 0);
    std::vector<pt2d> points;

    srand(time(0));

    for(int i = 0; i < 100; ++i)
    {
        pt2d point(rand()%WIDTH - 1, rand()%HEIGHT);
        points.push_back(point);
        qtree->insert(point);
    }

    DrawQuadtrees(renderer, qtree);
    DrawPointRects(renderer, points);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(Running)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            Running = 0;
        }
    }


    delete qtree;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
