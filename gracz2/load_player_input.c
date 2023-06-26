#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char affiliation[2];
    char unit_type[2];
    int unit_id;
    int x_coord;
    int y_coord;
    int current_stamina;
    int remaining_movement;
    int attack_count;
    char is_base_busy[2];
//    int training_time;
} au;

/* reads the remaining rounds of training from player1 or player2.txt */
void load_player_input(char fname[], au a[], int *u, int *l)
{
    /* variables used to store data read from rozkazy.txt */
    int letters = 0;
    int spaces = 0;
    const int length = 24;
    char player_input[length];
    int training_time_left;

    FILE * fptr; // input: player1.txt or player2.txt file, depending on function call

    fptr = fopen(fname, "r");
    if (!fptr)
        printf("Cannot find %s\n", fname);

    while (fgets(player_input, length, fptr) != NULL)
    {
        for (int i = 0; player_input[i] != '\n'; i++)  
        {
            if (isupper(player_input[i]))
            {
                letters++;
            }
            if (isblank(player_input[i]))
            {
                spaces++;
            }         
        }

        if (spaces == 1 && letters == 1)
        {
            sscanf(player_input, "%d T", &training_time_left);
            letters = 0;
            spaces = 0;
        }

        *l = training_time_left;
    }

    fclose(fptr);
}