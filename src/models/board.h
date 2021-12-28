#ifndef BOARD_H
#define BOARD_H
#include "color.h"
#define VIEWABLE_ROWS 20
#define COLUMNS 10
#define ROWS 40

typedef struct {
    int Columns;
    int Rows;
    int ViewableRows;

    Color Cells[ROWS][COLUMNS];
} Board;

#define DEFAULT_BOARD {COLUMNS, ROWS, VIEWABLE_ROWS}
#endif