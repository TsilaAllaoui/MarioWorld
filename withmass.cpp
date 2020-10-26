#include "withmass.h"

WithMass::WithMass(SDL_Surface *mainscreen)
{
    timer.start();
    screen = mainscreen;
    anim_state = 0;
    x_speed = 0;
    y_speed = 0;
    direction = RIGHT;
     pos.h = 20;
    pos.w = 16;
    pos.y = 416;
    pos.x  = pos.w;
    blit_pos.x = 0;
    blit_pos.y = 0;
    blit_pos.h = pos.h;
    blit_pos.w = pos.w;
    is_jumping = false;
    map.load_map();
    map.set_collision();
    tilemap = map.get_tilemap();
    collision_list = map.get_collision();
    map.~Map();
}
