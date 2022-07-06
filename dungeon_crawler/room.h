#include "utility.h"
#include "item.h"

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
    int locked;
} DOOR;

typedef struct torch {
    int light;
} TORCH;

typedef enum tile_type {
    wall = 0,
    empty = 1, 
    hole = 2,
    door = 3
} TILE_TYPE;

typedef struct room_tile {
    TILE_TYPE type;
    int light_level;
    ITEM *item;
    DOOR *door;
    unsigned char tile_char;
} ROOM_TILE;

typedef struct room {
    ROOM_TILE *tiles;
    int width;
    int height;
} ROOM;

void create_empty_room(ROOM *room, const int width, const int height);
void add_walls(ROOM *room);
void create_tile(ROOM_TILE *tile, const unsigned char symbol, TILE_TYPE type);
void print_room(ROOM room);
void delete_room(ROOM *room);
void delete_tile(ROOM_TILE *tile);

#endif