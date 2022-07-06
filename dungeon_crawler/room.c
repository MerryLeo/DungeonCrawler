#include <stdlib.h>
#include <stdio.h>
#include "room.h"

// Create an empty room with no walls
void create_empty_room(ROOM *room, const int width, const int height)
{
    room->tiles = (ROOM_TILE*)malloc(width * height * sizeof(ROOM_TILE));
    ROOM_TILE *tile;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tile = &(room->tiles[row * width + col]);
            create_tile(tile, EMPTY_TILE_CODE, empty);
        }
    }
    room->width = width;
    room->height = height;
}

// Add walls to an empty room
void add_walls(ROOM *room)
{
    int width = room->width;
    int height = room->height;
    int row, col;
    ROOM_TILE *tile1, *tile2;

    // Add top and bottom walls
    row = (height - 1) * width;
    for (col = 1; col < width - 1; col++)
    {
        // Get a reference to the top and bottom tile
        tile1 = &(room->tiles[col]);
        tile2 = &(room->tiles[col + row]);

        // Update top/bottom tiles
        tile1->tile_char = HORIZONTAL_WALL;
        tile1->type = wall;
        tile2->tile_char = HORIZONTAL_WALL;
        tile2->type = wall;
    }

    // Add right and left walls
    col = width;
    for (row = 1; row < height - 1; row++)
    {
        // Get a reference to the left and right tile
        tile1 = &(room->tiles[row * col + col - 1]);
        tile2 = &(room->tiles[row * col]);

        // Update left/right tiles
        tile1->tile_char = VERTICAL_WALL;
        tile1->type = wall;
        tile2->tile_char = VERTICAL_WALL;
        tile1->type = wall;
    }

    // Get a reference to left corner tiles
    tile1 = &(room->tiles[0]);
    tile2 = &(room->tiles[width - 1]);

    // Update left corner tiles
    tile1->tile_char = TOP_LEFT_CORNER;
    tile1->type = wall;
    tile2->tile_char = TOP_RIGHT_CORNER;
    tile2->type = wall;

    // Get a reference to right corner tiles
    tile1 = &(room->tiles[width * (height - 1)]);
    tile2 = &(room->tiles[width * height - 1]);

    // Update right corner tiles
    tile1->tile_char = BOTTOM_LEFT_CORNER;
    tile1->type = wall;
    tile2->tile_char = BOTTOM_RIGHT_CORNER;
    tile2->type = wall;
}

// Create a single tile
void create_tile(ROOM_TILE *tile, const unsigned char symbol, TILE_TYPE type) 
{
    tile->door = NULL;
    tile->item = NULL;
    tile->light_level = 0;
    tile->tile_char = symbol;
    tile->type = type;
}

// Print every tiles in the room
void print_room(ROOM room)
{
    int width = room.width;
    int height = room.height;
    char tile_char;
    char next_char;
    
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Get tile
            tile_char = room.tiles[row * width + col].tile_char;

            // Print top and bottom
            if (row == 0 || row == height - 1)
            {
                // Print left corners
                if (col == 0)
                {
                    next_char = room.tiles[row * width + col + 1].tile_char;
                    printf("%c%c", tile_char, next_char);
                }

                // Print right corners
                else if (col == width - 1)
                    printf("%c", tile_char, tile_char);

                // Print walls
                else
                    printf("%c%c", tile_char, tile_char);
            }

            // Print everything else
            else
                printf("%c ", tile_char);
        }
        printf("\n");
    }
    printf("\n");
}

// Free memory of a single room tile
void delete_tile(ROOM_TILE *tile)
{
    free(tile->door);
    tile->door = NULL;
}

// Free memory of a room
void delete_room(ROOM *room)
{
    int width = room->width;
    int height = room->height;
    int nbr_of_rooms = width * height;

    // Free memory for every tiles
    for (int room_num = 0; room_num < nbr_of_rooms; room_num++)
        delete_tile(&(room->tiles[room_num]));

    // Free memory for the tiles
    free(room->tiles);
    room->tiles = NULL;
}