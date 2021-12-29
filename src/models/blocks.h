#ifndef BLOCKS_H
#define BLOCKS_H
#include <stdlib.h>
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
    int *Cells;
} Block;

Block Zblock()
{
    Block b = {3, 3, RED, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[1] = 1;
    b.Cells[4] = 1;
    b.Cells[7] = 1;
    b.Cells[8] = 1;
    return b;
}

Block Sblock()
{
    Block b = {3, 3, GREEN, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[1] = 1;
    b.Cells[2] = 1;
    b.Cells[4] = 1;
    b.Cells[6] = 1;
    b.Cells[7] = 1;
    return b;
}

Block Tblock()
{
    Block b = {3, 3, PURPLE, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[1] = 1;
    b.Cells[2] = 1;
    b.Cells[4] = 1;
    b.Cells[7] = 1;
    return b;
}

Block LBlock()
{
    Block b = {4, 4, BLUE, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[4] = 1;
    b.Cells[8] = 1;
    b.Cells[12] = 1;
    b.Cells[13] = 1;
    b.Cells[14] = 1;
    return b;
}

Block JBlock()
{
    Block b = {4, 4, ORANGE, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[3] = 1;
    b.Cells[7] = 1;
    b.Cells[11] = 1;
    b.Cells[15] = 1;
    b.Cells[14] = 1;
    b.Cells[13] = 1;
    return b;
}

Block SQBlock()
{
    Block b = {4, 4, ORANGE, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[5] = 1;
    b.Cells[6] = 1;
    b.Cells[9] = 1;
    b.Cells[10] = 1;
    return b;
}

Block IBlock()
{
    Block b = {4, 4, ORANGE, UP};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[1] = 1;
    b.Cells[5] = 1;
    b.Cells[9] = 1;
    b.Cells[13] = 1;
    return b;
}

void RotateBlock(Block* block)
{

}

#endif
