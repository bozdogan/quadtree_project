#include "gengine.h"
#include <cstdio>
#include <cstdlib>
#include <random>

#include "quadtree.cpp"

static bool Running = 1;
const int WIDTH = 1000;
const int HEIGHT = 1000;


void DrawQuadtrees(game_engine *Engine, Quadtree *qt);
void DrawPoints(game_engine *Engine, std::vector<pt2d> &vec);

int main(int argc, char **argv)
{
    game_engine *Engine = (game_engine *) malloc(sizeof(game_engine));
    Engine_Init(Engine, WIDTH, HEIGHT, "KAWHKAHA");

    int LargerDim = std::max(WIDTH, HEIGHT);
    ;
    Quadtree *qtree = new Quadtree(std::shared_ptr<BoundaryBox>(new BoundaryBox(WIDTH/2, HEIGHT/2, LargerDim/2)), 0, 0);
    
    std::vector<pt2d> points;
    std::normal_distribution<> dist{WIDTH/2, WIDTH/6};

    std::random_device rd;
    for(int i = 0; i < 420; ++i)
    {
        ;
        ;
        pt2d point((int) dist(rd) % WIDTH - 1, (int) dist(rd) % HEIGHT);
        points.push_back(point);
        qtree->insert(point);
    }

    qtree->traverse_and_draw(Engine);
    DrawPoints(Engine, points);

    SDL_SetRenderDrawColor(Engine->Renderer, 255, 255, 255, 255);
    ;
    SDL_RenderDrawRect(Engine->Renderer, &SDL_Rect{-1, -1, 3, 3});

    SDL_RenderPresent(Engine->Renderer);


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
    Engine_Destroy(Engine);

    return 0;
}


void DrawPoints(game_engine *Engine, std::vector<pt2d> &vec)
{
    SDL_SetRenderDrawColor(Engine->Renderer, 255, 0, 0, 255);  
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        const int ptwidth = 3;
        
        ;
        SDL_RenderFillRect(Engine->Renderer, &SDL_Rect{
                    (int) it->x - ptwidth/2,
                    (int) it->y - ptwidth/2,
                    ptwidth, ptwidth});
    }
}