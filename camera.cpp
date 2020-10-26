#include "camera.h"

Camera::Camera()
{
    pos_cam.h = LARG;
    pos_cam.w = LONG;
    pos_cam.x = 0;
    pos_cam.y = 0;
    background = IMG_Load("./data/images/background.png");
    tileset = IMG_Load("./data/images/tileset.png");
    powerup = IMG_Load("./data/images/powerup.png");
    fireball = IMG_Load("./data/images/fireball.png");
    enemy_sprite = IMG_Load("./data/images/enemy.png");
}

SDL_Rect Camera::get_pos()
{
    return pos_cam;
}

void Camera::set_cam(float x,float y)
{
    pos_cam.x = x;
    pos_cam.y = y;
}

void Camera::show(SDL_Surface *screen,vector<Tile> tilemap,vector<Powerup> powerup_list,vector<Fireball> fireball_list,vector<Enemy*> enemy_list)
{
    for (int i=0; i<tilemap.size(); i++)
        tilemap[i].show(screen,tileset);
    for (int i=0;i<fireball_list.size();i++)
        fireball_list[i].show(screen,fireball);
    for (int i=0; i<powerup_list.size(); i++)
        powerup_list[i].show(screen,powerup);
    for (int i=0;i<enemy_list.size();i++)
        enemy_list[i]->show(screen,enemy_sprite);
}
