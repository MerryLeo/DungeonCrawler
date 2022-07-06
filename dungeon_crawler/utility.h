#ifndef UTILITY_H
#define UTILITY_H

typedef struct coord {
    int x;
    int y;
} COORD;

void initialise_random();
int generate_number(int min, int max);
int remape_value(int value, int min1, int max1, int min2, int max2);

#endif