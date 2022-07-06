#include <stdlib.h>
#include <stdio.h>
#include "room.h"

// Create an empty room with walls
void generate_empty_room(ROOM *room, const int width, const int height)
{
    room->tiles = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            room->tiles[row * width + col] = EMPTY_TILE_CODE;
    room->width = width;
    room->height = height;
}

// Add walls to an empty room
void add_walls(ROOM *room)
{
    int width = room->width;
    int height = room->height;
    int row, col;

    // Add top and bottom walls
    row = (height - 1) * width;
    for (col = 1; col < width - 1; col++)
    {
        room->tiles[col] = HORIZONTAL_WALL;
        room->tiles[col + row] = HORIZONTAL_WALL;
    }

    // Add right and left walls
    col = width;
    for (row = 1; row < height - 1; row++)
    {
        room->tiles[row * col + col - 1] = VERTICAL_WALL;
        room->tiles[row * col] = VERTICAL_WALL;
    }

    // Add all four corners
    room->tiles[0] = TOP_LEFT_CORNER;
    room->tiles[width - 1] = TOP_RIGHT_CORNER;
    room->tiles[width * (height - 1)] = BOTTOM_LEFT_CORNER;
    room->tiles[width * height - 1] = BOTTOM_RIGHT_CORNER;
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
            tile_char = room.tiles[row * width + col];

            // Print top and bottom
            if (row == 0 || row == height - 1)
            {
                // Print left corners
                if (col == 0)
                {
                    next_char = room.tiles[row * width + col + 1];
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

// Free memory
void delete_room(ROOM *room)
{
    free(room->tiles);
    room->tiles = NULL;
}