#include <stdio.h>
#include "./models/board.h"
#include "./models/blocks.h"

int main(int arc, char** argv)
{
    Board b = DEFAULT_BOARD;
    Color col;
    Block block = Z_BLOCK;
    printf("%d %d %d", b.Columns, b.Rows, b.ViewableRows);
    return 0;
}
