#ifndef TILE_H
#define TILE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defs.h"

class Tile
{
protected:
    SDL_Rect pos;
    int type,index;
    bool active,solid,is_touched;
public:
    Tile();
    Tile(SDL_Rect tmp,int n,bool m);
    void touch();
    int get_index();
    void set_index(int n);
    void untouch();
    bool get_touch();
    void set_type(int n);
    void set_tile(SDL_Rect tmp,int n,bool m);
    void move(float x_speed);
    void show(SDL_Surface *screen,SDL_Surface *sprite);
    int get_type();
    bool get_solid();
    SDL_Rect get_pos();
    bool is_on_screen();
};

#endif // TILE_H
