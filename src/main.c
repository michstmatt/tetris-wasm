#include "./models/board.h"
#include "./models/blocks.h"
#include <stdlib.h>

Board board;
Block block;

int initGame()
{
    board = (Board)DEFAULT_BOARD;
    block = Zblock();
    block.Col = 1;
    block.Row = 0;
    return 0;
}

int* getGame()
{
    return (int*)board.Cells;
}

int updateGame()
{
    clearBlock(&board, &block);
    if(blockCanMove(&board, &block, 1, 0))
        MoveBlock(&block, 1, 0);
    updateBlock(&board, &block);
    return block.Row;
}

void moveCurrentBlock(int right, int down, int rotate)
{
    clearBlock(&board, &block);
    if (down < 0)
    {
        down = 0;
    }
    MoveBlock(&block, down, right);
    if (rotate)
    {
        RotateBlock(&block);
    }
}