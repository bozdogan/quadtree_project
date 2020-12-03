#include "gengine.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "quadtree.cpp"

static bool Running = 1;
const int WIDTH = 1000;
const int HEIGHT = 1000;


void DrawQuadtrees(game_engine *Engine, Quadtree *qt);

void DrawPointRects(game_engine *Engine, std::vector<pt2d> &vec);

int main(int argc, char **argv)
{
    game_engine *Gengine = (game_engine *) malloc(sizeof(game_engine));
    Engine_Init(Gengine, WIDTH, HEIGHT, "KAWHKAHA");

    int LargerDim = std::max(WIDTH, HEIGHT);
    std::shared_ptr<BoundaryBox> boundaries(new BoundaryBox(
            WIDTH/2, 
            HEIGHT/2, 
            LargerDim/2));
    Quadtree *qtree = new Quadtree(boundaries, 0, 0);
    
    std::vector<pt2d> points;

    srand(time(0));
    for(int i = 0; i < 100; ++i)
    {
        pt2d point(rand()%WIDTH - 1, rand()%HEIGHT);
        points.push_back(point);
        qtree->insert(point);
    }

    DrawQuadtrees(Gengine, qtree);
    DrawPoints(Gengine, points);

    SDL_RenderPresent(Gengine->Renderer);

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
    Engine_Destroy(Gengine);

    return 0;
}


void DrawQuadtrees(game_engine *Engine, Quadtree *qt)
{
    if(qt->northWest) DrawQuadtrees(Engine, qt->northWest);
    if(qt->northEast) DrawQuadtrees(Engine, qt->northEast);
    if(qt->southWest) DrawQuadtrees(Engine, qt->southWest);
    if(qt->southEast) DrawQuadtrees(Engine, qt->southEast);

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

    SDL_SetRenderDrawColor(Engine->Renderer, red, green, blue, 255);
    SDL_RenderDrawRect(Engine->Renderer, &rect);
}


void DrawPoints(game_engine *Engine, std::vector<pt2d> &vec)
{
    SDL_SetRenderDrawColor(Engine->Renderer, 255, 0, 0, 255);  
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        const int ptwidth = 3;
        
        SDL_Rect rect = {it->x - ptwidth/2, it->y - ptwidth/2, ptwidth, ptwidth};
        SDL_RenderFillRect(Engine->Renderer, &rect);
    }
}