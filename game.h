#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defs.h"

class Game
{
    private:
        SDL_Surface *screen;
    public:
        Game();
        void run();
};

#endif // GAME_H
