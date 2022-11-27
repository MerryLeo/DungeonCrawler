#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "room.h"
#include "utility.h"
#include "exception.h"
#include "dungeon.h"

GAME* create_game()
{
    GAME* my_game = (GAME*)malloc(sizeof(GAME));
    my_game->dungeon = create_dungeon();
    return my_game;
}

void print_map(GAME game)
{
    print_dungeon(*game.dungeon);
    /*
    for (int room_num = 0; room_num < NUMBER_OF_ROOM; room_num++)
    {
        printf("Here's room %i : \n", room_num + 1);
        print_room(game.rooms[room_num]);
    }
    */
}

void play_game(GAME *game)
{
    printf(WELCOME);
    printf(START_MSG);
}

void end_game(GAME *game)
{
    free(game->dungeon);
}