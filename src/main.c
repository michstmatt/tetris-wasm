#include "./models/board.h"
#include "./models/blocks.h"
#include <stdlib.h>

Board board;
Block block;

int initGame()
{
    board = (Board)DEFAULT_BOARD;
    block = IBlock();
    block.Col = 0;
    block.Row = 0;
    return 0;
}

int *getGame()
{
    return (int *)board.Cells;
}

int updateGame()
{
    clearBlock(&board, &block);
    if (blockCanMove(&board, &block, 1, 0))
    {
        MoveBlock(&block, 1, 0);
    }
    else
    {
        block.UnmovedTime += 1;
    }
    updateBlock(&board, &block);

    if(block.UnmovedTime == 2)
    {
        checkRows(&board);
        block = IBlock();
    }

    return block.Row;
}

void moveCurrentBlock(int right, int down, int rotate)
{
    clearBlock(&board, &block);
    if (down < 0)
    {
        down = 0;
    }
    if (blockCanMove(&board, &block, right, down))
    {
        MoveBlock(&block, down, right);
    }
    if (rotate)
    {
        RotateBlock(&block);
    }
}