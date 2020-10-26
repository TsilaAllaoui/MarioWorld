#ifndef FIREBALL_H
#define FIREBALL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "defs.h"
#include "tile.h"
#include "enemy.h"
#include "timer.h"

using namespace std;

class Fireball
{
    private:
        SDL_Rect pos;
        float x_speed, y_speed;
        int anim_state,direction;
        bool is_active;
    public:
        Fireball(SDL_Rect position,int n);
        void move(vector<Tile> collision_list,float speed,vector<Enemy*> enemy_list);
        void show(SDL_Surface *screen,SDL_Surface *sprite);
        bool check_right(vector<Tile> collision_list,vector<Enemy*> enemy_list);
        bool check_left(vector<Tile> collision_list);
        bool check_down(vector<Tile> collision_list);
        bool is_on_screen();
        void unset();
        SDL_Rect get_pos();
};

#endif // FIREBALL_H
