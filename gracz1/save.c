#include <stdio.h>
#include <string.h>

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

void save(long* g, int* u, au a[], int* t, int* l)
{
    int x, y;

    FILE *f = fopen("player1.txt", "w");
    if (!f)
    {
        fprintf(stderr, "unable to open file for writing\n");
        return;
    }

    if (*t == 1)
    { 
        if (fprintf(f, "%d T\n", --(*l)) < 0)
            fprintf(stderr, "unable to write training units\n");
    }

    /* Save the amount of gold */
	if (fprintf(f, "%ld\n", *g) < 0)
    {
        fprintf(stderr, "unable to write bank status\n");
    }

    fclose(f);
}