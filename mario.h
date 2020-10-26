#ifndef MARIO_H
#define MARIO_H

#include "withmass.h"

class Mario:public WithMass
{
    private:
        bool keyhandle[10];
        int previous, type;
        Camera camera;
        vector<Powerup> powerup_list;
        vector<Fireball> fireball_list;
        vector<Enemy*> enemy_list;
    public:
        Mario(SDL_Surface *screen);
        virtual void show(SDL_Surface *screen);
        void set_animation();
        void update();
        void set_input();
        virtual void move();
        virtual void check_collision();
        virtual bool check_right();
        virtual bool check_left();
        virtual bool check_up();
        virtual bool check_down();
        virtual bool check_mid_air();
        virtual void apply_gravity();
        void change_sprite(int new_type);
        void dying();
        void world_handling();
};


#endif // MARIO_H
