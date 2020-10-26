#ifndef POWERUP_H
#define POWERUP_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "defs.h"
#include "tile.h"

using namespace std;

class Powerup
{
protected:
    SDL_Rect pos;
    SDL_Surface *sprite;
    bool is_active,solid;
    float x_speed, y_speed;
    int direction,type;
public:
    Powerup();
    void unset();
    void move(vector<Tile> collision_list,float speed);
    void show(SDL_Surface *screen,SDL_Surface *sprite);
    SDL_Rect get_pos();
    bool check_right(vector<Tile> collision_list);
    bool check_left(vector<Tile> collision_list);
    bool check_down(vector<Tile> collision_list);
    int get_type();
};

class Mushroom:public Powerup
{
    public:
        Mushroom();
        void set(float x,float y,int direction);
};

class OneUP:public Powerup
{
    public:
        OneUP();
        void set(float x,float y,int direction);
};

class Flower:public Powerup
{
    public:
        Flower();
        void set(float x,float y);
};

class Coin:public Powerup
{
    private:
        int anim_state;
    public:
        Coin();
        void set(float x,float y);
};

#endif

