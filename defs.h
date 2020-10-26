#ifndef DEFS_H
#define DEFS_H

#define LARG 480
#define LONG 480
#define LONG_MAP 120
#define LARG_MAP 15
#define BLOC 32
#define GRAVITY 1
#define FPS 30

#include <iostream>

using namespace std;

enum {UP_DOWN,LEFT_RIGHT};
enum {GROUND0,GROUND1,GROUND2,GROUND3,GROUND4,GROUND5,GROUND6,GROUND7,
      SKY,GRASS0,GRASS1,PIPE0,PIPE1,PIPE2,PIPE3,BLOC0,BLOC1,BLOC2,FINISH0,FINISH1,FINISH2,FINISH3,
      MUSHROOM,FLOWER,EMPTY,COIN,CLOUD,INVISIBLOC,ONEUP};

#endif // DEFS_H
