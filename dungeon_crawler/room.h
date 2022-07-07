#include "utility.h"
#include "item.h"
#include "torch.h"

#ifndef ROOM_H
#define ROOM_H

// ROOM Size
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

typedef struct {
    int locked;
} DOOR;

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

typedef struct {
    int light_level;
    TILE_TYPE type;
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

void create_empty_room(ROOM *room, const int width, const int height);
void remove_chunk_from_room(ROOM *room, int startRow, int endRow, int startCol, int endCol);
int is_tile_wall(ROOM room, ROOM_TILE *tile, const int row, const int col);
unsigned int get_wall_char(WALL_TYPE type);
void add_walls(ROOM *room);
void add_doors(ROOM *room);
void create_tile(ROOM_TILE *tile, const unsigned char symbol, TILE_TYPE type);
void print_room(ROOM room);
void delete_room(ROOM *room);

#endif