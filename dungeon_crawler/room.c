#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "utility.h"

// Create an empty rectangular room with dimensions
// width and height with no walls
void create_empty_room(ROOM *room, const int width, const int height)
{
    room->tiles = (ROOM_TILE*)malloc(width * height * sizeof(ROOM_TILE));
    ROOM_TILE *tile;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tile = &(room->tiles[row * width + col]);
            create_tile(tile, EMPTY_TILE_CODE, floor);
        }
    }
    room->width = width;
    room->height = height;
}

// Remove a chunk of the room to make a non-rectangular shaped room
// startRow, endRow, startCol, endCol are indices of positions
// to remove the chunk
void remove_chunk_from_room(ROOM *room, int startRow, int endRow, int startCol, int endCol)
{
    int room_width = room->width;
    int row, col;
    ROOM_TILE *tile;
    int temp;

    // Swap startRow and endRow
    if (startRow > endRow)
    {
        temp = startRow;
        startRow = endRow;
        endRow = temp;
    }

    // Swap startCol and endCol
    if (startCol > endCol)
    {
        temp = startCol;
        startCol = endCol;
        endCol = temp;
    }

    // Mark tiles in the chunk as out-of-bound
    for (row = startRow; row <= endRow; row++)
    {
        for (col = startCol; col <= endCol; col++)
        {
            tile = &(room->tiles[row * room_width + col]);
            tile->tile_char = ' ';
            tile->type = out_of_bound;
        }
    }
}

// Check all four directions around a tile
// to determine if its a wall, and updates the tile type with 
// the specific type of wall
// * tile can be walls only if they are inside the room
// and they are not out-of-bound (removed from the room)
int is_tile_wall(ROOM room, ROOM_TILE *tile, const int row, const int col)
{
    int room_width = room.width;
    int room_height = room.height;
    int up_left = FALSE, up_right = FALSE;
    int down_left = FALSE, down_right = FALSE;
    int up = FALSE, down = FALSE, left = FALSE, right = FALSE;
    
    // Slow algorithm to determine if a tile
    // is on the edge of the room
    if (tile->type != out_of_bound)
    {
        // Look left
        if (col - 1 < 0 || room.tiles[row * room_width + col - 1].type == out_of_bound)
            left = TRUE;

        // Look right
        if (col + 1 >= room_width || room.tiles[row * room_width + col + 1].type == out_of_bound)
            right = TRUE;

        // Look up
        if (row - 1 < 0 || room.tiles[(row - 1) * room_width + col].type == out_of_bound)
            up = TRUE;

        // Look down
        if (row + 1 >= room_height || room.tiles[(row + 1) * room_width + col].type == out_of_bound)
            down = TRUE;

        // Look up-left
        if (col - 1 < 0 || row - 1 < 0)
            up_left = TRUE;
        else if (col - 1 >= 0 && row - 1 >= 0 && room.tiles[(row - 1) * room_width + col - 1].type == out_of_bound)
            up_left = TRUE;
        
        // Look up-right
        if (col + 1 >= room_width || row - 1 < 0)
            up_right = TRUE;
        else if (col + 1 < room_width && row - 1 >= 0 && room.tiles[(row - 1) * room_width + col + 1].type == out_of_bound)
            up_right = TRUE;

        // Look down-left
        if (col - 1 < 0 || row + 1 >= room_height)
            down_left = TRUE;
        else if (col - 1 >= 0 && row + 1 < room_height && room.tiles[(row + 1) * room_width + col - 1].type == out_of_bound)
            down_left = TRUE;

        // Look down-right
        if (col + 1 >= room_width || row + 1 >= room_height)
            down_right = TRUE;
        else if (col + 1 < room_width && row + 1 < room_height && room.tiles[(row + 1) * room_width + col + 1].type == out_of_bound)
            down_right = TRUE;

        // Finds which type of wall the tile is and return true
        if (up_left == TRUE && up == TRUE && left == TRUE)
            tile->wall_type = upper_left_corner_wall;
        else if (up_right == TRUE && up == TRUE && right == TRUE)
            tile->wall_type = upper_right_corner_wall;
        else if (down_left == TRUE && down == TRUE && left == TRUE)
            tile->wall_type = down_left_corner_wall;
        else if (down_right == TRUE && down == TRUE && right == TRUE)
            tile->wall_type = down_right_corner_wall;
        else if (up == TRUE || down == TRUE)
            tile->wall_type = horizontal_wall;
        else if (left == TRUE || right == TRUE)
            tile->wall_type = vertical_wall;
        else if (up_left == TRUE && up == FALSE && left == FALSE)
            tile->wall_type = down_right_corner_wall;
        else if (up_right == TRUE && up == FALSE && right == FALSE)
            tile->wall_type = down_left_corner_wall;
        else if (down_left == TRUE && down == FALSE && left == FALSE)
            tile->wall_type = upper_right_corner_wall;
        else if (down_right == TRUE && down == FALSE && right == FALSE)
            tile->wall_type = upper_left_corner_wall;
        else
            return FALSE;
        return TRUE;
    }
    return FALSE;
}

// Get a char corresponding to the specific wall_type
unsigned int get_wall_char(WALL_TYPE type)
{
    switch (type)
    {
        case vertical_wall:
            return VERTICAL_WALL;
        case horizontal_wall:
            return HORIZONTAL_WALL;
        case upper_left_corner_wall:
            return TOP_LEFT_CORNER;
        case upper_right_corner_wall:
            return TOP_RIGHT_CORNER;
        case down_left_corner_wall:
            return BOTTOM_LEFT_CORNER;
        case down_right_corner_wall:
            return BOTTOM_RIGHT_CORNER;
        default:
            return (int)' ';
    }
}

// Add walls to an empty room
void add_walls(ROOM *room)
{
    int room_width = room->width;
    int room_height = room->height;
    int row, col;
    ROOM_TILE *tile;

    for (row = 0; row < room_height; row++)
    {
        for (col = 0; col < room_width; col++)
        {
            tile = &(room->tiles[row * room_width + col]);
            if (is_tile_wall(*room, tile, row, col) == TRUE)
            {
                tile->type = wall;
                tile->tile_char = get_wall_char(tile->wall_type);
            }
        }
    }
}

// Create a single tile
void create_tile(ROOM_TILE *tile, const unsigned char symbol, TILE_TYPE type) 
{
    tile->door = NULL;
    tile->item = NULL;
    tile->torch = NULL;
    tile->wall_type = not_a_wall;
    tile->light_level = 0;
    tile->tile_char = symbol;
    tile->type = type;
}

// Print every tiles in the room
void print_room(ROOM room)
{
    ROOM_TILE tile;
    int room_width = room.width;
    int room_height = room.height;
    char tile_char;

    for (int row = 0; row < room_height; row++)
    {
        for (int col = 0; col < room_width; col++)
        {
            // Get tile
            tile = room.tiles[row * room_width + col];
            tile_char = tile.tile_char;

            if (tile.wall_type == upper_left_corner_wall || tile.wall_type == down_left_corner_wall)
                printf("%c%c", tile_char, HORIZONTAL_WALL);
            else if (tile.wall_type == horizontal_wall)
                printf("%c%c", tile_char, tile_char);
            else
                printf("%c ", tile_char);
        }
        printf("\n");
    }
    printf("\n");
}

// Free memory of a room
void delete_room(ROOM *room)
{
    free(room);
    room = NULL;
}