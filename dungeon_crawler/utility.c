#include "utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

time_t now;

// Swap two values
void swap_values(int *value1, int *value2)
{
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

// Create a new RECTANGLE from two corners
RECTANGLE create_rectangle(int first_col, int first_row, int last_col, int last_row)
{
    RECTANGLE rectangle;
    COORD first_corner, last_corner;
    first_corner.row = first_row;
    first_corner.col = first_col;
    last_corner.row = last_row;
    last_corner.col = last_col;
    rectangle.first_corner = first_corner;
    rectangle.last_corner = last_corner;
    return rectangle;
}

// Create a new COORD structure
COORD create_coord(const int col, const int row)
{
    COORD coord;
    coord.row = row;
    coord.col = col;
    return coord;
}

// Initialise random for later
void initialise_random()
{
    now = time(0);
    srand((unsigned int)now);
}

// Generate number between min and max inclusive
int generate_number(const int min, const int max)
{
    int random_num = rand() % max + 1;
    random_num = remape_value(random_num, 0, max, min, max);
    return random_num;
}

// Remap a value that is between min1 and max1 to min2 and max2
int remape_value(const int value, const int min1, const int max1, const int min2, const int max2)
{
    int step1 = max1 - min1;
    int step2 = max2 - min2;
    float new_value = ((value - min1) / (float)step1) * step2 + min2;
    return (int)new_value;
}

// Print text with a color
void print_colored(const char *msg, const char *color)
{
    printf(color);
    printf(msg);
    printf(COLOR_DEFAULT);
}

// Clamp a value between 0 and 1
int clamp01(int value)
{
    if (value < 0)
        value = 0;
    else if (value > 1)
        value = 1;
    return value;
}