#include <stdio.h>
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

int mining(int m[][MAP_SIZE_X], au a[], int* u)
{
	int workers_count = 0;
//	int mine_x_coord;
//	int mine_y_coord;
//	int mine_coords;
	int workers_at_the_mine_count = 0;
	int mined_gold = 0;
	const int gold_per_worker = 50;

	/* are there workers among active units of the player? */
	//workers_count = 0;
	for (int i = 0; i < *u; i++)
	{
		if ((strcmp(a[i].unit_type, "W") == 0) && (strcmp(a[i].affiliation, "E") == 0))
		{
			workers_count++;
		}
	}
	//printf("Workers count: %d\n", workers_count);

	/* are any of the workers stationed at a mine? */
	if (workers_count > 0)
	{
		//workers_at_the_mine_count = 0;
		for (int w = 0; w < *u; w++)
		{
			for (int i = 0; i < MAP_SIZE_Y; i++)
			{
				for (int j = 0; j < MAP_SIZE_X; j++)
				{
					if ((m[i][j] == 6) && (strcmp(a[w].unit_type, "W") == 0) && (i == a[w].y_coord) && (j == a[w].x_coord)) 
						workers_at_the_mine_count++;
				}
			}
		}
	}

	//printf("Workers present at the mine: %d\n", workers_at_the_mine_count);

	if (workers_at_the_mine_count > 0)
		mined_gold = workers_at_the_mine_count * gold_per_worker;
	
	return mined_gold;

	/* is any of the workers at a mine? 
	if (workers_count > 0)
	{
		mine_coords = 0;
		for (int i = 0; i < MAP_SIZE_Y; i++)
		{
			for (int j = 0; j < MAP_SIZE_X; j++)
			{
				if (m[i][j] == 6) 
				{
					mine_y_coord = i;
					mine_coords++;
					mine_x_coord = j;
					mine_coords++;
				}
			}
		}
	}

	are workers at the mine?
	if (mine_coords >= 2)
		workers_at_the_mine_count = 0;
		for (int i = 0; i < *u; i++)
			if ((strcmp(a[i].unit_type, "W") == 0) && (a[i].x_coord == mine_x_coord) && (a[i].y_coord == mine_y_coord))
				workers_at_the_mine_count++;

	printf("Workers present at the mine: %d\n", workers_at_the_mine_count);

	if (workers_at_the_mine_count > 0)
		mined_gold = workers_at_the_mine_count * gold_per_worker;
	
	return mined_gold; */

}