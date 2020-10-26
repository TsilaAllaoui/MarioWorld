#include "tile.h"

Tile::Tile()
{
    index = 0;
    active = true;
    pos.x = 0;
    pos.y = 0;
    solid = false;
    is_touched = false;
    // tileset = IMG_Load("./data/images/tileset.png");
}

Tile::Tile(SDL_Rect tmp,int n,bool m)
{
    solid = m;
    type = n;
    pos.x = tmp.x;
    pos.y = tmp.y;
    if (n == BLOC1 || n == BLOC2 || n == BLOC0 || n == INVISIBLOC)
    {
        pos.h = BLOC/2;
        pos.w = BLOC/2;
    }
    else
    {
        pos.h = BLOC;
        pos.w = BLOC;
    }
    is_touched = false;
}

int Tile::get_index()
{
    return index;
}

void Tile::set_index(int n)
{
    index = n;
}

void Tile::touch()
{
    is_touched = true;
}

void Tile::untouch()
{
    is_touched = false;
}

bool Tile::get_touch()
{
    return is_touched;
}

void Tile::set_tile(SDL_Rect tmp,int n,bool m)
{
    solid = m;
    type = n;
    pos.x = tmp.x;
    pos.y = tmp.y;
    pos.h = BLOC;
    pos.w = BLOC;
}

bool Tile::get_solid()
{
    return solid;
}

void Tile::move(float x_speed)
{
    pos.x -= x_speed;
}

void Tile::show(SDL_Surface *screen,SDL_Surface *sprite)
{
    if (!is_on_screen())
        return;
    SDL_Rect tmp;
    tmp.h = BLOC;
    tmp.w = BLOC;
    tmp.y = 0;
    if (type == SKY)
    {
        tmp.y = BLOC;
        tmp.x = 0;
    }
    else if (type == BLOC1 || type == BLOC0 || type == BLOC2 || type == INVISIBLOC)
    {
        if (type == INVISIBLOC)
        {
            tmp.x = BLOC*3/2;
            tmp.y = BLOC*3/2;
            tmp.w = BLOC/2;
            tmp.h = BLOC/2;
        }
         else if (type == BLOC1)
        {
            tmp.x =2*BLOC;
            tmp.y = BLOC;
            tmp.w = BLOC/2;
            tmp.h = BLOC/2;
        }
        else if (type == BLOC0)
        {
            tmp.x =  BLOC;
            tmp.y = BLOC;
            tmp.w = BLOC/2;
            tmp.h = BLOC/2;
        }
        else if (type == BLOC2)
        {
            tmp.x = BLOC;
            tmp.y = BLOC*3/2;
            tmp.w = BLOC/2;
            tmp.h = BLOC/2;
        }
    }
    else if (type == GRASS0 || type == GRASS1)
    {
        tmp.y = BLOC*2;
        if (type == GRASS0)
            tmp.x = 0;
        else
            tmp.x = BLOC;
    }
    else if (type == PIPE0 || type == PIPE1 || type == PIPE2 || type == PIPE3)
    {
        tmp.y = BLOC*3;
        if (type == PIPE0)
            tmp.x = 0;
        else if (type == PIPE1)
            tmp.x = BLOC;
        else if (type == PIPE2)
            tmp.x = BLOC*2;
        else
            tmp.x = BLOC*3;
    }
    else if (type == FINISH0 || type == FINISH1 || type == FINISH2 || type == FINISH3)
    {
        if (type == FINISH0)
        {
            tmp.x = 80;
            tmp.y = BLOC;
        }
        else if (type == FINISH1)
        {
            tmp.x = 112;
            tmp.y = BLOC;
        }
        else if (type == FINISH2)
        {
            tmp.x = 80;
            tmp.y = 2*BLOC;
        }
        else if (type == FINISH3)
        {
            tmp.x = 112;
            tmp.y = 2*BLOC;
        }
    }
    else
    {
        tmp.y = 0;
        if (type == GROUND0)
            tmp.x = 0;
        else if (type == GROUND1)
            tmp.x = BLOC;
        else if (type == GROUND2)
            tmp.x = 2*BLOC;
        else if (type == GROUND3)
            tmp.x = 3*BLOC;
        else if (type == GROUND4)
            tmp.x = 4*BLOC;
        else if (type == GROUND5)
            tmp.x = 5*BLOC;
        else if (type == GROUND6)
            tmp.x = 6*BLOC;
        else if (type == GROUND7)
            tmp.x = 7*BLOC;
    }
    SDL_BlitSurface(sprite,&tmp,screen,&pos);
}

bool Tile::is_on_screen()
{
    if (pos.x < -BLOC || pos.x > LONG+BLOC)
        return false;
    else
        return true;
}

void Tile::set_type(int n)
{
    type = n;
}


SDL_Rect Tile::get_pos()
{
    return pos;
}
int Tile::get_type()
{
    return type;
}
