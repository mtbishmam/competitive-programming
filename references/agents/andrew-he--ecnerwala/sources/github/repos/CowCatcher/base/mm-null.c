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
	int i, j; struct agent_t *a = agents;
	fprintf(stderr, "Round #%d\n", turn);

	for (i = 0; i < numagents; ++a, ++i) for (j = 0; j < a->count; ++j)
		fprintf(stderr, ">> %24s (%c), unit=%02d, loc=%02d,%02d\n", a->name, 
			i?'F':'C', j, a->units[j] / BOARDSIZE, a->units[j] % BOARDSIZE);
	
	return 1;
};

void close_bcb_vis()
{

};

