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
    int Color;
    enum Orientation Orientation;
    int Row;
    int Col;
    int *Cells;
    long UnmovedTime;
} Block;

Block Zblock()
{
    Block b = {3, 3, RED, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[1] = 1;
    b.Cells[4] = 1;
    b.Cells[5] = 1;
    return b;
}

Block Sblock()
{
    Block b = {3, 3, GREEN, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[1] = 1;
    b.Cells[2] = 1;
    b.Cells[4] = 1;
    b.Cells[3] = 1;
    return b;
}

Block Tblock()
{
    Block b = {3, 3, PURPLE, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[1] = 1;
    b.Cells[2] = 1;
    b.Cells[4] = 1;
    return b;
}

Block Lblock()
{
    Block b = {4, 4, ORANGE, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[0] = 1;
    b.Cells[4] = 1;
    b.Cells[8] = 1;
    b.Cells[9] = 1;
    return b;
}

Block Jblock()
{
    Block b = {4, 4, BLUE, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[3] = 1;
    b.Cells[7] = 1;
    b.Cells[11] = 1;
    b.Cells[10] = 1;
    return b;
}

Block SQblock()
{
    Block b = {4, 4, YELLOW, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[5] = 1;
    b.Cells[6] = 1;
    b.Cells[9] = 1;
    b.Cells[10] = 1;
    return b;
}

Block Iblock()
{
    Block b = {4, 4, LIGHT_BLUE, UP, 0, 0};
    b.Cells = (int*)calloc(b.Width*b.Height, sizeof(int));
    b.Cells[1] = 1;
    b.Cells[5] = 1;
    b.Cells[9] = 1;
    b.Cells[13] = 1;
    return b;
}

/*
void drawBlock(Block* block)
{
    for(int i = 0; i<(block->Width * block->Height); i++)
    {
        printf("%d", block->Cells[i]);
        if ((i % block->Width) == block->Width-1)
        {
            printf("\n");
        }
    }
    printf("\n");
}*/

void randBlock(Block* block)
{
    int idx = rand() % 7;
    switch (idx)
    {
    case 0:
        (*block) = Zblock();
        break;
    case 1:
        (*block) = Sblock();
        break;
    case 2:
        (*block) = Tblock();
        break;
    case 3:
        (*block) = Lblock();
        break;
    case 4:
        (*block) = Jblock();
        break;
    case 5:
        (*block) = SQblock();
        break;
    case 6:
        (*block) = Iblock();
        break;
    default:
        (*block) = Zblock();
        break;
    }
    block->Row = 0;
    block->Col = 0;
}

void transpose(Block* block)
{
    for(int row = 0; row < block->Height; row++)
    {
        for(int col = 0; col< row; col++)
        {
            int rRow = row * block->Width;
            int p1 = rRow + col;

            int nRow = col * block->Width;
            int p2 = nRow + row;
            int tmp = block->Cells[p1];
            block->Cells[p1] = block->Cells[p2];
            block->Cells[p2] = tmp;
        }
    }
}

void reverseRow(Block* block)
{
    for (int row = 0; row < block->Height; row++)
    {
        for(int col = 0; col< (block->Width/2); col++)
        {
            int rRow = row * block->Width;
            int p1 = rRow + col;
            int p2 = rRow + block->Width - 1 - col;
            int tmp = block->Cells[p1];
            block->Cells[p1] = block->Cells[p2];
            block->Cells[p2] = tmp;           
        }
    }
}

void RotateBlock(Block* block)
{
    transpose(block);
    reverseRow(block);
    int ori = block->Orientation + 1;
    if (ori > 3)
    {
        ori = 0;
    }
    block->Orientation = ori;
}


void MoveBlock(Block* block, int row, int col)
{
    block->Row += row;
    block->Col += col;
}

#endif
