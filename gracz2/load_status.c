#include <stdio.h>
#include <unistd.h>
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
} au;

void load_status(char fname[], int* u, long* g, au a[])
{

    FILE * fptr;

    fptr = fopen(fname, "r");
    
    /* getting number of lines in status.txt*/
    int line_count = 0;
    char c;
        
    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n')
            line_count++;

    /* getting the number of units present on the map */
    *u = line_count - 1;

    /* going back to the beginning of the file */
    rewind(fptr); 

    /* updating gold */
    int temp;
    if (fscanf(fptr, "%d", &temp) != 1)
    {
        fprintf(stderr, "unable to parse status.txt\n");
    }

    *g = temp;

    /* updating base info */
    for (int i = 2; i <= 3; i++)
    {
        if (fscanf(fptr, "%s %s %d %d %d %d %s", a[i-2].affiliation, a[i-2].unit_type, &a[i-2].unit_id, &a[i-2].x_coord, &a[i-2].y_coord, &a[i-2].current_stamina, a[i-2].is_base_busy) != 7)
        {
            fprintf(stderr, "unable to parse status.txt\n");
        }
    }

    /* updating unit info */
    int i = 4;
    while (i <= line_count)
    {
        fscanf(fptr, "%s %s %d %d %d %d", a[i-2].affiliation, a[i-2].unit_type, &a[i-2].unit_id, &a[i-2].x_coord, &a[i-2].y_coord, &a[i-2].current_stamina);
        i++;
    }

    /* movement points counter set */
    for (int i = 0; i < *u; i++)
    {
        if (strcmp(a[i].unit_type, "K") == 0)
            a[i].remaining_movement = 5;
        else if (strcmp(a[i].unit_type, "B") == 0) // bases cannot move
            a[i].remaining_movement = 0;
        else
            a[i].remaining_movement = 2;
    }

    /* attack counter set to 1 */
    for (int i = 0; i < *u; i++)
    {
        if (strcmp(a[i].unit_type, "B") == 0) // bases cannot attack
            a[i].attack_count = 0;
        else
            a[i].attack_count = 1;
    }

fclose(fptr);
}