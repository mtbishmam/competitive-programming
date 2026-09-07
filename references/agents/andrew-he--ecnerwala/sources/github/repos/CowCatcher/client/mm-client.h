#ifndef MMCLIENT_H
#define MMCLIENT_H

#define BOARDSIZE 30
#define MAXUNITS 30

extern double P;
extern unsigned int T;

struct coord_t
{
	unsigned row;
	unsigned col;
};

extern struct coord_t locFlowers;
extern struct coord_t locTeleporter;
extern struct coord_t locCloak;
extern struct coord_t locDecoy;

struct player_unit
{
	unsigned int id;
	unsigned int row, col;
	unsigned int last_update;
};

// player information
struct player_data
{
	unsigned int id;

	// information about the player
	unsigned int count;
	struct player_unit units[MAXUNITS];
};

// my bot's data
extern struct player_data SELF;

// file descriptors
extern int _fdout, _fdin;

#endif
