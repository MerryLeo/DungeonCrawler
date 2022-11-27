#include <stdlib.h>
#include "game.h"
#include "room.h"

#define ROOM_NUMBER 4

int main()
{
    initialise_random();

    // Create Empty Rooms
    for (int i = 0; i < ROOM_NUMBER; i++)
    {
        short width = generate_number(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
        short height = generate_number(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
        ROOM room = create_empty_room(width + 1, height + 1);
        remove_tiles(&room, create_rectangle(3, 3, width, height));
        add_walls(&room);
        print_room(room);
    }
    // initialise_random();
    
    // // Initialise the game
    // GAME *my_game = create_game();

    // // Play the game
    // play_game(my_game);
    // print_map(*my_game);

    // // Free memory
    // end_game(my_game);
    
    return EXIT_SUCCESS;
}