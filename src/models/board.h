#ifndef BOARD_H
#define BOARD_H
#include "blocks.h"
#include "color.h"
#define VIEWABLE_ROWS 20
#define COLUMNS 10
#define ROWS 40

typedef struct {
    int Columns;
    int Rows;
    int ViewableRows;

    int Cells[ROWS][COLUMNS];
} Board;

#define DEFAULT_BOARD {COLUMNS, ROWS, VIEWABLE_ROWS}

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

void clearBlock(Board* board, Block* block)
{
    for(int row = 0; row < block->Height; row ++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int x = block->Col + col;
            int y = block->Row + row;
            board->Cells[y][x] = 0;
        }
    }

}

int blockCanMove(Board* board, Block* block, int mX, int mY)
{
    int allowed = 1;
    for(int row =0; row < block->Height; row++)
        for(int col =0; col < block->Width; col++)
        {
            int pos = row*block->Width + col;
            if(block->Cells[pos] == 0)
                continue;
            int y = block->Row + row + mY + board->ViewableRows;
            int x = block->Col + col + mX;
            allowed &= (x>= 0 && x < board->Columns && y >=0 && y < board->Rows && board->Cells[row][col] == 0);
        }
    return allowed;
}

void updateBlockInBounds(Board* board, Block* block)
{
    for(int row = 0; row < block->Height; row ++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int x = block->Col + col;
            int y = block->Row + row;

            // too far left, move right
            if (x < 0 || board->Cells[y][x] != 0)
            {
                block->Col += 1;
                break;
            }

            if (x >= board->Columns || board->Cells[y][x] != 0)
            {

                block->Col -= 1;
                break;
            }

        }
    }
}

void updateBlock(Board* board, Block* block)
{
    updateBlockInBounds(board, block);
    for(int row = 0; row < block->Height; row ++)
    {
        for (int col = 0; col < block->Width; col++)
        {
            int pos = row*block->Width + col;
            if (block->Cells[pos] == 1)
            {
                int x = block->Col + col;
                int y = block->Row + row;
                board->Cells[y][x] = block->Color;
            }
        }
    }
}

#endif