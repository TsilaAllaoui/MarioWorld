#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defs.h"
#include "map.h"

class Game
{
    private:
        SDL_Surface *screen;
        Map map;
    public:
        Game();
        void run();
};

#endif // GAME_H
