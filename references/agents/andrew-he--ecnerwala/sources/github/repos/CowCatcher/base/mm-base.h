#pragma once

#define READ 0
#define WRITE 1

#define RUNNING 0
#define ERROR -1

#define MAXAGENTS 2
#define NUMAGENTS 2 // FIXME only for 2014

#define MAXFARMERS 30
#define BOARDSIZE 30

extern unsigned int loc_decoy;
extern unsigned int loc_cloak;
extern unsigned int loc_telep;
extern unsigned int loc_flwrs;

struct agent_t
{
	char name[256];       // bot name
	unsigned int units[MAXFARMERS];
	unsigned int mooed[MAXFARMERS];
	unsigned int count;

// META:
	int status;           // bot's current status
	int fds[2];           // file descriptors to communicate
	int pid;              // process id of agent
	int timeout;          // amount of time given to respond

// VISUALIZATION:
	void* vis;            // data for visualisation
};

