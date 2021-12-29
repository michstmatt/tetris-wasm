#include <stdio.h>
#include "./models/board.h"
#include "./models/blocks.h"

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
}

int main(int arc, char** argv)
{
    Board b = DEFAULT_BOARD;
    Color col;
    Block block = IBlock();
    RotateBlock(&block);
    return 0;
}
