#include "utility.h"

#ifndef ROOM_H
#define ROOM_H

// Room Size
#define MAX_ROOM_WIDTH 20
#define MIN_ROOM_WIDTH 10
#define MAX_ROOM_HEIGHT 20
#define MIN_ROOM_HEIGHT 10

// Structures characters
#define EMPTY_TILE_CODE 249
#define VERTICAL_WALL 179
#define HORIZONTAL_WALL 196 
#define TOP_LEFT_CORNER 218
#define TOP_RIGHT_CORNER 191
#define BOTTOM_LEFT_CORNER 192
#define BOTTOM_RIGHT_CORNER 217

// Conditions
#define DOOR_LOCKED 1
#define DOOR_UNLOCKED 0

typedef struct door {
    COORD position;
    int locked;
} DOOR;

typedef struct room_tile {
    DOOR *door;
    unsigned char tile_char;
} ROOM_TILE;

typedef struct room {
    unsigned char *tiles;
    int width;
    int height;
} ROOM;

void generate_empty_room(ROOM *room, const int width, const int height);
void add_walls(ROOM *room);
void print_room(ROOM room);
void delete_room(ROOM *room);

#endif