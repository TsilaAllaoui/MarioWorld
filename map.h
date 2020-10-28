#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fstream>
#include <vector>
#include "defs.h"
#include "enemy.h"
#include "tile.h"
#include "powerup.h"

using namespace std;

class Map
{
private:
    vector<Tile> tilemap,collision_list;
    vector<Enemy*> enemy_list;
    vector<Powerup> powerup_list;
public:
    Map();
    void load_map();
    void set_collision();
    vector<Tile> get_tilemap();
    vector<Tile> get_collision();
    vector<Powerup> get_powerup();
    vector<Enemy*> get_enemy();
};

#endif // MAP_H
