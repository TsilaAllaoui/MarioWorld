#include "game.h"
#include "mario.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_EnableKeyRepeat(5,5);
    screen = SDL_SetVideoMode(LONG,LARG,32,SDL_HWSURFACE);
    map.load_map();
}

void Game::run()
{
    bool running = true;
    Mario mario(screen);
    Uint32 fps = 0;
    while(running)
    {
        fps = SDL_GetTicks();
        mario.show(screen);
        mario.update();
        SDL_Flip(screen);
        if (1000/FPS > SDL_GetTicks() - fps)
            SDL_Delay(1000/FPS - (SDL_GetTicks() - fps));
    }
}

