#ifndef UTILITY_H
#define UTILITY_H

#define PATH "../Saves/debug.txt"

// Useful define
#define TRUE 1
#define FALSE 0

// Colors
#define COLOR_DEFAULT "\033[0m" 
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"

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

typedef struct {
    int row;
    int col;
} COORD;

typedef struct {
    COORD first_corner;
    COORD last_corner;
} RECTANGLE;

RECTANGLE create_rectangle(int first_col, int first_row, int last_col, int last_row);
COORD create_coord(const int col, const int row);
void swap_values(int *value1, int *value2);
void print_colored(const char *msg, const char *color);
void initialise_random();
int generate_number(const int min, const int max);
int remape_value(const int value, const int min1, const int max1, const int min2, const int max2);
int clamp01(int value);

#endif