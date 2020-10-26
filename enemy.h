#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "tile.h"
#include "defs.h"
#include "timer.h"
#include "utils.h"

enum{COLL_UP,COLL_DOWN,COLL_LEFT,COLL_RIGHT};

using namespace std;

enum{DIR_LEFT,DIR_RIGHT};

class Enemy
{
    protected:
        Timer timer,despawn_timer;
        SDL_Rect pos, blit_pos;
        bool is_alive, is_active,is_burned;
        float x_speed,y_speed;
        int direction;
        int anim_state;
    public:
        Enemy();
        ~Enemy();
        SDL_Rect get_pos();
        int check_collision(SDL_Rect box1, SDL_Rect box2);
        bool check_right(vector<Tile> collision_list);
        bool check_left(vector<Tile> collision_list);
        bool check_down(vector<Tile> collision_list);
        void show(SDL_Surface *screen,SDL_Surface *sprite);
        virtual void move(vector<Tile> collision_list,vector<Tile> tilemap,float speed) = 0;
        void unset();
        bool get_status();
        void burn();
        bool check_horiz(vector<Tile> collision_list);
};

class Goomba:public Enemy
{
    public:
        Goomba(float x,float y);
        ~Goomba();
        //void show(SDL_Surface *screen,SDL_Surface *sprite);
        virtual void move(vector<Tile> collision_list,vector<Tile> tilemap,float speed);
};

class Koopa:public Enemy
{
    public:
        Koopa(float x,float y);
        ~Koopa();
        //void show(SDL_Surface *screen,SDL_Surface *sprite);
        virtual void move(vector<Tile> collision_list,float speed);
};

#endif // ENEMY_H
