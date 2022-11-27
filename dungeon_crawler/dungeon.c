#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include "dungeon.h"
#include "room.h"
#include "utility.h"

// Initialise a new dungeon and return a pointer to it
// DUNGEON* create_dungeon()
// {
//     // Memory Allocation for the dungeon and its rooms
//     DUNGEON *dungeon_ptr = (DUNGEON*)malloc(sizeof(DUNGEON));
//     dungeon_ptr->size = NUMBER_OF_ROOMS;
//     int dungeon_size = dungeon_ptr->size;
//     dungeon_ptr->rooms = (ROOM*)malloc(dungeon_size * sizeof(ROOM));

//     // Rooms creation
//     ROOM *room, *next_room_ptr;
//     int room_num;
//     int room_width, room_height;
//     int random_num;
//     RECTANGLE rect;
//     for (room_num = 0; room_num < dungeon_size; room_num++)
//     {
//         // Get a reference to the room
//         room = &dungeon_ptr->rooms[room_num];

//         // Create an empty room with random dimensions
//         room_width = generate_number(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
//         room_height = generate_number(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
//         room = &create_empty_room(room_width, room_height);

//         // Remove a random corner of the room
//         random_num = generate_number(0, 5);
//         switch (random_num)
//         {
//             // Remove upper left corner of the room
//             case 0:
//                 rect = create_rectangle(0, 0, room_width / 2 + 1, room_height / 2 + 1);
//                 remove_tiles(room, rect);
//                 break;

//             // Remove upper right corner of the room
//             case 1:
//                 rect = create_rectangle(room_width / 2 + 1, 0, room_width - 1, room_height / 2);
//                 remove_tiles(room, rect);
//                 break;

//             // Remove lower left corner of the room
//             case 2:
//                 rect = create_rectangle(0, room_height / 2 + 1, room_width / 2 + 1, room_height - 1);
//                 remove_tiles(room, rect);
//                 break;

//             // Remove lower right corner of the room
//             case 3:
//                 rect = create_rectangle(room_width / 2 + 1, room_height / 2 + 1, room_width - 1, room_height - 1);
//                 remove_tiles(room, rect);
//                 break;

//             // Don't remove any part of the room
//             default:
//                 break;
//         }

//         // Add walls around the room
//         add_walls(room);
//     }

//     // Add doors to every rooms
//     for (room_num = 0; room_num < dungeon_size - 1; room_num++)
//     {
//         room = &dungeon_ptr->rooms[room_num];
//         next_room_ptr = &dungeon_ptr->rooms[room_num + 1];
//         add_doors(room, next_room_ptr);
//     }

//     print_colored("Dungeon created!\n", COLOR_BLUE);

//     return dungeon_ptr;
// }

// Print the whole dungeon
void print_dungeon(DUNGEON dungeon)
{
    int dungeon_size = dungeon.size;
    for (int room_num = 0; room_num < dungeon_size; room_num++)
    {
        printf("Room %i: \n", room_num + 1);
        print_room(dungeon.rooms[room_num]);
    }
}