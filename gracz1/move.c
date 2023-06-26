#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

/* auxiliary arrays for determining the x vs y spread in distance */
const int spread1[2][2] = { {0, 1}, {1, 0} };
const int spread2[3][2] = { {0, 2}, {1, 1}, {2, 0} };
const int spread3[4][2] = { {0, 3}, {1, 2}, {2, 1}, {3, 0} };
const int spread4[5][2] = { {0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0} };
const int spread5[6][2] = { {0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0} };

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

void move(char fname[], au a[], int* u, int m[][MAP_SIZE_X])
{   
	srand(time(NULL)); // providing core for generating random numbers

    /* how many fields a unit is ordered to move in x and y direction */
	int x_axis_move;
    int y_axis_move;

    int row_number; // controls the use of the spread arrays
    int dice_cast = 0; // controls the validation process: 0 = no move generated; 1 = moves for two axes generated;

    int allowed_movement; // unit's movement points
    int distance; // the distance the user attempts to move the unit
    int x; // target x coordinate
    int y; // target y coordinate

    for (int i = 0; i < *u; i++)
    {
        /* cannot select enemy units */
        if ((strcmp(a[i].affiliation, "E") == 0))
            dice_cast = -1;
        
        /* cannot move bases */
        if ((strcmp(a[i].unit_type, "B") == 0))
            dice_cast = -1;

        /* knights have 5 points of movement */
        if ((strcmp(a[i].affiliation, "P") == 0) && (strcmp(a[i].unit_type, "B") != 0) && (strcmp(a[i].unit_type, "K") == 0)) 
        { 
            distance = rand() % 6;
            switch (distance)
            {
                case 0:
                    x_axis_move = 0;
                    y_axis_move = 0;
                    dice_cast = -1;
                    break;
                case 1:
                    row_number = rand() % 2;
                    x_axis_move = spread1[row_number][0];
                    y_axis_move = spread1[row_number][1];
                    dice_cast = 1;
                    break;
                case 2:
                    row_number = rand() % 3;
                    x_axis_move = spread2[row_number][0];
                    y_axis_move = spread2[row_number][1];
                    dice_cast = 1;
                    break;
                case 3:
                    row_number = rand() % 4;
                    x_axis_move = spread3[row_number][0];
                    y_axis_move = spread3[row_number][1];
                    dice_cast = 1;
                    break;
                case 4:
                    row_number = rand() % 5;
                    x_axis_move = spread4[row_number][0];
                    y_axis_move = spread4[row_number][1];
                    dice_cast = 1;
                    break;
                case 5:
                    row_number = rand() % 6;
                    x_axis_move = spread5[row_number][0];
                    y_axis_move = spread5[row_number][1];
                    dice_cast = 1;
                    break;
            } 
        }

        /* all other movable units have 2 points of movement */
        else if ((strcmp(a[i].affiliation, "P") == 0) && (strcmp(a[i].unit_type, "B") != 0) && (strcmp(a[i].unit_type, "K") != 0))
        {
            distance = rand() % 3;
            switch (distance)
            {
                case 0:
                    x_axis_move = 0;
                    y_axis_move = 0;
                    dice_cast = -1;
                    break;
                case 1:
                    row_number = rand() % 2;
                    x_axis_move = spread1[row_number][0];
                    y_axis_move = spread1[row_number][1];
                    dice_cast = 1;
                    break;
                case 2:
                    row_number = rand() % 3;
                    x_axis_move = spread2[row_number][0];
                    y_axis_move = spread2[row_number][1];
                    dice_cast = 1;
                    break;
            }
        }

        /* Validating target coordinates */
        if (dice_cast == 1)
        {
            /* validating the draws against the map */
            if (((a[i].x_coord + x_axis_move) >= MAP_SIZE_X) && ((a[i].y_coord + y_axis_move) >= MAP_SIZE_Y))
                dice_cast = -1; // cannot go outside the map
            if (distance > a[i].remaining_movement)
                dice_cast = -1; // cannot exceed remaining movement
            if (m[a[i].y_coord + y_axis_move][a[i].x_coord + x_axis_move] == 9)
                dice_cast = -1; // cannot go on natural obstacles
            if (m[a[i].y_coord + y_axis_move][a[i].x_coord + x_axis_move] == 2)
                dice_cast = -1; // cannot go on enemy-held field
            if (m[a[i].y_coord + y_axis_move][a[i].x_coord + x_axis_move] == 0)
                for (int j = 0; j < *u; j++)
		            if ((strcmp(a[j].affiliation, "E") == 0) && (a[j].x_coord == (a[i].x_coord + x_axis_move)) && (a[j].y_coord == (a[i].y_coord + y_axis_move)))
                        dice_cast = -1; // cannot go on enemy-held field
        }

        if (dice_cast == 1)
        {
            x = a[i].x_coord + x_axis_move;
            y = a[i].y_coord + y_axis_move;
            a[i].remaining_movement -= distance;

            printf("Ordering unit %d to move from (X: %d, Y: %d) to (X: %d, Y: %d).\n", a[i].unit_id, a[i].x_coord, a[i].y_coord, x, y);
            
            /* order successful, write to file */
            FILE *fptr;

            fptr = fopen(fname, "a");
            if (!fptr)
            {
                printf("Cannot open rozkazy.txt");
            }

            if (fprintf(fptr, "%d M %d %d\n", a[i].unit_id, x, y) < 0)
            {
                fprintf(stderr, "\nUnable to write order to file.\n");
            }

            fclose(fptr);
        }    
    }
}
