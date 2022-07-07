#include "room.h"

#ifndef GAME_H
#define GAME_H

#define NUMBER_OF_ROOM 25
#define NUMBER_OF_PRIMARY_ROOM 17
#define START_MSG "What do you want to do?\n"
#define WELCOME "Welcome to my dungeon crawler!\n\n"

typedef struct game {
    ROOM rooms[NUMBER_OF_ROOM];
} GAME;

void create_game(GAME *game);
void print_map(GAME game);
void play_game(GAME *game);
void end_game(GAME *game);

#endif