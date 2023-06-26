#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//#define MAP_SIZE_X 32
//#define MAP_SIZE_Y 32

#define OPPONENTS 8

/* attack arrays */
int knight[OPPONENTS] = { 35, 35, 35, 35, 35, 35, 35, 35 };
int swordsman[OPPONENTS] = { 30, 30, 30, 20, 20, 30, 30, 30 };
int archer[OPPONENTS] = { 15, 15, 15, 15, 10, 10, 15, 15 };
int pikeman[OPPONENTS] = { 35, 15, 15, 15, 15, 10, 15, 10 };
int catapult[OPPONENTS] = { 40, 40, 40, 40, 40, 40, 40, 50 };
int ram[OPPONENTS] = { 10, 10, 10, 10, 10, 10, 10, 50 };
int worker[OPPONENTS] = { 5, 5, 5, 5, 5, 5, 5, 1 };

/* aliases for array indices  */
const int vs_K = 0;
const int vs_S = 1;
const int vs_A = 2;
const int vs_P = 3;
const int vs_C = 4;
const int vs_R = 5;
const int vs_W = 6;
const int vs_B = 7;

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

void load_orders(char fname[], char fname1[], char fname2[], char fname3[], au a[], int *u)
//void load_orders(char fname1[], char fname2[], char fname3[], au a[], int *u)
{
    /* variables used to store data read from rozkazy.txt */
    int letters = 0;
    int spaces = 0;
    int digits = 0;
    int count = 0;
    int base_id;
    int id;
    int row_number;
    const int length = 24;
    char order[length];
    char previous_player_input[length];
    char next_player_input[length];
    long gold = 0;
    char training_unit_affiliation[2];
    char training_unit_type[2];
    int training_unit_id;
    int training_unit_x;
    int training_unit_y;
    int training_unit_stamina;
    int training_time_left;
    //int base_busy = 0;
    char* action;
    char type[2];
    char message[12];
    int* attacker;
    //int attacker[8];
    //int versus = 0;
    int x;
    int y;
    int target_id;

    FILE * fptr; // input: player1.txt file
    FILE * fptr1; // input: player2.txt file
    FILE * fptr2; // input file: rozkazy.txt
    FILE * fptr3; // directing output into status.txt

    fptr = fopen(fname, "r");
    if (!fptr)
        printf("Cannot find %s\n", fname);

    while (fgets(previous_player_input, length, fptr) != NULL)
    {
        for (int i = 0; previous_player_input[i] != '\n'; i++)  
        {
            if (isupper(previous_player_input[i]))
            {
                letters++;
            }
            if (isblank(previous_player_input[i]))
            {
                spaces++;
            }         
        }

        if (spaces == 1 && letters == 1)
        {
            sscanf(previous_player_input, "%d T", &training_time_left);
            letters = 0;
            spaces = 0;
        }
    letters = 0;
    spaces = 0;
    } 

    fclose(fptr);

        if (training_time_left == 0)
        {
            if (strcmp(fname, "player1.txt") == 0)
            {
                strcpy(training_unit_affiliation, "P");
                training_unit_x = training_unit_y = 0;
                strcpy(training_unit_type, a[0].is_base_busy);
                row_number = 0;
            }
            if (strcmp(fname, "player2.txt") == 0)
            {
                strcpy(training_unit_affiliation, "E");
                training_unit_x = training_unit_y = 31;
                strcpy(training_unit_type, a[1].is_base_busy);
                row_number = 1;
            }

            training_unit_id = *u;
            (*u)++;
            
            if (strcmp(a[row_number].is_base_busy, "K") == 0)
            {
                training_unit_stamina = 70;
            }
            if (strcmp(a[row_number].is_base_busy, "S") == 0)
            {
                training_unit_stamina = 60;
            }
            if (strcmp(a[row_number].is_base_busy, "A") == 0)
            {
                training_unit_stamina = 40;
            }
            if (strcmp(a[row_number].is_base_busy, "P") == 0)
            {
                training_unit_stamina = 50;
            }
            if (strcmp(a[row_number].is_base_busy, "C") == 0)
            {
                training_unit_stamina = 50;
            }
            if (strcmp(a[row_number].is_base_busy, "R") == 0)
            {
                training_unit_stamina = 90;
            }
            if (strcmp(a[row_number].is_base_busy, "W") == 0)
            {
                training_unit_stamina = 20;
            }

            strcpy(a[training_unit_id].affiliation, training_unit_affiliation);
            strcpy(a[training_unit_id].unit_type, training_unit_type);
            a[training_unit_id].unit_id = training_unit_id;
            a[training_unit_id].x_coord = training_unit_x;
            a[training_unit_id].y_coord = training_unit_y;
            a[training_unit_id].current_stamina = training_unit_stamina;

            strcpy(a[row_number].is_base_busy, "0");//printf("Training done: %s %s %d %d %d %d\n", a[training_unit_id].affiliation, a[training_unit_id].unit_type, a[training_unit_id].unit_id, a[training_unit_id].x_coord, a[training_unit_id].y_coord, a[training_unit_id].current_stamina);
        }
        
    fptr1 = fopen(fname1, "r");
    if (!fptr1)
        printf("Cannot find %s\n", fname1);

    while (fgets(next_player_input, length, fptr1) != NULL)
    {
        for (int i = 0; next_player_input[i] != '\n'; i++)  
        {
            if (isupper(next_player_input[i]))
            {
                letters++;
            }
            if (isdigit(next_player_input[i]))
            {
                digits++;
            }
            if (isblank(next_player_input[i]))
            {
                spaces++;
            }         
        }

        if (letters == 0 && digits >= 1 && spaces == 0)
        {
            sscanf(next_player_input, "%ld", &gold);
            letters = 0;
            digits = 0;
            spaces = 0;
        }
    letters = 0;
    digits = 0;
    spaces = 0;
    }

    fclose(fptr1);

    fptr2 = fopen(fname2, "r");
    if (!fptr2)
        printf("Cannot find %s\n", fname2);

    while (fgets(order, length, fptr2) != NULL)
    {
        for (int i = 0; order[i] != '\n'; i++)
        {
            if (isupper(order[i]))
            {
                letters++;
            }
            if (isblank(order[i]))
            {
                spaces++;
            }         
        }

        if (letters == 2)
        {
            sscanf(order, "%d B %s", &base_id, type);
            letters = 0;
            spaces = 0;

            /* select proper row in case there is a mismatch between active_units row numbering and id of a unit */
            for (int g = 0; g < *u; g++)
            {
                if (a[g].unit_id == base_id)
                    row_number = g;
                else
                    continue;
            }

            strcpy(a[row_number].is_base_busy, type);
        }

        if (letters == 1 && spaces == 3)
        {
            sscanf(order, "%d M %d %d", &id, &x, &y);
            letters = 0;
            spaces = 0;

            /* select proper row in case there is a mismatch between active_units row numbering and id of a unit */
            for (int k = 0; k < *u; k++)
            {
                if (a[k].unit_id == id)
                    row_number = k;
                else
                    continue;
            }

            a[row_number].x_coord = x;
            a[row_number].y_coord = y;

        }
        
        if (letters == 1 && spaces == 2)
        {
            sscanf(order, "%d A %d", &id, &target_id);
            letters = 0;
            spaces = 0;

            /* select proper row in case there is a mismatch between active_units row numbering and id of a unit */
            for (int m = 0; m < *u; m++)
            {
                if (a[m].unit_id == id)
                    row_number = m;
                else
                    continue;
            }

            if (strcmp(a[row_number].unit_type, "K") == 0)
            {
                attacker = knight;
            }
            else if (strcmp(a[row_number].unit_type, "S") == 0)
            {
                attacker = swordsman;
            }
            else if (strcmp(a[row_number].unit_type, "A") == 0)
            {
                attacker = archer;
            }
            else if (strcmp(a[row_number].unit_type, "P") == 0)
            {
                attacker = pikeman;
            }
            else if (strcmp(a[row_number].unit_type, "C") == 0)
            {
                attacker = catapult;
            }
            else if (strcmp(a[row_number].unit_type, "R") == 0)
            {
                attacker = ram;
            }
            else if (strcmp(a[row_number].unit_type, "W") == 0)
            {
                attacker = worker;
            }

            /* select proper row in case there is a mismatch between active_units row numbering and id of a unit */
            for (int n = 0; n < *u; n++)
            {
                if (a[n].unit_id == target_id)
                    row_number = n;
                else
                    continue;
            }

            if (strcmp(a[row_number].unit_type, "K") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_K];
            }
            else if (strcmp(a[row_number].unit_type, "S") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_S];
            }
            else if (strcmp(a[row_number].unit_type, "A") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_A];
            }
            else if (strcmp(a[row_number].unit_type, "P") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_P];
            }
            else if (strcmp(a[row_number].unit_type, "C") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_C];
            }
            else if (strcmp(a[row_number].unit_type, "R") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_R];
            }
            else if (strcmp(a[row_number].unit_type, "W") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_W];
            }
            else if (strcmp(a[row_number].unit_type, "B") == 0)
            {
                a[row_number].current_stamina -= attacker[vs_B];
            }
            
            if ((strcmp(a[row_number].unit_type, "B") == 0) && a[target_id].current_stamina <= 0)
            {
                if (strcmp(a[row_number].affiliation, "P") == 0)
                {
                    printf("\nPlayer 1 loses the base, game over.\n");
                    exit(0);
                }

                if (strcmp(a[row_number].affiliation, "E") == 0)
                {
                    printf("\nPlayer 2 loses the base, game over.\n");
                    exit(0);
                }
            }

            if (a[row_number].current_stamina <= 0)
            {
                a[row_number].current_stamina = -1;
            }
        }    
    }

    fclose(fptr2);

    /* erasing status.txt */
    fptr3 = fopen(fname3, "w");
    if (!fptr3)
        printf("Cannot find %s\n", fname3);

    fclose(fptr3);

    /* writing the analyzed data */
    fptr3 = fopen(fname3, "a");

    /* Save the amount of gold */
	if (fprintf(fptr3, "%ld\n", gold) < 0)
    {
        fprintf(stderr, "unable to write bank status\n");
    }

    /* Save base and unit data */
    for (int j = 0; j < *u; j++)
    {

        if (a[j].current_stamina == -1)
        {
            continue;
        }

        if (strcmp(a[j].unit_type, "B") == 0)
        {
            if (fprintf(fptr3, "%s %s %d %d %d %d %s\n", a[j].affiliation, a[j].unit_type, a[j].unit_id, a[j].x_coord, a[j].y_coord, a[j].current_stamina, a[j].is_base_busy) < 0)
            {
                fprintf(stderr, "unable to write base data\n");
            }
        }

        if (strcmp(a[j].unit_type, "B") != 0)
        {
            if (fprintf(fptr3, "%s %s %d %d %d %d\n", a[j].affiliation, a[j].unit_type, a[j].unit_id, a[j].x_coord, a[j].y_coord, a[j].current_stamina) < 0)
            {
                fprintf(stderr, "unable to write unit data\n");
            }
        }
    }
    
    fclose(fptr3);
}