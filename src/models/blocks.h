#ifndef BLOCKS_H
#define BLOCKS_H
#include "color.h"

enum Orientation
{
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3
};

typedef struct 
{
    int Width;
    int Height;
    Color Color;
    enum Orientation Orientation;
} Block;

#define Z_BLOCK {3, 3, RED, UP}
#define S_BLOCK {3, 3, GREEN, UP}
#define T_BLOCK {3, 3, PURPLE, UP}
#define L_BLOCK {4, 4, BLUE, UP}
#define J_BLOCK {4, 4, ORANGE, UP}
#define SQ_BLOCK {4, 4, YELLOW, UP}
#define ST_BLOCK {4, 4, LIGHT_BLUE, UP}

#endif
