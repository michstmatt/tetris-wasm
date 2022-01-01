#include "./models/board.h"
#include "./models/blocks.h"
#include <stdlib.h>

Board board;
Block block;

long lastUpdate;
int blockUpdateDelta;
int score[3];

int initGame(long time)
{
    board = (Board)DEFAULT_BOARD;
    srand(time);
    randBlock(&block);
    lastUpdate = time;
    blockUpdateDelta = 500;
    return 0;
}

int* getScore()
{
    return score;
}

int *updateGame(long time, int moveRight, int moveDown, int rotate)
{
    Board *boardPtr = &board;
    Block *blockPtr = &block;
    clearBlock(boardPtr, blockPtr);

    if(checkGameOver(boardPtr))
    {
        score[2] = 1;
        return (int *)(boardPtr->Cells);
    }

    int didMove = 0;
    int delta = time - lastUpdate;

    if ((moveRight || moveDown) && blockCanMove(boardPtr, blockPtr, moveDown, moveRight))
    {
        didMove = 1;
        MoveBlock(blockPtr, moveDown, moveRight);
    }

    if (rotate)
    {
        RotateBlock(blockPtr);
    }

    if (delta > blockUpdateDelta)
    {
        lastUpdate = time;
        if (blockCanMove(boardPtr, blockPtr, 1, 0))
        {
            didMove = 1;
            MoveBlock(blockPtr, 1, 0);
        }

        if (!didMove)
        {
            blockPtr->UnmovedTime += delta;
            if (blockPtr->UnmovedTime > 1000)
            {
                // new block
                updateBlock(boardPtr, blockPtr);
                score[0] += checkRows(boardPtr);
                randBlock(blockPtr);
            }
        }
    }

    updateBlock(boardPtr, blockPtr);

    return (int *)(boardPtr->Cells);
    //return (int *)(board.Cells);
}