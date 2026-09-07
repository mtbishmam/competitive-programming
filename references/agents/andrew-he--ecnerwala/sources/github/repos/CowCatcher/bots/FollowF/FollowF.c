#include <stdio.h>

#include "mm-client.h"

// This is the name that the driver will refer to your bot as.
const char* BOT_NAME = "Farmer-Follow";

// Return whether setup was successful, bot dies if 0.
int client_setup(int *argc, char ***argv)
{
	return 1;
}

// This function is called when the game begins.
void game_setup(const struct player_data* players)
{

}

// When this function is called, your move is about to start. You can make decisions here if you would like.
void turn_start(unsigned int roundnum, const struct player_data* players)
{

}

#define OVERLAP(rd, cd, obj) (unit->row+(rd) == (obj).row && unit->col+(cd) == (obj).col)
#define OVERLAP_ALL(rd, cd) (OVERLAP((rd), (cd), locCloak) || OVERLAP((rd), (cd), locDecoy) || OVERLAP((rd), (cd), locFlowers) || OVERLAP((rd), (cd), locTeleporter))

// A unit (id + coordinates) is provided. Update its row/col before exiting.
// row/col are zero indexed and range from 0 to BOARDSIZE
void player_turn(struct player_unit* unit, const struct player_data* players)
{
	if (unit->row < players[0].units[0].row && !OVERLAP_ALL(1,0)) ++unit->row;
	else if (unit->row > players[0].units[0].row && !OVERLAP_ALL(-1,0)) --unit->row;
	
	if (unit->col < players[0].units[0].col && !OVERLAP_ALL(0,1)) ++unit->col;
	else if (unit->col > players[0].units[0].col && !OVERLAP_ALL(0,-1)) --unit->col;
}

// This function is called at the end of the game, as a courtesy.
void game_end()
{

}

