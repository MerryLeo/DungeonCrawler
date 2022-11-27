// ROOM is used to contain useful information about its content,
// and methods to create rooms

#include "utility.h"
#include "item.h"

#ifndef ROOM_H
#define ROOM_H

// ROOM Size
#define MAX_ROOM_WIDTH 25
#define MIN_ROOM_WIDTH 6
#define MAX_ROOM_HEIGHT 15
#define MIN_ROOM_HEIGHT 6

// ROOM Specifications
#define MIN_DOOR_DIST 4

// Structures characters
#define EMPTY_TILE_CODE 249
#define VERTICAL_WALL 179
#define HORIZONTAL_WALL 196 
#define TOP_LEFT_CORNER 218
#define TOP_RIGHT_CORNER 191
#define BOTTOM_LEFT_CORNER 192
#define BOTTOM_RIGHT_CORNER 217
#define DOOR_SYMBOL ' '

typedef enum {
    not_a_wall = 0,
    vertical_wall = 1,
    horizontal_wall = 2,
    upper_left_corner_wall = 3,
    upper_right_corner_wall = 4,
    down_left_corner_wall = 5,
    down_right_corner_wall = 6,
} WALL_TYPE;

typedef enum {
    floor = 0,
    wall = 1,
    hole = 2,
    door = 3,
    out_of_bound = 4
} TILE_TYPE;

typedef enum {
    none = 0,
    main_room = 1,
    secondary_room = 2,
    storage = 3,
    trap = 4
} ROOM_TYPE;

typedef struct {
    void *dest;
    int opened;
    int locked;
} DOOR;

typedef struct {
    int light_level;
    TILE_TYPE type;
    DESCRIPTION *description;
    WALL_TYPE wall_type;
    TORCH *torch;
    ITEM *item;
    DOOR *door;
    unsigned char tile_char;
} ROOM_TILE;

typedef struct {
    ROOM_TILE *tiles;
    int width;
    int height;
} ROOM;

ROOM create_empty_room(const int width, const int height);
void remove_tiles(ROOM *room, RECTANGLE tiles_to_remove);
int is_tile_wall(ROOM room, ROOM_TILE *tile, const int row, const int col);
// ROOM_TILE* get_adjacent_tiles(ROOM room, const int col, const int row);
unsigned int get_wall_char(WALL_TYPE type);
void add_walls(ROOM *room);
// void add_doors(ROOM *source, ROOM *dest);
// void create_door(ROOM_TILE *tile, ROOM *dest);
ROOM_TILE create_tile(const unsigned char symbol, TILE_TYPE type);
// ROOM_TILE* get_random_wall(const ROOM *room);
void print_room(ROOM room);
void delete_room(ROOM *room);

#endif