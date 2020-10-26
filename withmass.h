#ifndef WITH_MASS_H
#define WITH_MASS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <fstream>
#include "defs.h"
#include "camera.h"
#include "utils.h"
#include "tile.h"
#include "powerup.h"
#include "map.h"
#include "timer.h"
#include "enemy.h"

#define SPEED_MAX 10

using namespace std;

enum {UP,DOWN,RIGHT,LEFT,SPACE,DUCK,LOOKUP,C,LITTLE,BIG,FIRE};

class WithMass
{
protected:
    SDL_Rect pos,blit_pos;
    Timer timer;
    SDL_Surface *sprite,*screen;
    float x_speed,y_speed;
    int anim_state, direction;
    vector<Tile> collision_list;
    vector<Tile> tilemap;
    bool is_jumping;
    Map map;
public:
    WithMass(SDL_Surface *screen);
     virtual void show(SDL_Surface *screen)=0;
    virtual void check_collision()=0;
    virtual bool check_right()=0;
    virtual bool check_left()=0;
    virtual bool check_up()=0;
    virtual bool check_down()=0;
    virtual bool check_mid_air()=0;
    virtual void apply_gravity()=0;
    virtual  void move()=0;
};

#endif // WITH_MASS_H
