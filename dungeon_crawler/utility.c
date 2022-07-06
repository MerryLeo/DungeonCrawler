#include "utility.h"
#include <stdlib.h>
#include <time.h>

time_t now;

void initialise_random()
{
    now = time(0);
    srand((unsigned int)now);
}

// Generate number between min and max inclusive
int generate_number(int min, int max)
{
    int random_num = rand() % max + 1;
    random_num = remape_value(random_num, 0, max, min, max);
    return random_num;
}

// Remap a value between min2 and max2
int remape_value(int value, int min1, int max1, int min2, int max2)
{
    int step1 = max1 - min1;
    int step2 = max2 - min2;
    float new_value = ((value - min1) / (float)step1) * step2 + min2;
    return (int)new_value;
}