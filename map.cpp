#include "map.h"

Map::Map()
{
}

void Map::load_map()
{
    ifstream File("./data/map/level1.txt");
    char c;
    SDL_Rect position;
    for (int i=0; i<LARG_MAP; i++)
        for (int j=0;j<LONG_MAP;j++)
        {
            File.get(c);
            if (c == '\n' || c == ' ' || c == ':')
            {
                File.seekg(0,ios::cur);
                j--;
            }
            else
            {
            position.x = j*BLOC;
            position.y = i*BLOC;
            Tile tmp;
            if (c == '0')
                tmp.set_tile(position,SKY,false);
            else if (c == '1')
                tmp.set_tile(position,GROUND0,true);
            else if (c == '2')
                tmp.set_tile(position,GROUND1,true);
            else if (c == '3')
                tmp.set_tile(position,GROUND2,true);
            else if (c == '4')
                tmp.set_tile(position,GROUND3,true);
            else if (c == '5')
                tmp.set_tile(position,GROUND4,true);
            else if (c == '6')
                tmp.set_tile(position,GROUND5,true);
            else if (c == '7')
                tmp.set_tile(position,GROUND6,true);
            else if (c == '8')
                tmp.set_tile(position,GROUND7,true);
            else if (c == '9')
                tmp.set_tile(position,GRASS0,false);
            else if (c == 'a')
                tmp.set_tile(position,GRASS1,false);
            else if (c == 'b')
                tmp.set_tile(position,PIPE0,true);
            else if (c == 'c')
                tmp.set_tile(position,PIPE1,true);
            else if (c == 'n')
                tmp.set_tile(position,PIPE2,true);
            else if (c == 'o')
                tmp.set_tile(position,PIPE3,true);
            else if (c == 'p')
                tmp.set_tile(position,FINISH0,false);
            else if (c == 'q')
                tmp.set_tile(position,FINISH1,false);
            else if (c == 'r')
                tmp.set_tile(position,FINISH2,false);
            else if (c == 's')
                tmp.set_tile(position,FINISH3,false);
            else if (c == 'd')
                tmp.set_tile(position,BLOC0,true);
            else if (c == 'e')
                tmp.set_tile(position,BLOC1,true);
            else if (c == 'f')
                tmp.set_tile(position,BLOC2,true);
            /*-----Otrn 2 - 8 f tsis collision------*/
            else if (c == 'g')
                tmp.set_tile(position,GROUND1,false);
            else if (c == 'h')
                tmp.set_tile(position,GROUND2,false);
            else if (c == 'i')
                tmp.set_tile(position,GROUND3,false);
            else if (c == 'j')
                tmp.set_tile(position,GROUND4,false);
            else if (c == 'k')
                tmp.set_tile(position,GROUND5,false);
            else if (c == 'l')
                tmp.set_tile(position,GROUND6,false);
            else if (c == 'm')
                tmp.set_tile(position,GROUND7,false);
            else if (c == 't')
                tmp.set_tile(position,CLOUD,false);
            else if (c == 'u')
                tmp.set_tile(position,INVISIBLOC,true);
            tilemap.push_back(tmp);
                File.seekg(0,ios::cur);
            }
        }
    int bloc_num;
    File >> bloc_num;
    do
    {
        File >> position.x;
        File >> position.y;
        Tile bloc(position,BLOC1,true);
        tilemap.push_back(bloc);
        bloc_num -- ;
        tilemap[tilemap.size()-1].set_index(tilemap.size()-1);
    }
    while (bloc_num > 0);
    File >> bloc_num;
    do
    {
        File >> position.x;
        File >> position.y;
        enemy_list.push_back(new Goomba(position.x,position.y));
        bloc_num -- ;
    }
    while (bloc_num > 0);
    File >> bloc_num;
    do
    {
        File >> position.x;
        File >> position.y;
        Coin coin;
        coin.set(position.x,position.y);
        powerup_list.push_back(coin);
        bloc_num -- ;
    }
    while (bloc_num > 0);
    File >> bloc_num;
    do
    {
        File >> position.x;
        File >> position.y;
        Tile tile(position,INVISIBLOC,true);
        tilemap.push_back(tile);
        tilemap[tilemap.size()-1].set_index(tilemap.size()-1);
        bloc_num -- ;
    }
    while (bloc_num > 0);
    File.close();
    set_collision();
}

vector<Enemy*> Map::get_enemy()
{
    return enemy_list;
}

void Map::set_collision()
{
    for (int i=0; i<tilemap.size(); i++)
        if (tilemap[i].get_solid())
            collision_list.push_back(tilemap[i]);
}

vector<Tile> Map::get_tilemap()
{
    return tilemap;
}

vector<Tile> Map::get_collision()
{
    return collision_list;
}

vector<Powerup> Map::get_powerup()
{
    return powerup_list;
}
