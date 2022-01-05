#include "./models/board.h"
#include "./models/blocks.h"
#include "./models/queue.h"
#include <stdlib.h>

Board board;
Block block;
BlockQueue blockQueue;
Board queueBoard;

long lastUpdate;
int blockUpdateDelta;
int score[3];

int initGame(long time)
{
    board = (Board)DEFAULT_BOARD;
    queueBoard = (Board){3, 20, 20};
    blockQueue.Length = QUEUE_LEN;
    srand(time);
    SeedQueue(&blockQueue);
    for (int i = 0; i < blockQueue.Length; i++)
    {
        Block *blockPtr = &(blockQueue.Blocks[i]);
        blockQueue.Blocks[i].Row = 5 * i;
        updateBlock(&queueBoard, blockPtr);
    }
    block = QueuePopPush(&blockQueue);
    lastUpdate = time;
    blockUpdateDelta = 500;
    return 0;
}

int *getQueue()
{
    return (int *)queueBoard.Cells;
}

int *getScore()
{
    return score;
}

void blockSet()
{
    // new block
    updateBlock(&board, &block);
    score[0] += checkRows(&board);
    block = QueuePopPush(&blockQueue);
    for (int r = 0; r < queueBoard.Rows; r++)
        for (int c = 0; c < queueBoard.Columns; c++)
        {
            queueBoard.Cells[r][c] = 0;
        }
    int realIndex;
    for (int i = 0; i < blockQueue.Length; i++)
    {
        realIndex = blockQueue.Index + i;
        if (realIndex >= blockQueue.Length)
        {
            realIndex = 0;
        }
        Block *blockPtr = &(blockQueue.Blocks[realIndex]);

        blockQueue.Blocks[realIndex].Row = 5 * i;
        updateBlock(&queueBoard, blockPtr);
    }
}

int *updateGame(long time, int moveRight, int moveDown, int rotate)
{
    Board *boardPtr = &board;
    Block *blockPtr = &block;
    clearBlock(boardPtr, blockPtr);

    if (checkGameOver(boardPtr))
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
        TryRotateBlock(boardPtr, blockPtr);
        updateBlockInBounds(boardPtr, blockPtr);
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
                blockSet();
            }
        }
    }

    updateBlock(boardPtr, blockPtr);

    return (int *)(boardPtr->Cells);
    //return (int *)(board.Cells);
}