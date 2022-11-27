#include "room.h"

#ifndef DUNGEON_H
#define DUNGEON_H

#define NUMBER_OF_ROOMS 15

typedef struct {
    ROOM *rooms;
    int size;
} DUNGEON;

// DUNGEON* create_dungeon();
void print_dungeon(DUNGEON dungeon);

#endif
