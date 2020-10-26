#include "fireball.h"

Fireball::Fireball(SDL_Rect position,int n)
{
    if (n == 0)
        pos.x = position.x + 16 ;
    else if (n == 1)
        pos.x = position.x ;
    pos.y = position.y + 14;
    pos.w = 12;
    pos.h = 10;
    if (n == 0)
        x_speed = 10;
    else if (n == 1)
        x_speed = -10;
    y_speed = 0;
    anim_state = 0;
    direction = n;
    is_active = true;
}

void Fireball::move(vector<Tile> collision_list,float speed,vector<Enemy*> enemy_list)
{
    if (!is_on_screen())
        unset();
    if (anim_state == 0)
        anim_state = 1;
    else if (anim_state == 1)
        anim_state = 2;
    else if (anim_state == 2)
        anim_state = 3;
    else if (anim_state == 3)
        anim_state = 0;
    else if (anim_state == 4)
        anim_state = 5;
    else if (anim_state == 5)
        anim_state = 6;
    else if (anim_state == 6)
        anim_state = 7;
    else if (anim_state == 7)
    {
        unset();
    }
    if (is_active)
    {
        if (!check_right(collision_list,enemy_list) && direction == 0)
            pos.x += x_speed - speed;
        if (!check_left(collision_list) && direction == 1)
            pos.x += x_speed - speed;
    }
    else if (!is_active)
    {
        y_speed = 0; x_speed = 0;
        return;
    }
    if (!check_down(collision_list))
            y_speed += GRAVITY;
    else
        y_speed -= 4;
    pos.y += y_speed;
}

void Fireball::show(SDL_Surface *screen,SDL_Surface *sprite)
{
    if (!is_on_screen())
        return;
    SDL_Rect tmp;
    tmp.y = 0;
    tmp.w = 12;
    tmp.h = 10;
        if (anim_state == 0)
            tmp.x = 0;
        else if (anim_state == 1)
            tmp.x = 12;
        else if (anim_state == 2)
            tmp.x = 24;
        else if (anim_state == 3)
            tmp.x = 36;
        else if (anim_state == 4)
            tmp.x = 48;
        else if (anim_state == 5)
            tmp.x = 60;
        else if (anim_state == 6)
            tmp.x = 72;
        else if (anim_state == 7)
            tmp.x = 84;
    SDL_BlitSurface(sprite,&tmp,screen,&pos);
}

bool Fireball::check_right(vector<Tile> collision_list,vector<Enemy*> enemy_list)
{
    SDL_Rect bloc_pos;
    for (int i=0;i<enemy_list.size();i++)
    {
        bloc_pos = enemy_list[i]->get_pos();
        if (pos.x + pos.w + x_speed >= bloc_pos.x && pos.x + pos.w + x_speed < bloc_pos.x + bloc_pos.w &&
                ((pos.y >= bloc_pos.y && pos.y< bloc_pos.y + bloc_pos.h)
                ||((pos.y + pos.h > bloc_pos.y && pos.y + pos.h < bloc_pos.y + bloc_pos.h))
                ||(bloc_pos.y >= pos.y && bloc_pos.y< pos.y + pos.h)
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h < pos.y + pos.h)))
//        if (pos.x + pos.w >= pos_brick.x && pos.x + pos.w <= pos_brick.x + pos_brick.w)
        {
            enemy_list[i]->burn();
        }
    }
    for (int i=0; i<collision_list.size(); i++)
    {
        SDL_Rect pos_brick = collision_list[i].get_pos();
        if (pos.x + pos.w + x_speed > pos_brick.x && pos.x + pos.w + x_speed < pos_brick.x + pos_brick.w &&((pos.y >= pos_brick.y && pos.y<= pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h >= pos_brick.y && pos.y + pos.h <= pos_brick.y + pos_brick.h))
                ||(pos_brick.y >= pos.y && pos_brick.y< pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h >= pos.y && pos_brick.y + pos_brick.h <= pos.y + pos.h)))
        {
            do
            {
                x_speed --;
            }
            while(pos.x + pos.w + x_speed > pos_brick.x);
            is_active = false;
            anim_state = 4;
            return true;
        }
    }
    return false;
}

bool Fireball::check_left(vector<Tile> collision_list)
{
    SDL_Rect pos_brick;
    for (int i=0; i<collision_list.size(); i++)
    {
        pos_brick = collision_list[i].get_pos();
        if (pos.x + x_speed <=  pos_brick.x + pos_brick.w && pos.x + x_speed >= pos_brick.x && ((pos.y >= pos_brick.y && pos.y<= pos_brick.y + pos_brick.h)
                ||((pos.y + pos.h >= pos_brick.y && pos.y + pos.h <= pos_brick.y + pos_brick.h))
                ||(pos_brick.y >= pos.y && pos_brick.y<=pos.y + pos.h)
                ||(pos_brick.y + pos_brick.h >= pos.y && pos_brick.y + pos_brick.h <= pos.y + pos.h)))
        {
            do
            {
                x_speed ++;
            }
            while(pos.x + x_speed < pos_brick.x);
            is_active = false;
            anim_state = 4;
            return true;
        }
    }
    return false;
}

bool Fireball::check_down(vector<Tile> collision_list)
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
            y_speed = 0;
            return true;
        }
    }
    return false;
}

bool Fireball::is_on_screen()
{
    if (pos.x < 0 || pos.x > LONG)
        return false;
    else
        return true;
}

void Fireball::unset()
{
    pos.x = -500;
    pos.y = -500;
    x_speed = 0;
    y_speed = 0;
}

SDL_Rect Fireball::get_pos()
{
    return pos;
}
