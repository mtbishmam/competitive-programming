#include <stdio.h>
#include <math.h>

#include "mm-client.h"

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })

// This is the name that the driver will refer to your bot as.
const char* BOT_NAME = "Cow-Avoid";

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

unsigned int distance_wall(int row, int col)
{
	return min(min(row, BOARDSIZE-1-row), min(col, BOARDSIZE-1-col));
}

unsigned int distance_to_farmer(int row, int col, const struct player_data p)
{
	unsigned int d = 100, i;
	for (i = 0; i < p.count; ++i)
		d = min(d, min(abs(row - p.units[i].row), abs(col - p.units[i].col)));
	return d;
}

// A unit (id + coordinates) is provided. Update its row/col before exiting.
// row/col are zero indexed and range from 0 to BOARDSIZE
void player_turn(struct player_unit* unit, const struct player_data* players)
{
	int best = -1;
	int brow, bcol, r, c;
	for (r = -1; r <= 1; ++r)
	for (c = -1; c <= 1; ++c)
	{
		if (unit->row+r < 0) continue;
		if (unit->row+r >= BOARDSIZE) continue;
		if (unit->col+c < 0) continue;
		if (unit->col+c >= BOARDSIZE) continue;

		int wscore = distance_wall(unit->row+r, unit->col+c);
		int fscore = distance_to_farmer(unit->row+r, unit->col+c, players[1]);
		int score = min(wscore, fscore);

		if (score > best) { brow = unit->row+r; bcol = unit->col+c; best = score; }
	}

	unit->row = brow;
	unit->col = bcol;
}

// This function is called at the end of the game, as a courtesy.
void game_end()
{

}

