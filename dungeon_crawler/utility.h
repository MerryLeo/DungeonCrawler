#ifndef UTILITY_H
#define UTILITY_H

// Useful define
#define ERROR -1
#define SUCCESS 1
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

typedef struct coord {
    int x;
    int y;
} COORD;

void print_colored(char msg[], char color[]);
void initialise_random();
int generate_number(int min, int max);
int remape_value(int value, int min1, int max1, int min2, int max2);
int clamp01(int value);

#endif