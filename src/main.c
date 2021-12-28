#include <stdio.h>
#include "./models/board.h"
#include "./models/cell.h"

int main(int arc, char** argv)
{
    Board b = DEFAULT_BOARD;
    Cell c;
    Color col;
    printf("%d %d %d", b.Columns, b.Rows, b.ViewableRows);
    return 0;
}
