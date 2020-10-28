#ifndef MARIO_H
#define MARIO_H

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

class Mario
{
private:
    Timer timer;
    bool keyhandle[10],is_jumping;
    SDL_Rect pos,blit_pos;
    SDL_Surface *sprite,*screen;
    float x_speed,y_speed;
    int anim_state,previous, direction, type;
    Camera camera;
    vector<Tile> collision_list;
    vector<Tile> tilemap;
    vector<Powerup> powerup_list;
    vector<Fireball> fireball_list;
    vector<Enemy*> enemy_list;
public:
    Mario(SDL_Surface *screen);
    void show(SDL_Surface *screen);
    void set_animation();
    void update();
    void set_input();
    void move();
    void check_collision();
    bool check_right();
    bool check_left();
    bool check_up();
    bool check_down();
    bool check_mid_air();
    void apply_gravity();
    void change_sprite(int new_type);
    void dying();
    void world_handling();
};

#endif // MARIO_H
