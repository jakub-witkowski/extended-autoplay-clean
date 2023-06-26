#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "load_status.h"
#include "load_orders.h"

#define MAP_SIZE_X 32 // horizontal dimension of the map
#define MAP_SIZE_Y 32 // vertical dimension of the map
#define MAX_NUMBER_OF_UNITS 1002 // defines the maximum number of units that may be produced in 2000 rounds
#define MAX_NUMBER_OF_ROUNDS 20 // defines the total maximum number of rounds allowed

/* Variables holding the current round number for each player */
int player1_round_counter = 1;
int player2_round_counter = 1;

long gold = 0; // holds the amount of gold
au active_units[MAX_NUMBER_OF_UNITS]; // holds information on player and enemy active units;
int units_on_the_map_counter = 0; // holds the number of units currently present on the map

/* variables used to settle the score */
int player1_units = 0;
int player2_units = 0;
char* message = "";

int main()
{

    while ((player1_round_counter + player2_round_counter) <= MAX_NUMBER_OF_ROUNDS)
    {

    int ret;

    if ((ret = fork()) == 0)
    {
        printf("\n-----------------------------------------------");
        printf("\nPLAYER 1, ROUND %d: \n", player1_round_counter);
        char *argv1[] = {"./player1", "mapa.txt", "status.txt", "rozkazy.txt", "5", NULL};
        execvp("./player1", argv1);
        if (!ret)
        {
            perror("execvp: ");
            return 1;
        }
    }

    wait(NULL);

    /* analyze the results */
    load_status("status.txt", &units_on_the_map_counter, &gold, active_units); // read data from status.txt
    load_orders("player1.txt", "player2.txt", "rozkazy.txt", "status.txt", active_units, &units_on_the_map_counter); // read data from rozkazy.txt

    player1_round_counter++;

    int ret2;

    if ((ret2 = fork()) == 0)
    {
        printf("\n-----------------------------------------------");
        printf("\nPLAYER 2, ROUND %d: \n", player2_round_counter);
        char *argv2[] = {"./player2", "mapa.txt", "status.txt", "rozkazy.txt", "5", NULL};
        execvp("./player2", argv2);
        if (!ret)
        {
            perror("execvp: ");
            return 1;
        }
    }

    wait(NULL);

    /* analyze the results */
    load_status("status.txt", &units_on_the_map_counter, &gold, active_units); // read data from status.txt
    load_orders("player2.txt", "player1.txt", "rozkazy.txt", "status.txt", active_units, &units_on_the_map_counter); // read data from rozkazy.txt
    
    player2_round_counter++;

    }

    /* establishing the number of units */
    for (int i = 0; i < units_on_the_map_counter; i++)
    {
        if ((strcmp(active_units[i].affiliation, "P") == 0) && active_units[i].current_stamina > 0)
            player1_units++;
        if ((strcmp(active_units[i].affiliation, "E") == 0) && active_units[i].current_stamina > 0)
            player2_units++;
    }

    /* settling the score */
    if (player1_units > player2_units)
        message = "\n Player 1 wins the game! \n";
    if (player1_units < player2_units)
        message = "\n Player 2 wins the game! \n";
    if (player1_units == player2_units)
        message = "\n It's a tie! \n ";

    printf("\n-----------------------------------------------");
    printf("\nFinal outcome: ");
    printf("%s\n", message);

    return 0;
}