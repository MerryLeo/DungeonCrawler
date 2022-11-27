#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "utility.h"
#include "exception.h"

// Return an empty rectangular room
// with no walls of dimensions width and height 
ROOM create_empty_room(const int width, const int height)
{
    // Initialize Room Dimensions
    ROOM room;
    room.width = width;
    room.height = height;

    // Create Empty Tiles
    room.tiles = (ROOM_TILE*)calloc(width * height, sizeof(ROOM_TILE));
    ROOM_TILE empty_tile = create_tile(EMPTY_TILE_CODE, floor);
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            room.tiles[row * width + col] = empty_tile;
    return room;
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
            tile = &room->tiles[row * room_width + col];
            if (is_tile_wall(*room, tile, row, col) == TRUE)
            {
                tile->type = wall;
                tile->tile_char = get_wall_char(tile->wall_type);
            }
        }
    }
}

// Creates two doors in seperate rooms
// and links them together
// void add_doors(ROOM *source, ROOM *dest)
// {
//     ROOM_TILE *first_door, *second_door;
//     do
//     {
//         first_door = get_random_wall(source);
//     } while (first_door == NULL);
//     do
//     {
//         second_door = get_random_wall(dest);
//     } while (second_door == NULL);
//     create_door(first_door, dest);
//     create_door(second_door, source);
// }

// Create a single door
// void create_door(ROOM_TILE *tile, ROOM *dest)
// {
//     tile->tile_char = DOOR_SYMBOL;
//     tile->wall_type = not_a_wall;
//     tile->type = door;
//     tile->door = (DOOR*)malloc(sizeof(DOOR));
//     tile->door->dest = dest;
//     tile->door->locked = FALSE;
//     tile->door->opened = TRUE;
// }

// Create a single tile from a symbol and a type
ROOM_TILE create_tile(const unsigned char symbol, TILE_TYPE type) 
{
    ROOM_TILE tile;
    tile.door = NULL;
    tile.description = NULL;
    tile.item = NULL;
    tile.torch = NULL;
    tile.wall_type = not_a_wall;
    tile.light_level = 0;
    tile.tile_char = symbol;
    tile.type = type;
    return tile;
}

// Get a random non-corner wall from the room
// Return NULL if the function failed
// ROOM_TILE* get_random_wall(const ROOM *room)
// {
//     int room_width = room->width;
//     int room_height = room->height;
//     int row, col, choice; 
//     ROOM_TILE *door_tile;

//     choice = generate_number(1, 4);
//     switch (choice)
//     {
//         case 1:
//             // Get a random row and look for a vertical wall
//             // starting from left to right
//             row = generate_number(1, room_height - 1);
//             for (col = 0; col < room_width; col++)
//             {
//                 door_tile = &room->tiles[row * room_width + col];
//                 if (door_tile->type == wall && door_tile->wall_type == horizontal_wall || door_tile->wall_type == vertical_wall)
//                     return door_tile;
//             }
//         case 2:
//             // Get a random row and look for a vertical wall
//             // starting from right to left
//             row = generate_number(1, room_height - 1);
//             for (col = room_width - 1; col >= 0; col--)
//             {
//                 door_tile = &room->tiles[row * room_width + col];
//                 if (door_tile->type == wall && door_tile->wall_type == horizontal_wall || door_tile->wall_type == vertical_wall)
//                     return door_tile;
//             }
//         case 3:
//             // Get a random column and look for a horizontal wall
//             // starting from up to down
//             col = generate_number(1, room_width - 1);
//             for (row = 0; row < room_height; row++)
//             {
//                 door_tile = &room->tiles[row * room_width + col];
//                 if (door_tile->type == wall && door_tile->wall_type == horizontal_wall || door_tile->wall_type == vertical_wall)
//                     return door_tile;
//             }
            
//         case 4:
//             // Get a random column and look for a horizontal wall
//             // starting from down to up
//             col = generate_number(1, room_width - 1);
//             for (row = room_height - 1; row >= 0; row--)
//             {
//                 door_tile = &room->tiles[row * room_width + col];
//                 if (door_tile->type == wall && door_tile->wall_type == horizontal_wall || door_tile->wall_type == vertical_wall)
//                     return door_tile;
//             }
//     }
//     return NULL;
// }

// Returns 8 tiles that are adjacent to the position (col, row)
// Tiles in the array are 
// ROOM_TILE* get_adjacent_tiles(ROOM room, const int col, const int row)
// {
//     int current_row = row - 1, current_col;
//     ROOM_TILE tiles[8];
//     int count = 0;
    
//     for (current_col = col - 1; current_col < col + 2; current_col++)
//     {
//         tiles[count] = room.tiles[current_row * room.width + current_col];
//         count++;
//     }
//     tiles[count] = room.tiles[++current_row * room.width + --current_col];
//     count++;

//     current_row++;
//     for (current_col = col + 1; current_col > col - 2; current_col--)
//     {
//         tiles[count] = room.tiles[current_row * room.width + current_col];
//         count++;
//     }
//     tiles[count] = room.tiles[--current_row * room.width + ++current_col];

//     return tiles;
// }

// Print every tiles in the room
void print_room(ROOM room)
{
    ROOM_TILE tile;
    for (int row = 0; row < room.height; row++)
    {
        for (int col = 0; col < room.width; col++)
        {
            tile = room.tiles[row * room.width + col];
            switch (tile.wall_type)
            {
                case upper_left_corner_wall:
                case down_left_corner_wall:
                    printf("%c%c", tile.tile_char, HORIZONTAL_WALL);
                    break;
                case horizontal_wall:
                    printf("%c%c", tile.tile_char, tile.tile_char);
                    break;
                default:
                    printf("%c ", tile.tile_char);
            }
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