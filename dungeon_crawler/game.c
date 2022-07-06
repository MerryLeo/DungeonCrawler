#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "room.h"
#include "utility.h"

void initialise_game(GAME *game)
{
    // Room dimensions
    int width;
    int height;

    // Creates every room
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        width = generate_number(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
        height = generate_number(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
        ROOM *room = &(game->rooms[room_num]);
        generate_empty_room(room, width, height);
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