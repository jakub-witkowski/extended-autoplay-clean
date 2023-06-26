#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

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

void attack(char fname[], au a[], int* u)
{
    int combat_ready = 0; // controls the validation process
    int attack_range = 0; // from what distance can a unit attack?
    int targets_within_range = 0; // holds the number of enemy units within the range of attack
    int distance; // the distance between the attacker unit and the target unit
    int attacker_id; // the requested attacking unit id
    int target_id; // the requested target unit id

    for (int i = 0; i < *u; i++)
    {
        /* cannot select enemy units */
        if ((strcmp(a[i].affiliation, "E") == 0))
            combat_ready = -1;
        
        /* cannot select units in training 
        if ((strcmp(a[i].affiliation, "P") == 0) && (a[i].training_time > 0))
            combat_ready = -1;*/

        /* cannot use the base for attack */
        if ((strcmp(a[i].unit_type, "B") == 0))
            combat_ready = -1;
        
        /* checking the remaining movement points */
        if ((strcmp(a[i].affiliation, "P") == 0) && (a[i].remaining_movement < 1))
            combat_ready = -1;

        /* has the unit already made an attack in the current round? */
        if ((strcmp(a[i].affiliation, "P") == 0) && (a[i].attack_count < 1))
            combat_ready = -1;

        /* conditions for attack satisfied */
        if ((strcmp(a[i].affiliation, "P") == 0) && (a[i].remaining_movement >= 1) && (a[i].attack_count == 1))
            combat_ready = 1;

        /* determining the attack range */
        if (combat_ready == 1)
        {
            if (strcmp(a[i].unit_type, "A") == 0)
                attack_range = 5;
            else if (strcmp(a[i].unit_type, "P") == 0)
                attack_range = 2;
            else if (strcmp(a[i].unit_type, "C") == 0)
                attack_range = 7;
            else
                attack_range = 1;
        }

        /* are there any enemy units within the range of the unit? */
        if (combat_ready == 1 && attack_range > 0)
        {
            for (int j = 0; j < *u; j++)
            {
                distance = abs(a[i].x_coord - a[j].x_coord) + abs(a[i].y_coord - a[j].y_coord);

                if (strcmp(a[j].affiliation, "P") == 0)
                    continue;
                if (strcmp(a[j].affiliation, "E") == 0)
                {
                    if (attack_range > 1)
                    {
                        if ((distance <= attack_range) && a[i].attack_count != 0)
                        {
                            targets_within_range++;
                            attacker_id = a[i].unit_id;
                            target_id = a[j].unit_id;
                            a[i].attack_count = 0;
                            a[i].remaining_movement = 0;
                            printf("Ordering unit %d to attack enemy unit %d. \n", attacker_id, target_id);

                            /* order successful, write to file */
                            FILE *fptr; 
                            fptr = fopen(fname, "a");
                            if (!fptr)
                            {
                                printf("Cannot open rozkazy.txt");
                            }

                            if (fprintf(fptr, "%d A %d\n", attacker_id, target_id) < 0)
                            {
                                fprintf(stderr, "\nUnable to write order to file.\n");
                            }

                            fclose(fptr);

                            continue; // skip if there's more than one enemy unit within range;
                        }
                    }
                    else if ((attack_range > 0 && attack_range <= 1) && a[i].attack_count != 0)
                    {
                        if (distance <= (a[i].remaining_movement + 1))
                        {
                            targets_within_range++;
                            attacker_id = a[i].unit_id;
                            target_id = a[j].unit_id;
                            a[i].remaining_movement -= distance;
                            a[i].attack_count = 0;
                            a[i].remaining_movement = 0;
                            printf("Ordering unit %d to attack enemy unit %d. \n", attacker_id, target_id);

                            /* order successful, write to file */
                            FILE *fptr; 
                            fptr = fopen(fname, "a");
                            if (!fptr)
                            {
                                printf("Cannot open rozkazy.txt");
                            }

                            if (fprintf(fptr, "%d A %d\n", attacker_id, target_id) < 0)
                            {
                                fprintf(stderr, "\nUnable to write order to file.\n");
                            }

                            fclose(fptr);

                            continue; // skip if there's more than one enemy unit within range;
                        }
                    }
                }
            }
        }
    }     
}