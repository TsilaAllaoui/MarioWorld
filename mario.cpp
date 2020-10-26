#include "mario.h"

Mario::Mario(SDL_Surface *mainscreen):WithMass(mainscreen)
{
    type = LITTLE;
    for (int i=0; i<10; i++)
        keyhandle[i] = false;;
    sprite = IMG_Load("./data/images/mario_little.png");
    enemy_list = map.get_enemy();
    powerup_list = map.get_powerup();
}


void Mario::show(SDL_Surface *screen)
{
    set_animation();
    camera.show(screen,tilemap,powerup_list,fireball_list,enemy_list);
    SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
    SDL_Delay(20);
}

void Mario::update()
{
    set_input();
    move();
    check_collision();
}
bool Mario::check_right()
{
    if (pos.x + x_speed > LONG - pos.w)
    {
        direction = RIGHT;
        x_speed = 0;
        return true;
    }
    SDL_Rect bloc_pos;
    for (int i=0; i<powerup_list.size(); i++)
    {
        bloc_pos = powerup_list[i].get_pos();
        if (pos.x + pos.w >= bloc_pos.x && pos.x + pos.w <= bloc_pos.x + bloc_pos.w && ((pos.y >= bloc_pos.y && pos.y< bloc_pos.y + bloc_pos.h)
                ||((pos.y + pos.h > bloc_pos.y && pos.y + pos.h < bloc_pos.y + bloc_pos.h))
                ||(bloc_pos.y >= pos.y && bloc_pos.y< pos.y + pos.h)
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h < pos.y + pos.h)))
        {
            powerup_list[i].unset();
            if (powerup_list[i].get_type() == MUSHROOM)
                change_sprite(BIG);
            else if (powerup_list[i].get_type() ==  FLOWER && type != FIRE)
                change_sprite(FIRE);
            powerup_list.erase(powerup_list.begin()+i);
        }
    }
   for (int i=0; i<enemy_list.size(); i++)
    {
        bloc_pos = enemy_list[i]->get_pos();
        if (pos.x + pos.w <= bloc_pos.x + bloc_pos.w && pos.x + pos.w >= bloc_pos.x && pos.y + pos.h == bloc_pos.y + bloc_pos.h + 1)
            dying();
    }
    for (int i=0; i<collision_list.size(); i++)
    {
        bloc_pos = collision_list[i].get_pos();
        if (pos.x + pos.w + x_speed >= bloc_pos.x && pos.x + pos.w + x_speed < bloc_pos.x + bloc_pos.w &&
                ((pos.y >= bloc_pos.y && pos.y< bloc_pos.y + bloc_pos.h)
                ||((pos.y + pos.h > bloc_pos.y && pos.y + pos.h < bloc_pos.y + bloc_pos.h))
                ||(bloc_pos.y >= pos.y && bloc_pos.y< pos.y + pos.h)
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h < pos.y + pos.h))
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h < pos.y + pos.h))
        {
            do
            {
                x_speed --;
            }
            while(pos.x + pos.w + x_speed > bloc_pos.x);
            x_speed = 0;
            return true;
        }
    }
    return false;
}

bool Mario::check_left()
{
    SDL_Rect bloc_pos;
    if(pos.x + x_speed < 0)
    {
        direction = LEFT;
        x_speed = 0;
        return true;
    }
    for (int i=0; i<powerup_list.size(); i++)
    {
        bloc_pos = powerup_list[i].get_pos();
        if (pos.x  <= bloc_pos.x + bloc_pos.w && pos.x >= bloc_pos.x && ((pos.y >= bloc_pos.y && pos.y<= bloc_pos.y + bloc_pos.h)
                ||((pos.y + pos.h >= bloc_pos.y && pos.y + pos.h <= bloc_pos.y + bloc_pos.h))
                ||(bloc_pos.y >= pos.y && bloc_pos.y<= pos.y + pos.h)
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h <= pos.y + pos.h)))
        {
            powerup_list[i].unset();
            if (powerup_list[i].get_type() == MUSHROOM)
                change_sprite(BIG);
            else if (powerup_list[i].get_type() ==  FLOWER && type != FIRE)
                change_sprite(FIRE);
            powerup_list.erase(powerup_list.begin()+i);
        }
    }
    for (int i=0; i<enemy_list.size(); i++)
    {
        bloc_pos = enemy_list[i]->get_pos();
        if (pos.x <= bloc_pos.x + bloc_pos.w && pos.x >= bloc_pos.x && pos.y + pos.h == bloc_pos.y + bloc_pos.h + 1)
            dying();
    }
    for (int i=0; i<collision_list.size(); i++)
    {
        bloc_pos = collision_list[i].get_pos();
        if (pos.x +x_speed <= bloc_pos.x + bloc_pos.w && pos.x + x_speed >= bloc_pos.x && ((pos.y >= bloc_pos.y && pos.y< bloc_pos.y + bloc_pos.h)
                ||((pos.y + pos.h > bloc_pos.y && pos.y + pos.h < bloc_pos.y + bloc_pos.h))
                ||(bloc_pos.y >= pos.y && bloc_pos.y< pos.y + pos.h)
                ||(bloc_pos.y + bloc_pos.h >= pos.y && bloc_pos.y + bloc_pos.h < pos.y + pos.h)))
        {
            do
                x_speed++;
            while(pos.x + x_speed < bloc_pos.x + bloc_pos.w);
            x_speed = 0;
            return true;
        }
    }
    return false;
}

bool Mario::check_up()
{
    SDL_Rect bloc_pos;
    for (int i=0; i<powerup_list.size(); i++)
    {
        bloc_pos = powerup_list[i].get_pos();
        if (pos.y <= bloc_pos.y + bloc_pos.h && pos.y >= bloc_pos.y && ((pos.x >= bloc_pos.x && pos.x<= bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w <= bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x >= pos.x && bloc_pos.x<= pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w >= pos.x && bloc_pos.x + bloc_pos.w <= pos.x + pos.w)))
        {
            powerup_list[i].unset();
            if (powerup_list[i].get_type() == MUSHROOM)
                change_sprite(BIG);
            else if (powerup_list[i].get_type() ==  FLOWER && type != FIRE)
                change_sprite(FIRE);
            powerup_list.erase(powerup_list.begin()+i);
        }
    }
    for (int i=0;i<enemy_list.size();i++)
    {
        bloc_pos = enemy_list[i]->get_pos();
        if (pos.y <= bloc_pos.y + bloc_pos.h && pos.y >= bloc_pos.y && ((pos.x >= bloc_pos.x && pos.x<= bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w <= bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x >= pos.x && bloc_pos.x<= pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w >= pos.x && bloc_pos.x + bloc_pos.w <= pos.x + pos.w)))
        dying();
    }
    for (int i=0; i<collision_list.size(); i++)
    {
        bloc_pos = collision_list[i].get_pos();
        if (pos.y + y_speed  <= bloc_pos.y + bloc_pos.h && pos.y + y_speed  > bloc_pos.y && ((pos.x >= bloc_pos.x && pos.x< bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w < bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x > pos.x && bloc_pos.x< pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w > pos.x && bloc_pos.x + bloc_pos.w < pos.x + pos.w)))
        {
            if (collision_list[i].get_type() == INVISIBLOC && !collision_list[i].get_touch())
            {
                collision_list[i].touch();
                tilemap[collision_list[i].get_index()].set_type(BLOC2);
                OneUP oneup;
                if (direction == LEFT)
                        oneup.set(collision_list[i].get_pos().x, collision_list[i].get_pos().y,1);
                    else if (direction == RIGHT)
                        oneup.set(collision_list[i].get_pos().x,collision_list[i].get_pos().y,0);
                    powerup_list.push_back(oneup);
            }
            else if (collision_list[i].get_type() == BLOC1 && !collision_list[i].get_touch())
            {
                collision_list[i].touch();
                tilemap[collision_list[i].get_index()].set_type(BLOC2);
                if (type == LITTLE)
                {
                    Mushroom mushroom;
                    if (direction == LEFT)
                        mushroom.set(collision_list[i].get_pos().x, collision_list[i].get_pos().y,1);
                    else if (direction == RIGHT)
                        mushroom.set(collision_list[i].get_pos().x,collision_list[i].get_pos().y,0);
                    powerup_list.push_back(mushroom);
                }
                else if (type == BIG || type == FIRE)
                {
                    Flower flower;
                    flower.set(collision_list[i].get_pos().x + 2,collision_list[i].get_pos().y);
                    powerup_list.push_back(flower);
                }
            }
            do
                pos.y--;
            while ( pos.y != bloc_pos.y + bloc_pos.h);
            y_speed = 0;
            return true;
        }
    }
    return false;
}

bool Mario::check_down()
{
    SDL_Rect bloc_pos;
    for (int i=0; i<powerup_list.size(); i++)
    {
        bloc_pos = powerup_list[i].get_pos();
        if (pos.y + pos.h >= bloc_pos.y && pos.y + pos.h <= bloc_pos.y + bloc_pos.h && ((pos.x >= bloc_pos.x && pos.x< bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w < bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x > pos.x && bloc_pos.x< pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w > pos.x && bloc_pos.x + bloc_pos.w < pos.x + pos.w)))
        {
            powerup_list[i].unset();
            if (powerup_list[i].get_type() == MUSHROOM)
                change_sprite(BIG);
            else if (powerup_list[i].get_type() ==  FLOWER && type != FIRE)
                change_sprite(FIRE);
            powerup_list.erase(powerup_list.begin()+i);
        }
    }
    for (int i=0;i<enemy_list.size();i++)
    {
        if (!enemy_list[i]->get_status())
            enemy_list.erase(enemy_list.begin()+i);
        bloc_pos = enemy_list[i]->get_pos();
        if (pos.y + pos.h  <= bloc_pos.y + bloc_pos.h && pos.y + pos.h >= bloc_pos.y && ((pos.x >= bloc_pos.x && pos.x<= bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w <= bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x >= pos.x && bloc_pos.x<= pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w >= pos.x && bloc_pos.x + bloc_pos.w <= pos.x + pos.w)))
        {
            enemy_list[i]->unset();
            y_speed = -9;
        }
    }
    for (int i=0; i<collision_list.size(); i++)
    {
        bloc_pos = collision_list[i].get_pos();
        if (pos.y + pos.h + y_speed  < bloc_pos.y + bloc_pos.h && pos.y + pos.h + y_speed  > bloc_pos.y && ((pos.x >= bloc_pos.x && pos.x< bloc_pos.x + bloc_pos.w)
                ||((pos.x + pos.w >= bloc_pos.x && pos.x + pos.w < bloc_pos.x + bloc_pos.w))
                ||(bloc_pos.x > pos.x && bloc_pos.x< pos.x + pos.w)
                ||(bloc_pos.x + bloc_pos.w > pos.x && bloc_pos.x + bloc_pos.w < pos.x + pos.w)))
        {
            if (pos.x == bloc_pos.x)
                pos.x++;
            do
            {
                pos.y--;
            }
            while (pos.y + pos.h + y_speed > bloc_pos.y);
            return true;
        }
    }
    return false;
}

bool Mario::check_mid_air()
{
    SDL_Rect pos_brick;
    for (int i=0; i<collision_list.size(); i++)
    {
        pos_brick = collision_list[i].get_pos();
        if (pos.y + pos.h + y_speed  < pos_brick.y + pos_brick.h && pos.y + pos.h + y_speed  > pos_brick.y && ((pos.x > pos_brick.x && pos.x< pos_brick.x + pos_brick.w)
                ||((pos.x + pos.w > pos_brick.x && pos.x + pos.w < pos_brick.x + pos_brick.w))
                ||(pos_brick.x > pos.x && pos_brick.x< pos.x + pos.w)
                ||(pos_brick.x + pos_brick.w > pos.x && pos_brick.x + pos_brick.w < pos.x + pos.w)))
            return true;
    }
    return false;
}

void Mario::set_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_KEYDOWN:
    {
        if (event.key.keysym.sym == SDLK_o)
            change_sprite(BIG);
        if (event.key.keysym.sym == SDLK_p)
            change_sprite(LITTLE);
        if (event.key.keysym.sym == SDLK_i)
            change_sprite(FIRE);
        if (event.key.keysym.sym == SDLK_c)
        {
            if (type != FIRE)
                return;
            if (timer.get_time() <= 500)
                return;
            SDL_Rect tmp;
            timer.start();
            SDL_Rect new_pos;
            new_pos.x = pos.x; new_pos.y = pos.y;
            if (direction == RIGHT)
            {
                tmp.x = 5*pos.w; tmp.y = pos.h ; tmp.w = pos.w; tmp.h = pos.h;
                SDL_BlitSurface(sprite,&tmp,screen,&pos);
                SDL_Flip(screen);
                Fireball new_ball(new_pos,0);
                fireball_list.push_back(new_ball);
            }
            else if (direction == LEFT)
             {
                tmp.x = 4*pos.w; tmp.y = pos.h ; tmp.w = pos.w; tmp.h = pos.h;
                SDL_BlitSurface(sprite,&tmp,screen,&pos);
                SDL_Flip(screen);
                Fireball new_ball(new_pos,1);
                fireball_list.push_back(new_ball);
            }
            keyhandle[C] = true;
        }
        if (event.key.keysym.sym ==  SDLK_ESCAPE)
            exit(EXIT_SUCCESS);
        if (event.key.keysym.sym == SDLK_UP)
            keyhandle[UP] = true;
        if (event.key.keysym.sym == SDLK_DOWN)
            keyhandle[DOWN] = true;
        if (event.key.keysym.sym == SDLK_LEFT)
            keyhandle[LEFT] = true;
        if (event.key.keysym.sym == SDLK_RIGHT)
            keyhandle[RIGHT] = true;
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            keyhandle[SPACE] = true;
            pos.y--;
        }
        break;
    }
    case SDL_KEYUP:
    {
        if (event.key.keysym.sym == SDLK_UP)
            keyhandle[UP] = false;
        if (event.key.keysym.sym == SDLK_DOWN)
            keyhandle[DOWN] = false;
        if (event.key.keysym.sym == SDLK_LEFT)
            keyhandle[LEFT] = false;
        if (event.key.keysym.sym == SDLK_RIGHT)
            keyhandle[RIGHT] = false;
        if (event.key.keysym.sym == SDLK_SPACE)
            keyhandle[SPACE] = false;
        if (event.key.keysym.sym == SDLK_c)
            keyhandle[C] = false;
        anim_state = 0;
        break;
    }
    }
}

void Mario::move()
{
    if (!keyhandle[UP] && !keyhandle[DOWN] && !keyhandle[LEFT] && !keyhandle[RIGHT] && x_speed == 0)
        anim_state = 0;
    if (keyhandle[RIGHT])
    {
        if (!keyhandle[C])
            if (x_speed <= SPEED_MAX && anim_state != DUCK && anim_state != LOOKUP)
                x_speed += 1;
        else if (keyhandle[C])
            x_speed = SPEED_MAX;
    }
    if (keyhandle[LEFT])
    {
        if (!keyhandle[C])
            if (x_speed >= -SPEED_MAX && anim_state != DUCK && anim_state != LOOKUP)
                x_speed -= 1;
        else if (keyhandle[C])
            x_speed = SPEED_MAX;
    }
    if (!keyhandle[RIGHT] && !keyhandle[LEFT])
    {
        if (x_speed < 0)
            x_speed+=1;
        else if (x_speed > 0)
            x_speed-=1;
    }
    if (keyhandle[SPACE] && !is_jumping)
    {
        y_speed = -14;
        is_jumping = true;
    }
    if (keyhandle[DOWN] && check_mid_air())
        anim_state = DUCK;
    if (keyhandle[UP] && check_mid_air())
        anim_state = LOOKUP;
}

void Mario::check_collision()
{
    SDL_Rect fire,enemy;
    for (int i=0;i<fireball_list.size();i++)
    {
        fire = fireball_list[i].get_pos();
        for (int j=0;j<enemy_list.size();j++)
        {
            enemy = enemy_list[j]->get_pos();
            if (fire.x + fire.w >= enemy.x && fire.x + fire.w <= enemy.x + enemy.w &&((fire.y >= enemy.y && fire.y <= enemy.y + enemy.h)||
                                                                                      (fire.y + fire.h >= enemy.y&& fire.y + fire.h <= enemy.y + enemy.h)))
            {
                enemy_list[i]->burn();
               // enemy_list.erase(enemy_list.begin()+j);
                fireball_list.erase(fireball_list.begin()+i);
            }
        }
    }
    if (!check_down())
    {
        if (y_speed <= 7)
        {
            y_speed += GRAVITY;
        }
    }
    else
        is_jumping = false;
    pos.y += y_speed;
    if (check_up())
        y_speed = 0;
    if (!check_left() && !check_right() && !check_up())
    {
        if (x_speed > 0)
        {
            if (keyhandle[LEFT])
            {
                if (anim_state != 4)
                    anim_state = 4;
            }
            if (direction != RIGHT)
                direction = RIGHT;
            if (anim_state == 0)
                anim_state = 1;
            else if (anim_state == 1)
                anim_state = 2;
            else if (anim_state == 2)
                anim_state = 3;
            else if (anim_state == 3 || (anim_state == 4 && !keyhandle[LEFT]))
                anim_state = 0;
        }
        else if (x_speed < 0)
        {
             if (keyhandle[RIGHT])
            {
                if (anim_state != 4)
                    anim_state = 4;
            }
            if (direction != LEFT)
                direction = LEFT;
            if (anim_state == 0)
                anim_state = 1;
            else if (anim_state == 1)
                anim_state = 2;
            else if (anim_state == 2)
                anim_state = 3;
            else if (anim_state == 3 || (anim_state == 4 && !keyhandle[RIGHT]))
                anim_state = 0;
        }
        if (x_speed == 0)
        {
            if (!anim_state == DUCK)
                anim_state = 0;
        }
        world_handling();
    }
}

void Mario::change_sprite(int new_type)
{
    if (new_type == LITTLE && type != LITTLE)
    {
        type = new_type;
        sprite = IMG_Load("./data/images/mario_little.png");
        pos.w = 16;
        pos.h = 20;
        blit_pos.w = pos.w;
        blit_pos.h = pos.h;
    }
    else if ((new_type == BIG && type == LITTLE) || new_type == FIRE && (type == BIG || type == LITTLE))
    {
        SDL_Surface *temp;
        SDL_Rect previous;
        previous.y = pos.y;
        for (int i=0; i<4; i++)
        {
            pos.y = previous.y;
            SDL_Rect tmp_pos;
            if (direction == LEFT)
                tmp_pos.x = 2*pos.w;
            else if (direction == RIGHT)
                tmp_pos.x = 0;
            if (type == LITTLE)
            {
                temp = IMG_Load("./data/images/mario_little.png");
                tmp_pos.h = 20;
            }
            if (type == BIG)
            {
                temp = IMG_Load("./data/images/mario_big.png");
                tmp_pos.h = 32;
            }
            tmp_pos.w = pos.w;
            tmp_pos.y = 0;
            camera.show(screen,tilemap,powerup_list,fireball_list,enemy_list);
            SDL_BlitSurface(temp,&tmp_pos,screen,&pos);
            SDL_Flip(screen);
            SDL_Delay(50);
            if (new_type == BIG)
            {
                pos.y -= 12;
                temp = IMG_Load("./data/images/mario_big.png");
            }
        else if (new_type == FIRE)
            {
                if (type == LITTLE)
                    pos.y -= 12;
                temp = IMG_Load("./data/images/mario_fire.png");
            }
            tmp_pos.h = 32;
            camera.show(screen,tilemap,powerup_list,fireball_list,enemy_list);
            SDL_BlitSurface(temp,&tmp_pos,screen,&pos);
            SDL_Flip(screen);
            SDL_Delay(50);
        }
         type = new_type;
        pos.w = 16;
        pos.h = 32;
        blit_pos.w = pos.w;
        blit_pos.h = pos.h;
        if (new_type == BIG)
            sprite = IMG_Load("./data/images/mario_big.png");
        else if (new_type == FIRE)
            sprite = IMG_Load("./data/images/mario_fire.png");
    }
}

void Mario::apply_gravity()
{
    y_speed += GRAVITY;
}

void Mario::set_animation()
{
    if (anim_state == DUCK)
    {
        blit_pos.y = 2*pos.h;
        if (direction == RIGHT)
            blit_pos.x = pos.w;
        else if (direction == LEFT)
            blit_pos.x = 0;
        return;
    }
    if (anim_state == LOOKUP)
    {
        blit_pos.y = 2*pos.h;
        if (direction == RIGHT)
            blit_pos.x = 3*pos.w;
        else if (direction == LEFT)
            blit_pos.x = 2*pos.w;
        return;
    }
    if (direction == RIGHT)
    {
        if (!check_mid_air())
        {
            blit_pos.y = pos.h;
            if (y_speed > 0)
                blit_pos.x = pos.w;
            else
                blit_pos.x = 0;
        }
        else if (anim_state == 4)
        {
            blit_pos.x = 4*pos.w; blit_pos.y = 2*pos.h;
            blit_pos.w = pos.w; blit_pos.h = pos.h;
        }
        else
        {
            blit_pos.y = 0;
            if (x_speed > 8)
            {
                if (anim_state == 0 || anim_state == 3)
                    blit_pos.x = 6*pos.w;
                else if (anim_state == 1)
                    blit_pos.x = 7*pos.w;
                else if (anim_state == 2)
                {
                    if (type == LITTLE)
                        blit_pos.x = 7*pos.w;
                    else if (type == BIG || type == FIRE)
                    {
                        blit_pos.y = 3*pos.h;
                        blit_pos.x = pos.w;
                    }
                }
            }
            else
            {

                if (anim_state == 0 || anim_state == 3)
                    blit_pos.x = 0;
                else if (anim_state == 1)
                    blit_pos.x = pos.w;
                else if (anim_state == 2)
                {
                    if (type == LITTLE)
                        blit_pos.x = pos.w;
                    else if (type == BIG || type == FIRE)
                    {
                        blit_pos.y = 3*pos.h;
                        blit_pos.x = pos.w;
                    }
                }
            }
        }
    }
    else if (direction == LEFT)
    {
        if (!check_mid_air())
        {
            blit_pos.y = pos.h;
            if (y_speed > 0)
                blit_pos.x = 3*pos.w;
            else
                blit_pos.x = 2*pos.w;
        }
        else if (anim_state == 4)
        {
            blit_pos.x = 5*pos.w; blit_pos.y = 2*pos.h;
            blit_pos.w = pos.w; blit_pos.h = pos.h;
        }
        else
        {
            blit_pos.y = 0;
            if (x_speed < -8)
            {
                if (anim_state == 0 || anim_state == 3)
                    blit_pos.x = 4*pos.w;
                else if (anim_state == 1)
                    blit_pos.x = 5*pos.w;
                else if (anim_state == 2)
                {
                    if (type == LITTLE)
                        blit_pos.x = 4*pos.w;
                    else if (type == BIG || type == FIRE)
                    {
                        blit_pos.y = 3*pos.h;
                        blit_pos.x = 2*pos.w;
                    }
                }
            }
            else
            {
                if (anim_state == 0 || anim_state == 3)
                    blit_pos.x = 2*pos.w;
                else if (anim_state == 1)
                    blit_pos.x = 3*pos.w;
                else if (anim_state == 2)
                {
                    if (type == LITTLE)
                        blit_pos.x = 2*pos.w;
                    else if (type == BIG || type == FIRE)
                    {
                        blit_pos.y = 3*pos.h;
                        blit_pos.x = 3*pos.w;
                    }
                }
            }
        }
    }
}

void Mario::dying()
{
    blit_pos.x = 6*pos.w; blit_pos.y = 2*pos.h - 5;
    blit_pos.w = BLOC/2; blit_pos.h = pos.h + 5;
    float max_height = pos.y - pos.h;
    while (pos.y > max_height)
    {
        pos.y -= 3;
        camera.show(screen,tilemap,powerup_list,fireball_list,enemy_list);
        SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
        SDL_Flip(screen);
    }
    SDL_Delay(650);
    while (pos.y < LARG)
    {
        pos.y += 3;
        camera.show(screen,tilemap,powerup_list,fireball_list,enemy_list);
        SDL_BlitSurface(sprite,&blit_pos,screen,&pos);
        SDL_Flip(screen);
    }
    SDL_Delay(5000);
    exit(EXIT_SUCCESS);
}

void Mario::world_handling()
{
    if ((pos.x + x_speed < LONG/2 && tilemap[0].get_pos().x >=0) || (pos.x >= tilemap[1795].get_pos().x/2))
        {
            pos.x +=x_speed;
            for (int i=0; i<powerup_list.size(); i++)
                powerup_list[i].move(collision_list,0);
            for (int i=0;i<fireball_list.size();i++)
                fireball_list[i].move(collision_list,0,enemy_list);
            for (int i=0;i<enemy_list.size();i++)
                enemy_list[i]->move(collision_list,tilemap,0);
        }
        else
        {
            for (int i=0; i<tilemap.size(); i++)
                tilemap[i].move(x_speed);
            for (int i=0; i<collision_list.size(); i++)
                collision_list[i].move(x_speed);
            for (int i=0; i<powerup_list.size(); i++)
                powerup_list[i].move(collision_list,x_speed);
            for (int i=0;i<fireball_list.size();i++)
                fireball_list[i].move(collision_list,x_speed,enemy_list);
            for (int i=0;i<enemy_list.size();i++)
                enemy_list[i]->move(collision_list,tilemap,x_speed);
        }

}
