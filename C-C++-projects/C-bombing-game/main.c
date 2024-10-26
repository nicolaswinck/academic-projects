#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_LIVES 1
#define MAX_LIVES 10

#define MIN_PATH_LEN 10
#define MAX_PATH_LEN 70
#define MULT_PATH 5

// Structures for player and game info.
struct PlayerInfo
{
    char inputPlayerChar;
    int inputNumLives;
    int playerHistory[MAX_PATH_LEN];
    int inputNextMove;
    int treasureCount;
};

struct GameInfo
{
    int inputPathLen;
    int inputNumMoves;
    int inputBombPlaces[MAX_PATH_LEN];
    int inputTreasurePlaces[MAX_PATH_LEN];
};

int main(void)
{
    // Variables: validation flags and iterators.
    int inputOk, gameOver, i, j, k;

    // Erasing history: setting everything to zero.
    struct PlayerInfo player = { 0 };
    struct GameInfo game = { 0 };

    // Displaying the game heather.
    printf("================================\n"
        "         Treasure Hunt!\n"
        "================================\n\n");

    printf("Player configuration\n"
        "--------------------\n");

    // Prompting user for player character.
    printf("Enter a single character to represent the player: ");
    scanf(" %c", &player.inputPlayerChar);

    // Assigning flag to zero.
    inputOk = 0;

    // Prompting user for the numbering of lives (validation).
    do {
        printf("Set the number of lives: ");
        scanf("%d", &player.inputNumLives);

        if (player.inputNumLives < MIN_LIVES || player.inputNumLives > MAX_LIVES)
        {
            printf("     Must be between %d and %d!\n", MIN_LIVES, MAX_LIVES);
        }

        else
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    printf("Player configuration set-up is complete\n\n");
    printf("Game Configuration\n"
        "------------------\n");

    // Resetting validation flag.
    inputOk = 0;

    // Prompting user for the path length (validation).
    do {
        printf("Set the path length (a multiple of %d between %d-%d): ",
            MULT_PATH, MIN_PATH_LEN, MAX_PATH_LEN);
        scanf("%d", &game.inputPathLen);

        if (game.inputPathLen < MIN_PATH_LEN || game.inputPathLen > MAX_PATH_LEN ||
            ((game.inputPathLen % MULT_PATH) != 0))
        {
            printf("     Must be a multiple of %d and between %d-%d!\n",
                MULT_PATH, MIN_PATH_LEN, MAX_PATH_LEN);
        }
        else
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    // Resetting validation flag.
    inputOk = 0;

    // Prompting user for the number of moves (validation).
    do {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &game.inputNumMoves);

        if (game.inputNumMoves < player.inputNumLives ||
            game.inputNumMoves >(float)game.inputPathLen * 0.75)
        {
            printf("    Value must be between %d and %d!\n",
                player.inputNumLives, (int)(game.inputPathLen * 0.75));
        }
        else
        {
            inputOk = 1;
            printf("\n");
        }

    } while (inputOk == 0);

    // Prompting user for bomb placement.
    printf("Bomb Placement\n"
        "--------------\n");
    printf("Enter the bomb positions in sets of %d where a value\n"
        "of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n"
        "(Example: 1 0 0 1 1) NOTE: there are %d to set!\n",
        MULT_PATH, game.inputPathLen);

    // Main loop: iterating using the total path # divided by the multiple set.
    for (i = 0, k = 0; i < game.inputPathLen; i += MULT_PATH)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + MULT_PATH);

        // Secondary loop: getting input for each bomb place.
        for (j = 0; j < MULT_PATH; j++, k++)
        {
            // Assigning each input to an element of the array.
            scanf("%d", &game.inputBombPlaces[k]);
        }
    }

    printf("Bom placement set\n\n");

    // Prompting user for treasure placement.
    printf("Treasure Placement\n"
        "------------------\n");
    printf("Enter the treasure placements in sets of %d where a value\n"
        "of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n"
        "(Example: 1 0 0 1 1) NOTE: there are %d to set!\n",
        MULT_PATH, game.inputPathLen);

    // Main loop: iterating using the total path # divided by the multiple set.
    for (i = 0, k = 0; i < game.inputPathLen; i += MULT_PATH)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + MULT_PATH);

        // Secondary loop: getting input for each treasure place.
        for (j = 0; j < MULT_PATH; j++, k++)
        {
            // Assigning each input to an element of the array.
            scanf("%d", &game.inputTreasurePlaces[k]);
        }
    }

    printf("Treasure placement set\n\n");
    printf("Game configuration setup is complete...\n\n");

    // Displaying the heather for the whole game configuration.
    printf("------------------------------------\n"
        "Treasure Hunt configuration settings\n"
        "------------------------------------\n");

    // Displaying player information.
    printf("Player:\n");
    printf("   Symbol     : %c\n", player.inputPlayerChar);
    printf("   Lives      : %d\n", player.inputNumLives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n\n");

    // Displaying game information.
    printf("Game:\n");
    printf("   Path Length: %d\n", game.inputPathLen);
    printf("   Bombs      : ");

    // Displaying all the bomb array elements in a single row, no spaces.
    for (i = 0; i < game.inputPathLen; i++)
    {
        printf("%d", game.inputBombPlaces[i]);
    }

    putchar('\n');
    printf("   Treasure   : ");

    // Displaying all the treasure array elements in a single row, no spaces.
    for (i = 0; i < game.inputPathLen; i++)
    {
        printf("%d", game.inputTreasurePlaces[i]);
    }

    printf("\n\n");

    // Displaying message to user, indicating the beggining of the game.
    printf("====================================\n"
        "~ Get ready to play Treasure Hunt! ~\n"
        "====================================\n");

    // Setting validation flags to zero.
    inputOk = 0;
    gameOver = 0;

    // Starting the game loop.
    do {
        printf("\n  ");

        // Updating the game path (line-2 of the game board).
        
        for (i = 0; i < game.inputPathLen; i++)
        {
            if (player.playerHistory[i + 1] == 1)
            {
                if (game.inputBombPlaces[i] == 1 &&
                    game.inputTreasurePlaces[i] == 0)
                {
                    printf("!");
                }

                if (game.inputTreasurePlaces[i] == 1 &&
                    game.inputBombPlaces[i] == 0)
                {
                    printf("$");
                }

                if (game.inputBombPlaces[i] == 1 &&
                    game.inputTreasurePlaces[i] == 1)
                {
                    printf("&");
                }

                if (game.inputTreasurePlaces[i] == 0 &&
                    game.inputBombPlaces[i] == 0)

                {
                    printf(".");
                }
            }
            else
            {
                printf("-");
            }
        }

        printf("\n  ");

        // Building the major position ruler (line-3 of the game board).
        for (i = 0; i < game.inputPathLen; i++)
        {
            if ((i + 1) % 10)
            {
                printf("|");

            }
            else
            {
                printf("%d", (i + 1) / 10);
            }
        }

        printf("\n  ");

        // Building the minor position ruler (line-4 of the game board)
        for (i = 0, j = 0; i < game.inputPathLen; i++, j++)
        {
            if ((i + 1) % 10)
            {
                printf("%d", j + 1);

            }
            else
            {
                printf("%d", 0);
                j = -1;
            }
        }

        putchar('\n');

        // Displaying the player's statistics.
        printf("+---------------------------------------------------+\n");
        printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n",
            player.inputNumLives, player.treasureCount, game.inputNumMoves);
        printf("+---------------------------------------------------+\n");

        // Checking for a game over condition.
        if (player.inputNumLives < 1 || game.inputNumMoves < 1)
        {
            gameOver = 1;
        }
        else
        {
            // Validating user's next move input.
            do {
                printf("Next Move [1-%d]: ", game.inputPathLen);
                scanf("%d", &player.inputNextMove);

                if (player.inputNextMove < 1 || player.inputNextMove > game.inputPathLen)
                {
                    printf("  Out of Range!\n");
                }
                else
                {
                    inputOk = 1;
                }

            } while (inputOk == 0);

            // Resetting validation flag to zero.
            inputOk = 0;

            putchar('\n');

            // Checking for the moves and updating player's information.
            if (player.playerHistory[player.inputNextMove] == 1)
            {
                printf("===============> Oh! You've been here before!\n\n");
            }
            else
            {
                if (game.inputBombPlaces[player.inputNextMove - 1] == 0 &&
                    game.inputTreasurePlaces[player.inputNextMove - 1] == 0)
                {
                    printf("===============> [.] ...Nothing found here... [.]\n\n");
                }
                else if (game.inputBombPlaces[player.inputNextMove - 1] == 1 &&
                    game.inputTreasurePlaces[player.inputNextMove - 1] == 0)
                {
                    printf("===============> [!] !!! BOOOOOM !!! [!]\n\n");

                    player.inputNumLives--;
                }
                else if (game.inputBombPlaces[player.inputNextMove - 1] == 0 &&
                    game.inputTreasurePlaces[player.inputNextMove - 1] == 1)
                {
                    printf("===============> [$] $$$ Found Treasure! $$$ [$]\n\n");

                    player.treasureCount++;
                }
                else if (game.inputBombPlaces[player.inputNextMove - 1] == 1 &&
                    game.inputTreasurePlaces[player.inputNextMove - 1] == 1)
                {
                    printf("===============> [&] !!! BOOOOOM !!! [&]\n");
                    printf("===============> [&] $$$ Life Insurance Payout! [&]\n\n");

                    player.inputNumLives--;
                    player.treasureCount++;
                }

                game.inputNumMoves--;

                // Checking for counting stats to display the right messages.
                if (game.inputNumMoves < 1)
                {
                    printf("No more moves remaining!\n\n");
                }

                if (player.inputNumLives < 1)
                {
                    printf("No more lives remaining!\n\n");
                }

                player.playerHistory[player.inputNextMove] = 1;
            }

            printf("  ");

            // Updating the player's most recent position (line-1 of the game board).
            // Resetting iterator to zero.
            i = 0;

            while (i < player.inputNextMove)
            {
                if (i != player.inputNextMove - 1)
                {
                    printf(" ");
                }
                else
                {
                    printf("%c", player.inputPlayerChar);
                }

                i++;
            }
        }
                      
    } while (gameOver == 0);

    // Displaying final message to the user, indicating the end of the game.
    putchar('\n');

    printf("##################\n"
        "#   Game over!   #\n"
    "##################\n\n");

    printf("See you next time!\n");

    return 0;
}