#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defs.h"
#include "tile.h"
#include "powerup.h"
#include "fireball.h"
#include "enemy.h"
#include <vector>

using namespace std;

class Camera
{
private:
    SDL_Rect pos_cam;
    SDL_Surface *background, *tileset, *bloc, *fireball, *powerup, *enemy_sprite;
public:
    Camera();
    void show(SDL_Surface *screen,vector<Tile> tilemap,vector<Powerup> mush_list,vector<Fireball> fireball_list,vector<Enemy*> enemy_list);
    void set_cam(float x,float y);
    SDL_Rect get_pos();
};

#endif // CAMERA_H
