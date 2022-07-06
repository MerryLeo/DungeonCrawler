#include <stdlib.h>
#include "game.h"

int main()
{
    GAME my_game;
    
    // Initialise the game
    initialise_game(&my_game);

    // Play the game
    play_game(&my_game);
    print_map(my_game);

    // Free memory
    end_game(&my_game);
    
    return EXIT_SUCCESS;
}