#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "utility.h"
#include "exception.h"

// Create an empty rectangular room with dimensions
// width and height with no walls
// Return ERROR if memory could not be allocated, otherwise
// returns SUCCESS
int create_empty_room(ROOM *room, const int width, const int height)
{
    room->tiles = (ROOM_TILE*)calloc(width * height, sizeof(ROOM_TILE));
    if (room->tiles == NULL)
        return ERROR_NULL_PTR;
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
    return SUCCESS;
}

// Remove a rectangle from the room
// coordinates of the rectangle represent positions (indices)
// to remove from the room
// to remove the chunk
void remove_tiles(ROOM *room, RECTANGLE tiles_to_remove)
{
    // Get coordinates of both corners of the rectangle
    // to remove part of the room
    int room_width = room->width;
    int start_row = tiles_to_remove.first_corner.row;
    int start_col = tiles_to_remove.first_corner.col;
    int end_row = tiles_to_remove.last_corner.row;
    int end_col = tiles_to_remove.last_corner.col;
    int row, col;
    ROOM_TILE *tile;

    // Mark tiles in the chunk as out of bound
    for (row = start_row; row <= end_row; row++)
    {
        for (col = start_col; col <= end_col; col++)
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

// Add door from source to dest
int add_doors(ROOM *source, ROOM *dest)
{
    ROOM_TILE *tile;
    int attempt;
    attempt = get_random_wall(source, tile);
    if (attempt == ERROR)
        return ERROR;
    create_door(tile->door, tile, dest);
    attempt = get_random_wall(dest, tile);
    if (attempt == ERROR)
        return ERROR;
    create_door(tile->door, tile, source);
}

void create_door(DOOR *room_door, ROOM_TILE *tile, const ROOM *dest)
{
    tile->tile_char = DOOR_SYMBOL;
    tile->wall_type = not_a_wall;
    tile->type = door;
    room_door->dest = (ROOM*)dest;
    room_door->locked = 0;
    room_door->opened = 0;
}

// Create a single tile
void create_tile(ROOM_TILE *tile, const unsigned char symbol, TILE_TYPE type) 
{
    tile->door = NULL;
    tile->description = NULL;
    tile->item = NULL;
    tile->torch = NULL;
    tile->wall_type = not_a_wall;
    tile->light_level = 0;
    tile->tile_char = symbol;
    tile->type = type;
}

// Get a random non-corner wall from the room
int get_random_wall(const ROOM *room, ROOM_TILE *tile)
{
    int room_width = room->width;
    int room_height = room->height;
    int row, col, choice; 
    ROOM_TILE *wall_tile;

    // Try to find a random wall
    while (1)
    {
        choice = clamp01(generate_number(-5, 5));

        // Choose between a random row or a random column
        if (choice == 1)
        {
            choice = clamp01(generate_number(-5, 5));
            row = generate_number(1, room_height - 1);
            if (choice == 1)
            {
                for (col = 0; col < room_width; col++)
                {
                    tile = &(room->tiles[row * room_width + col]);
                    if (tile->type == wall && tile->wall_type == horizontal_wall || tile->wall_type == vertical_wall)
                    {
                        tile = wall_tile;
                        return SUCCESS;
                    }
                }
            }
            else
            {
                for (col = room_width - 1; col >= 0; col--)
                {
                    tile = &(room->tiles[row * room_width + col]);
                    if (tile->type == wall && tile->wall_type == horizontal_wall || tile->wall_type == vertical_wall)
                    {
                        tile = wall_tile;
                        return SUCCESS;
                    }
                }
            }
        }
        else
        {
            choice = clamp01(generate_number(-5, 5));
            col = generate_number(1, room_width - 1);
            if (choice == 1)
            {
                for (row = 0; row < room_height; row++)
                {
                    tile = &(room->tiles[row * room_width + col]);
                    if (tile->type == wall && tile->wall_type == horizontal_wall || tile->wall_type == vertical_wall)
                    {
                        tile = wall_tile;
                        return SUCCESS;
                    }
                }
            }
            else 
            {
                for (row = room_height - 1; row >= 0; row--)
                {
                    tile = &(room->tiles[row * room_width + col]);
                    if (tile->type == wall && tile->wall_type == horizontal_wall || tile->wall_type == vertical_wall)
                    {
                        tile = wall_tile;
                        return SUCCESS;
                    }
                }
            }
        }
        return ERROR;
    }
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