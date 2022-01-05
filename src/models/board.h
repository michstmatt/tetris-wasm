#ifndef BOARD_H
#define BOARD_H
#include "blocks.h"
#include "color.h"
#include <string.h>
#define VIEWABLE_ROWS 20
#define COLUMNS 10
#define ROWS 24

typedef struct
{
    int Columns;
    int Rows;
    int ViewableRows;

    int Cells[ROWS][COLUMNS];
} Board;

#define DEFAULT_BOARD                \
    {                                \
        COLUMNS, ROWS, VIEWABLE_ROWS \
    }

/*
void drawBoard(Board* board)
{
    for(int row = 0; row < board->ViewableRows; row++)
    {
        for(int col = 0; col < board ->Columns; col++)
        {
            printf("%c", (board->Cells[row][col] == 0 ? '.' : 'X'));
        }
        printf("\n");
    }
}
*/

void clearBlock(Board *board, Block *block)
{
    for (int row = 0; row < block->Height; row++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int x = block->Col + col;
            int y = block->Row + row;
            int pos = row * block->Width + col;
            if (block->Cells[pos] == 1)
                board->Cells[y][x] = 0;
        }
    }
}

int blockCanMove(Board *board, Block *block, int mY, int mX)
{
    int allowed = 1;
    for (int row = 0; row < block->Height; row++)
        for (int col = 0; col < block->Width; col++)
        {
            int pos = row * block->Width + col;
            if (block->Cells[pos] == 0)
                continue;
            int y = block->Row + row + mY;
            int x = block->Col + col + mX;
            if (!(x >= 0 && x < board->Columns && y >= 0 && y < board->Rows && board->Cells[y][x] == 0))
            {
                allowed = 0;
            }
        }
    return allowed;
}

void updateBlockInBounds(Board *board, Block *block)
{
    for (int row = 0; row < block->Height; row++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int pos = row * block->Width + col;
            if (block->Cells[pos] == 0)
                continue;
            int x = block->Col + col;
            int y = block->Row + row;

            // too far left, move right
            if (x < 0)
            {
                block->Col += 1;
                break;
            }

            if (x >= board->Columns)
            {

                block->Col -= 1;
                break;
            }
        }
    }
}

void TryRotateBlock(Board *board, Block *block)
{
    int numCells = block->Width * block->Height;
    int backup[numCells];
    memcpy(backup, block->Cells, numCells * sizeof(int));

    RotateBlock(block);

    int okToRotate = blockCanMove(board, block, 0, 0);

    // block cannot rotate without collision
    if (!okToRotate)
    {
        memcpy(block->Cells, backup, numCells * sizeof(int));
    }
}

void updateBlock(Board *board, Block *block)
{
    updateBlockInBounds(board, block);
    for (int row = 0; row < block->Height; row++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int pos = row * block->Width + col;
            if (block->Cells[pos] == 1)
            {
                int x = block->Col + col;
                int y = block->Row + row;
                board->Cells[y][x] = block->Color;
            }
        }
    }
}

int checkRows(Board *board)
{
    int cleared = 0;
    for (int row = 0; row < board->Rows; row++)
    {
        int sum = 0;
        for (int col = 0; col < board->Columns; col++)
        {
            sum += (board->Cells[row][col] > 0);
        }
        if (sum == board->Columns)
        {
            cleared++;
            // clear row
            // move row down
            for (int mRow = row; row > 0; row--)
            {
                for (int col = 0; col < board->Columns; col++)
                {
                    board->Cells[row][col] = board->Cells[row - 1][col];
                }
            }
        }
    }
    return cleared;
}
int checkGameOver(Board *board)
{
    int hiddenRows = board->Rows - board->ViewableRows;
    for (int row = 0; row < hiddenRows; row++)
    {
        for (int col = 0; col < board->Columns; col++)
        {
            if (board->Cells[row][col] > 0)
            {
                return 1;
            }
        }
    }
    return 0;
}
#endif