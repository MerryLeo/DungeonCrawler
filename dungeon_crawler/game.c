#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "room.h"
#include "utility.h"

void initialise_game(GAME *game)
{
    // ROOM dimensions
    int width;
    int height;
    int remove_chunk = FALSE;
    int position;

    // Creates every room
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        width = generate_number(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
        height = generate_number(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
        remove_chunk = clamp01(generate_number(-5, 5));
        ROOM *room = &(game->rooms[room_num]);
        create_empty_room(room, width, height);

        if (remove_chunk == TRUE)
        {
            position = generate_number(0, 4);
            switch (position)
            {
                case 0:
                    remove_chunk_from_room(room, 0, height / 2, 0, width / 2);
                    break;
                case 1:
                    remove_chunk_from_room(room, 0, height / 2, width / 2, width - 1);
                    break;
                case 2:
                    remove_chunk_from_room(room, height / 2, height - 1, 0, width / 2);
                    break;
                case 3:
                    remove_chunk_from_room(room, height / 2, height - 1, width / 2, width - 1);
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
    // print_room(game->rooms[0]);
}

void end_game(GAME *game)
{
    ROOM *room_ptr;
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        room_ptr = &(game->rooms[room_num]);
        delete_room(room_ptr);
    }
}