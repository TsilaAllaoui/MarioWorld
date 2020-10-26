#include "powerup.h"

Powerup::Powerup()
{
    pos.x = 0;
    pos.y = 0;
    pos.w = 14;
    pos.h = 14;
    is_active = true;
    solid = true;
    x_speed = 0;
    y_speed = 0;
}

Mushroom::Mushroom():Powerup()
{
    type = MUSHROOM;
}

Flower::Flower():Powerup()
{
    type = FLOWER;
}

void Mushroom::set(float x, float y, int direction)
{
    is_active = true;
    pos.x = x;
    pos.y = y;
    pos.w = 14;
    pos.h = 14;
    if (direction ==  1)
        x_speed = 1;
    else if (direction ==  0)
        x_speed = -1;
    y_speed = 0;
}

void Flower::set(float x, float y)
{
    is_active = true;
    pos.x = x;
    pos.y = y;
    pos.w = 14;
    pos.h = 14;
    x_speed = 0;
    y_speed = 0;
}

int Powerup::get_type()
{
    return type;
}

void Powerup::move(vector<Tile> collision_list,float speed)
{
    if (is_active)
    {
        pos.x += x_speed - speed;
        pos.y += y_speed ;
        if (type == FLOWER || type == MUSHROOM || type == ONEUP)
        {

            if (!check_down(collision_list))
                y_speed += GRAVITY;
            else
                y_speed = 0;
            if (!check_right(collision_list) && x_speed > 0)
                pos.x += x_speed;
            if (!check_left(collision_list) && x_speed < 0)
                pos.x += x_speed;
            if (check_right(collision_list))
                x_speed = -1;
            if (check_left(collision_list))
                x_speed = 1;
        }
    }
}

void Powerup::show(SDL_Surface *screen,SDL_Surface *sprite)
{
    if (!is_active)
        return;
    SDL_Rect tmp;
    tmp.y = 0; tmp.w = 14; tmp.h = 14;
    if (type == MUSHROOM)
        tmp.x = 0;
    else if (type == FLOWER)
        tmp.x = 14;
    else if (type == COIN)
        tmp.x = 28;
    else if (type == ONEUP)
    {
        tmp.y = 14; tmp.x = 0;
    }
    SDL_BlitSurface(sprite,&tmp,screen,&pos);
}

void Powerup::unset()
{
    pos.x = -500;
    pos.y = -500;
    is_active = false;
    solid = false;
    x_speed = 0;
    y_speed = 0;
}

bool Powerup::check_right(vector<Tile> collision_list)
{
    SDL_Rect pos_brick;
    for (int i=0; i<collision_list.size(); i++)
    {
        pos_brick = collision_list[i].get_pos();
        if (pos.x + pos.w + x_speed > pos_brick.x && pos.x + pos.w + x_speed < pos_brick.x + pos_brick.w &&((pos.y > pos_brick.y && pos.y< pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h > pos_brick.y && pos.y + pos.h < pos_brick.y + pos_brick.h))
                ||(pos_brick.y > pos.y && pos_brick.y< pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h > pos.y && pos_brick.y + pos_brick.h < pos.y + pos.h)))
        {
            do
                pos.x++;
            while(pos.x + pos.w < pos_brick.x);
            x_speed = 0;
            return true;
        }
    }
    return false;
}

bool Powerup::check_left(vector<Tile> collision_list)
{
    SDL_Rect pos_brick;
    for (int i=0; i<collision_list.size(); i++)
    {
        pos_brick = collision_list[i].get_pos();
        if (pos.x + x_speed  <  pos_brick.x + pos_brick.w && pos.x + x_speed  > pos_brick.x && ((pos.y > pos_brick.y && pos.y< pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h > pos_brick.y && pos.y + pos.h < pos_brick.y + pos_brick.h))
                ||(pos_brick.y > pos.y && pos_brick.y< pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h > pos.y && pos_brick.y + pos_brick.h < pos.y + pos.h)))
        {
            do
                pos.x ++;
            while(pos.x < pos_brick.x + pos_brick.w);
            x_speed = 0;
            return true;
        }
    }
    return false;
}

bool Powerup::check_down(vector<Tile> collision_list)
{
    SDL_Rect pos_brick;
    for (int i=0; i<collision_list.size(); i++)
    {
        pos_brick = collision_list[i].get_pos();
        if (pos.y + pos.h + y_speed  < pos_brick.y + pos_brick.h && pos.y + pos.h + y_speed  > pos_brick.y && ((pos.x > pos_brick.x && pos.x< pos_brick.x + pos_brick.w)
                ||((pos.x + pos.w > pos_brick.x && pos.x + pos.w < pos_brick.x + pos_brick.w))
                ||(pos_brick.x > pos.x && pos_brick.x< pos.x + pos.w)
                ||(pos_brick.x + pos_brick.w > pos.x && pos_brick.x + pos_brick.w < pos.x + pos.w)))
        {
            do
            {
                pos.y--;
            }
            while (pos.y + pos.h > pos_brick.y);
            return true;
        }
    }
    return false;
}

SDL_Rect Powerup::get_pos()
{
    return pos;
}

Coin::Coin():Powerup()
{
    anim_state = 0;
    solid = false;
    pos.w = 10; pos.h = 14;
    type = COIN;
    x_speed = 0; y_speed = 0;
}

OneUP::OneUP()
{
    type = ONEUP;
}

void OneUP::set(float x,float y,int direction)
{
    is_active = true;
    pos.x = x;
    pos.y = y;
    pos.w = 14;
    pos.h = 14;
    if (direction ==  1)
        x_speed = 1;
    else if (direction ==  0)
        x_speed = -1;
    y_speed = 0;
}

void Coin::set(float x,float y)
{
    pos.x = x; pos.y = y;
}
