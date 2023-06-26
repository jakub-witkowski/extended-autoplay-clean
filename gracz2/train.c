#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

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

void train(char fname[], long* g, au a[], int* u, int* t, int* l)
{
	srand(time(NULL)); // providing core for generating random numbers

	int value; // holds the drawing drawing result;
	char* phrase; // phrase printed once training is initiated;
	int choice_made = 0; // controls the selection process;

	/* variables holding values that go into active_units once training is initiated */
	int training_time;
	int unit_cost;
	int unit_stamina;
	char* type;
	
	if (choice_made == 0 && *g < 200)
	{
		unit_cost = 100;
		training_time = 2;
		phrase = "training a worker";
		type = "W";
		choice_made = 1;
	}

	if (choice_made == 0 && (*g >= 100 && *g < 250))
	{
		value = rand() % 21;
		if (value <=10)
		{
			unit_cost = 100;
			training_time = 2;
			phrase = "training a worker";
			type = "W";
			choice_made = 1;
		}
		else if (value >10 && value <= 20)
		{
			unit_cost = 200;
			training_time = 3;
			phrase = "training a pikeman";
			type = "P";
			choice_made = 1;
		}
	}

	if (choice_made == 0 && (*g >= 250 && *g < 400))
	{
		value = rand() % 41;
		if (value <= 10)
		{
			unit_cost = 100;
			training_time = 2;
			phrase = "training a worker";
			type = "W";
			choice_made = 1;
		}
		else if (value > 10 && value <= 20)
		{
			unit_cost = 200;
			training_time = 3;
			phrase = "training a pikeman";
			type = "P";
			choice_made = 1;
		}
		else if (value > 20 && value <= 30)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training a swordsman";
			type = "S";
			choice_made = 1;
		}
		else if (value > 30 && value <= 40)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training an archer";
			type = "A";
			choice_made = 1;
		}
	}

	if (choice_made == 0 && (*g >= 400 && *g < 500))
	{
		value = rand() % 51;
		if (value <= 10)
		{
			unit_cost = 100;
			training_time = 2;
			phrase = "training a worker";
			type = "W";
			choice_made = 1;
		}
		else if (value > 10 && value <= 20)
		{
			unit_cost = 200;
			training_time = 3;
			phrase = "training a pikeman";
			type = "P";
			choice_made = 1;
		}
		else if (value > 20 && value <= 30)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training a swordsman";
			type = "S";
			choice_made = 1;
		}
		else if (value > 30 && value <= 40)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training an archer";
			type = "A";
			choice_made = 1;
		}
		else if (value > 40 && value <= 50)
		{
			unit_cost = 400;
			training_time = 5;
			phrase = "training a knight";
			type = "K";
			choice_made = 1;
		}
	}

	if (choice_made == 0 && (*g >= 500 && *g < 800))
	{
		value = rand() % 61;
		if (value <= 10)
		{
			unit_cost = 100;
			training_time = 2;
			phrase = "training a worker";
			type = "W";
			choice_made = 1;
		}
		else if (value > 10 && value <= 20)
		{
			unit_cost = 200;
			training_time = 3;
			phrase = "training a pikeman";
			type = "P";
			choice_made = 1;
		}
		else if (value > 20 && value <= 30)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training a swordsman";
			type = "S";
			choice_made = 1;
		}
		else if (value > 30 && value <= 40)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training an archer";
			type = "A";
			choice_made = 1;
		}
		else if (value > 40 && value <= 50)
		{
			unit_cost = 400;
			training_time = 5;
			phrase = "training a knight";
			type = "K";
			choice_made = 1;
		}
		else if (value > 50 && value <= 60)
		{
			unit_cost = 500;
			training_time = 4;
			phrase = "producing a ram";
			type = "R";
			choice_made = 1;	
		}
	}

	if (choice_made == 0 && *g > 800)
	{
		value = rand() % 71;
		if (value <= 10)
		{
			unit_cost = 100;
			training_time = 2;
			phrase = "training a worker";
			type = "W";
			choice_made = 1;
		}
		else if (value > 10 && value <= 20)
		{
			unit_cost = 200;
			training_time = 3;
			phrase = "training a pikeman";
			type = "P";
			choice_made = 1;
		}
		else if (value > 20 && value <= 30)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training a swordsman";
			type = "S";
			choice_made = 1;
		}
		else if (value > 30 && value <= 40)
		{
			unit_cost = 250;
			training_time = 3;
			phrase = "training an archer";
			type = "A";
			choice_made = 1;
		}
		else if (value > 40 && value <= 50)
		{
			unit_cost = 400;
			training_time = 5;
			phrase = "training a knight";
			type = "K";
			choice_made = 1;
		}
		else if (value > 50 && value <= 60)
		{
			unit_cost = 500;
			training_time = 4;
			phrase = "producing a ram";
			type = "R";
			choice_made = 1;	
		}
		else if (value > 60)
		{
			unit_cost = 800;
			training_time = 6;
			phrase = "producing a catapult";
			type = "C";
			choice_made = 1;			
		}	
	}

	if (choice_made == 1)
	{
		*t = 1;
		*l = training_time;
		*g -= unit_cost;
		(*u)++;

		/* save order to rozkazy.txt */
		FILE *fptr; 
		fptr = fopen(fname, "a");
        if (!fptr)
		{
            printf("Cannot open rozkazy.txt");
        }

        if (fprintf(fptr, "1 B %c\n", *type) < 0)
		{
            fprintf(stderr, "\nUnable to write order to file.\n");
        }

        fclose(fptr);

		printf("Started %s.\n", phrase);
	}
}