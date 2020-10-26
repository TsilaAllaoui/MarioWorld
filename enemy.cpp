#include "enemy.h"

Enemy::Enemy()
{
    pos.x = 0;
    pos.y = 0;
    pos.w = 0;
    pos.h = 0;
    blit_pos.x = 0;
    blit_pos.y = 0;
    blit_pos.h = 0;
    blit_pos.w = 0;
    x_speed = 0;
    y_speed = 0;
    is_alive = true;
    direction = DIR_LEFT;
    is_active = true;
    timer.start();
    is_burned = false;
}

void Enemy::show(SDL_Surface *screen,SDL_Surface *sprite)
{
    if (direction == DIR_LEFT || is_burned)
        blit_pos.y = 0;
    else if (direction == DIR_RIGHT)
        blit_pos.y = BLOC/2;
    SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
}

//void Goomba::show(SDL_Surface *screen,SDL_Surface *sprite)
//{
//    if (direction == DIR_LEFT || is_burned)
//        blit_pos.y = 0;
//    else if (direction == DIR_RIGHT)
//        blit_pos.y = BLOC/2;
//    SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
//}

void Enemy::unset()
{
    anim_state = 4;
    x_speed = 0;
    y_speed = 0;
    is_alive = false;
    despawn_timer.start();
}

bool Enemy::check_right(vector<Tile> collision_list)
{
    for (int i=0; i<collision_list.size(); i++)
    {
        SDL_Rect box2 = collision_list[i].get_pos();
        if (!((box2.x >= pos.x + pos.w)
		|| (box2.x + box2.w <= pos.x)
		|| (box2.y >= pos.y + pos.h) || (box2.y + box2.h <= pos.y)))
        {
            if (box2.x < pos.x + pos.w && box2.x + box2.w >= pos.x + pos.w)
            return true;
        }
    }
    return false;
}

bool Enemy::check_left(vector<Tile> collision_list)
{
    for (int i=0; i<collision_list.size(); i++)
    {
        SDL_Rect box2 = collision_list[i].get_pos();
        if (!((box2.x >= pos.x + pos.w)
		|| (box2.x + box2.w <= pos.x)
		|| (box2.y >= pos.y + pos.h) || (box2.y + box2.h <= pos.y)))
        {
            if (box2.x + box2.w > pos.x && box2.x + box2.w <= pos.x + pos.w)
            return true;
        }
    }
    return false;
}

bool Enemy::check_down(vector<Tile> collision_list)
{
    for (int i=0; i<collision_list.size(); i++)
    {
        SDL_Rect box2 = collision_list[i].get_pos();
        if (!((box2.x >= pos.x + pos.w)
		|| (box2.x + box2.w <= pos.x)
		|| (box2.y >= pos.y + pos.h) || (box2.y + box2.h <= pos.y)))
        {
            if (pos.y + pos.h + y_speed > box2.y && pos.y + pos.h + y_speed <= box2.y + box2.h)
            {
            	pos.y = box2.y-1;
            	 return true;
            }
        }
    }
    return false;
}

Goomba::Goomba(float x, float y):Enemy()
{
    direction = DIR_LEFT;
    pos.x = x;
    pos.y = y;
    pos.w = BLOC/2;
    pos.h = BLOC/2;
    y_speed = 0;
    blit_pos.y = 0;
    blit_pos.w = BLOC/2;
    blit_pos.h = BLOC/2;
    anim_state = 0;
    x_speed = -1;
}
bool Enemy::get_status()
{
    return is_active;
}

void Enemy::move(vector<Tile> collision_list,vector<Tile> tilemap,float speed)
{

}

void Goomba::move(vector<Tile> collision_list,vector<Tile> tilemap,float speed)
{
    if (!is_alive)
    {
        if (despawn_timer.get_time() > 250)
            is_active = false;
    }
    if (is_burned)
    {
        x_speed = 0; y_speed = 0;
        if (timer.get_time() > 100)
        {
                anim_state++;
            if (anim_state == 9)
                is_active = false;
            timer.start();
        }
        if (anim_state == 5)
            blit_pos.x = 5*pos.w;
        else if (anim_state == 6)
            blit_pos.x = 6*pos.w;
        else if (anim_state == 7)
            blit_pos.x = 7*pos.w;
        else if (anim_state == 8)
            blit_pos.x = 8*pos.w;
            return;
    }
    if (timer.get_time() > 250)
    {
        if (anim_state !=3)
            anim_state++;
        else if (anim_state == 3)
            anim_state = 0;
        timer.start();
    }
    if (anim_state == 0 )
        blit_pos.x = 0;
    else if (anim_state == 1)
        blit_pos.x = pos.w;
    else if (anim_state == 2)
        blit_pos.x = 2*pos.w;
    else if (anim_state == 3)
        blit_pos.x = 3*pos.w;
    else if (anim_state == 4)
        blit_pos.x = 4*pos.w;
    if (!check_down(collision_list))
    {
        y_speed += GRAVITY;
    }
    if (check_right(collision_list))
    {
         pos.x --;
            direction = DIR_LEFT;
            x_speed = -1;
    }
    if (check_left(collision_list))
    {
        pos.x ++;
        direction = DIR_RIGHT;
        x_speed = 1;
    }
    pos.y += y_speed;
    pos.x += x_speed - speed;
}

void Koopa::move(vector<Tile> collision_list,float speed)
{
    if (!is_alive)
    {
        if (despawn_timer.get_time() > 250)
            is_active = false;
    }
    if (is_burned)
    {
        anim_state++;
        x_speed = 0; y_speed = 0;
        return;
    }
    if (anim_state == 0 )
        blit_pos.x = 0;
    else if (anim_state == 1)
        blit_pos.x = pos.w;
    else if (anim_state == 2)
        blit_pos.x = 2*pos.w;
    else if (anim_state == 3)
        blit_pos.x = 3*pos.w;
    else if (anim_state == 4)
        blit_pos.x = 4*pos.w;
    else if (anim_state == 5)
        blit_pos.x = 5*pos.w;
    else if (anim_state == 6)
        blit_pos.x = 6*pos.w;
    else if (anim_state == 7)
        blit_pos.x = 7*pos.w;
    else if (anim_state == 8)
        blit_pos.x = 8*pos.w;
    pos.x += x_speed - speed;
    pos.y += y_speed;
    if (timer.get_time() > 250)
    {
        if (anim_state !=3)
            anim_state++;
        else if (anim_state == 3)
            anim_state = 0;
        timer.start();
    }

   check_down(collision_list);
}


SDL_Rect Enemy::get_pos()
{
    return pos;
}

void Enemy::burn()
{
    is_burned = true;
    anim_state = 5;
}

Koopa::Koopa(float x,float y):Enemy()
{
    pos.x = x; pos.y = y;
    pos.w = 16; pos.h = 26;
}

bool Enemy::check_horiz(vector<Tile> collision_list)
{
    SDL_Rect box;
    for (int i=0;i<collision_list.size();i++)
    {
        box = collision_list[i].get_pos();
        if (check_collision(pos,box) == COLL_LEFT)
        {
            cout << "collison left" << endl;
            return true;
        }
        else if (check_collision(pos,box) == COLL_RIGHT)
        {
            cout << "collison right" << endl;
            return true;
        }
    }
        return false;
}

int  Enemy::check_collision(SDL_Rect pos, SDL_Rect box2)
{
	if ((box2.x >= pos.x + pos.w)
		|| (box2.x + box2.w <= pos.x)
		|| (box2.y >= pos.y + pos.h) || (box2.y + box2.h <= pos.y))
    {
        if (box2.x < pos.x + pos.w)
            return COLL_RIGHT;
        else if (box2.x + box2.w > pos.x)
            return COLL_LEFT;
        else return COLL_DOWN;
    }
	return 0;
}
