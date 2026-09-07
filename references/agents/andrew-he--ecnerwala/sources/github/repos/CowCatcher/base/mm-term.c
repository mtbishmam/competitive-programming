#include <unistd.h>
#include <stdio.h>

#include "mm-base.h"
#include "mm-visual.h"

int setup_bcb_vis(int numagents, struct agent_t *agents, int *argc, char ***argv)
{
	return 1;
};

int update_bcb_vis(int numagents, struct agent_t *agents, const int turn)
{
	int farmer[BOARDSIZE * BOARDSIZE] = { 0 };

	int i, j;

	for (j = 0; j < agents[1].count; ++j)
		farmer[agents[1].units[j]]++;

	printf("\033[2J");
	printf("Round #%d %s", turn, agents[0].mooed[0] ? "- MOO!!!!!!!!" : "");
	for (i = 0; i < BOARDSIZE*BOARDSIZE; ++i)
	{
		if (0 == i % BOARDSIZE) printf("\n");

		char cell = '.';
		if (farmer[i] > 9) farmer[i] = 9;

		if (i == loc_decoy) cell = 'c';
		if (i == loc_flwrs) cell = '%';
		if (i == loc_cloak) cell = 's';
		if (i == loc_telep) cell = 't';

		if (farmer[i] > 0) cell = '0' + farmer[i];
		if (agents[0].count > 1 && agents[0].units[1] == i) cell = agents[0].mooed[1] ? '#' : 'c';
		if (agents[0].units[0] == i) cell = agents[0].mooed[0] ? '#' : 'C';

		printf("%c ", cell);
	}

	printf("\n");
	usleep(100000L + (150000L / agents[1].count));
	return 1;
};

void close_bcb_vis()
{

};

