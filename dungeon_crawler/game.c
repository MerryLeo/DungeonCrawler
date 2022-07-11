#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "room.h"
#include "utility.h"
#include "exception.h"

void create_game(GAME *game)
{
    int room_width, room_height;
    int remove_chunk = FALSE;
    RECTANGLE tiles_to_remove;
    COORD first_corner, last_corner;
    int corner_to_remove_tiles;
    int error_code;

    // Creates every room
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        room_width = generate_number(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
        room_height = generate_number(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
        remove_chunk = clamp01(generate_number(-5, 5));

        ROOM *room = &(game->rooms[room_num]);
        create_empty_room(room, room_width, room_height);

        // Decide to remove a part of the room
        if (remove_chunk == TRUE)
        {
            corner_to_remove_tiles = generate_number(0, 4);
            switch (corner_to_remove_tiles)
            {
                // Remove upper-left corner of the room
                case 0:
                    first_corner = create_coord(0, 0);
                    last_corner = create_coord(room_width / 2, room_height / 2);
                    tiles_to_remove = create_rectangle(first_corner, last_corner);
                    remove_tiles(room, tiles_to_remove);
                    break;

                // Remove upper-right corner of the room
                case 1:
                    first_corner = create_coord(room_width / 2, room_height / 2);
                    last_corner = create_coord(room_width - 1, 0);
                    tiles_to_remove = create_rectangle(first_corner, last_corner);
                    remove_tiles(room, tiles_to_remove);
                    break;

                // Remove lower-left corner of the room
                case 2:
                    first_corner = create_coord(0, room_height / 2);
                    last_corner = create_coord(room_width / 2, room_height - 1);
                    tiles_to_remove = create_rectangle(first_corner, last_corner);
                    remove_tiles(room, tiles_to_remove);
                    break;

                // Remove lower-right corner of the room
                case 3:
                    first_corner = create_coord(room_width / 2, room_height / 2);
                    last_corner = create_coord(room_width - 1, room_height - 1);
                    tiles_to_remove = create_rectangle(first_corner, last_corner);
                    remove_tiles(room, tiles_to_remove);
                    break;
            }
        }
        add_walls(room);
    }
    
}

void print_map(GAME game)
{
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        printf("Here's room %i : \n", room_num + 1);
        print_room(game.rooms[room_num]);
    }
}

void play_game(GAME *game)
{
    printf(WELCOME);
    printf(START_MSG);
}

void end_game(GAME *game)
{
    free(game->rooms);
}