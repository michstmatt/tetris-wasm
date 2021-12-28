#ifndef COLOR_H
#define COLOR_H

typedef struct
{
    short R;
    short G;
    short B;
} Color;

#define RED {255, 0, 0}
#define BLUE {0, 0, 255}
#define GREEN {0, 255, 0}
#define YELLOW {255, 255, 0}
#define ORANGE {255, 165, 0}
#define PURPLE {255, 0, 255}
#define LIGHT_BLUE {112, 163, 204}

#endif