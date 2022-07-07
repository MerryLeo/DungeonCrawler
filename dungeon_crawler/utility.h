#ifndef UTILITY_H
#define UTILITY_H

#define TRUE 1
#define FALSE 0

typedef enum {
    up = 0,
    right = 1,
    left = 2,
    down = 3,
    up_left = 4,
    up_right = 5,
    down_left = 6,
    down_right = 7
} DIRECTION;

typedef struct coord {
    int x;
    int y;
} COORD;

void initialise_random();
int generate_number(int min, int max);
int remape_value(int value, int min1, int max1, int min2, int max2);
int clamp01(int value);

#endif