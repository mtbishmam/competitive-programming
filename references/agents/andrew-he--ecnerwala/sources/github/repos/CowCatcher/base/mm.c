#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <string.h>
#include <time.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <errno.h>
#include <signal.h>
#include <ctype.h>

#include "mm-base.h"
#include "mm-visual.h"

#define MSG_BFR_SZ 128

#define TIMEOUT_MS_BOT 500
#define TIMEOUT_MS_HMN 30000

#define xstr(s) _str(s)
#define _str(s) #s

#define PORTNO 1337
#define PORTSTR xstr(PORTNO)

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })

#define randf() ((double)rand()/(double)RAND_MAX)

struct agent_t agents[NUMAGENTS];

struct agent_t* agentf;
struct agent_t* agentc;

unsigned int loc_decoy = -1;
unsigned int loc_cloak = -1;
unsigned int loc_telep = -1;
unsigned int loc_flwrs = -1;

unsigned short cow_has_tele = 0;
unsigned int cowmoves = 0;

// file pointer to data for setting up the game
FILE* gamedata = NULL;

double P = 1.0; // probability of detection
unsigned int T = 100; // rounds until new farmer

// setup a child and get its file descriptors
void setup_agent(int, struct agent_t*, char*);

// listen to a bot for a message
void listen_bot(char*, int);

// listen to a bot, with a limited amount of time to wait
void listen_bot_timeout(char*, int, int timeout_ms);

// tell a bot a message
void tell_bot(char*, int);

// tell all bots (but one, possibly) a piece of data
void tell_all(char*, int);

// close all bots' file descriptors
void cleanup_bots();

// socket file descriptor
int sockfd;

unsigned char socket_ready = 0u;
void socket_setup()
{
	if (socket_ready) return;
	socket_ready = 1u;
	
	struct addrinfo hints;
	struct addrinfo *result, *rp;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(NULL, PORTSTR, &hints, &result))
	{ fprintf(stderr, "getaddrinfo failed\n"); exit(1); }

	for (rp = result; rp; rp = rp->ai_next)
	{
		sockfd = socket(rp->ai_family,
			rp->ai_socktype, rp->ai_protocol);
		if (sockfd == -1) continue;
		if (bind(sockfd, rp->ai_addr,
			rp->ai_addrlen) == 0) break;

		close(sockfd);
	}

	if (!rp) exit(1);
	freeaddrinfo(result);
	listen(sockfd, 8);
}

void setup_game(int argc, char** argv)
{
	unsigned int i; char msg[MSG_BFR_SZ];

	P = atof(argv[1]);
	T = atoi(argv[2]);

	// setup the agent using this command
	setup_agent(0, &agents[0], argv[3]);
	setup_agent(1, &agents[1], argv[4]);

	agentc = &agents[0];
	agentf = &agents[1];

	agentc->count = 1;
	agentc->units[0] = (BOARDSIZE * BOARDSIZE) - 1;
	
	for (i = 0; i < NUMAGENTS; ++i)
	{
		// tell the bot its id, it should respond with its name
		sprintf(msg, "INIT %u", i); tell_bot(msg, i);
		listen_bot_timeout(msg, i, agents[i].timeout);

		strncpy(agents[i].name, msg + 5, 255);
		agents[i].name[255] = 0;
	}

	sprintf(msg, "P %lf", P);
	tell_all(msg, -1);

	sprintf(msg, "T %u", T);
	tell_all(msg, -1);

	loc_cloak = (rand() % (BOARDSIZE*BOARDSIZE - 2)) + 1;
	loc_decoy = (rand() % (BOARDSIZE*BOARDSIZE - 2)) + 1;
	loc_flwrs = 14 * BOARDSIZE + 14;
	loc_telep = (rand() % (BOARDSIZE*BOARDSIZE - 2)) + 1;

	#define POS2COORDS(x) ((x) / BOARDSIZE), ((x) % BOARDSIZE)
	
	sprintf(msg, "POS 1 %d %d", POS2COORDS(loc_cloak));
	tell_all(msg, -1);
	
	sprintf(msg, "POS 2 %d %d", POS2COORDS(loc_decoy));
	tell_all(msg, -1);
	
	sprintf(msg, "POS 3 %d %d", POS2COORDS(loc_flwrs));
	tell_all(msg, -1);
	
	sprintf(msg, "POS 4 %d %d", POS2COORDS(loc_telep));
	tell_all(msg, -1);
}

// let's milk some cows
int play_game()
{
	char msg[MSG_BFR_SZ];
	struct agent_t *a;
	unsigned int i, j, x, rnum;

	for (rnum = 0;; ++rnum)
	{
		++cowmoves;

		int newfarmer = (0 == rnum % T);
		if (newfarmer && agentf->count < MAXFARMERS)
		{
			agentf->units[agentf->count] = 0;
			agentf->count++;

			sprintf(msg, "COUNT 1 %d", agentf->count);
			tell_all(msg, -1);
		}

		for (i = 0, a = agents; i < NUMAGENTS; ++a, ++i)
		{
			// announce all the round information
			sprintf(msg, "ROUND %u", rnum);
			tell_bot(msg, i);

			for (x = 0; x < a->count; ++x)
			{
				int k;
				for (k = 0; k < agentf->count; ++k)
				{
					if (agentf->units[k] == agentc->units[0])
						goto gameover;

					// if a farmer touches the decoy cow, it is removed
					if (agentc->count > 1 && agentf->units[k] == agentc->units[1])
						agentc->count = 1;
				}

				unsigned int baseavail = 1;
				unsigned int *availmoves = &baseavail;

				int iscow = a == agentc && x == 0;
				if (iscow) availmoves = &cowmoves;

				for (; *availmoves > 0; --*availmoves)
				{
					update_bcb_vis(NUMAGENTS, agents, rnum);
					a->mooed[x] = 0;

					unsigned int row, col, loc = a->units[x], prev;
					prev = loc;
					sprintf(msg, "MOVE %d %d %d", x, loc / BOARDSIZE, loc % BOARDSIZE);
					tell_bot(msg, i);

					listen_bot_timeout(msg, i, a->timeout);
					if (a->status != RUNNING) return -1;

					sscanf(msg, "%d %d", &row, &col);

					if (row < 0) row = 0;
					if (row >= BOARDSIZE) row = BOARDSIZE - 1;

					if (col < 0) col = 0;
					if (col >= BOARDSIZE) col = BOARDSIZE - 1;

					loc = row * BOARDSIZE + col;
					if (a == agentf && (loc == loc_cloak || loc == loc_flwrs 
						|| loc == loc_decoy || loc == loc_telep)) loc = prev;

					int distrow = abs(prev / BOARDSIZE - row);
					int distcol = abs(prev % BOARDSIZE - col);
					int nomove = distrow == 0 && distcol == 0;

					int cantele = a == agentc && cow_has_tele;
					if ((distrow > 1 || distcol > 1) && cantele) cow_has_tele = 0;

					if (abs(prev / BOARDSIZE - row) > 1 && !cantele) loc = prev;
					if (abs(prev % BOARDSIZE - col) > 1 && !cantele) loc = prev;

					if (a == agentf)
					{
						if (loc == loc_cloak) loc = prev;
						if (loc == loc_decoy) loc = prev;
						if (loc == loc_flwrs) loc = prev;
						if (loc == loc_telep) loc = prev;
					}
					a->units[x] = loc;

					if (iscow && a->units[x] == loc_cloak) 
					{ loc_cloak = -1; P *= 0.5; }

					if (iscow && a->units[x] == loc_decoy)
					{
						loc_decoy = -1;

						agentc->units[agentc->count] = agentc->units[0];
						agentc->count++;

						sprintf(msg, "COUNT 0 %d", agentc->count);
						tell_all(msg, -1);
					}

					if (iscow && a->units[x] == loc_flwrs)
					{
						loc_flwrs = -1;

						for (j = 0; j < agentf->count; ++j)
						{
							if (randf() < 0.5)
							{
								int sz = sizeof(agentf->units[0]) * (agentf->count - j - 1);
								memmove(agentf->units + j, agentf->units + j + 1, sz);
								--agentf->count;
							}

							sprintf(msg, "UPDATE 1 %d %d %d 0", j, agentf->units[j] / BOARDSIZE, agentf->units[j] % BOARDSIZE);
							tell_all(msg, -1);
						}

						sprintf(msg, "COUNT 1 %d", agentf->count);
						tell_all(msg, -1);
					}

					if (iscow && a->units[x] == loc_telep)
					{ loc_telep = -1; cow_has_tele = 1; }

					// only tell everyone the cow's location if it's a "moo" phase
					int moo = (randf() < P && !nomove) || newfarmer;
					a->mooed[x] = moo && a == agentc;

					int issilent = (a == agentc && !moo);
					row = loc / BOARDSIZE; col = loc % BOARDSIZE;
					sprintf(msg, "UPDATE %d %d %d %d %d", i, x, row, col, issilent);
					tell_all(msg, !issilent ? -1 : 1); // COW = 0
					
					// no more moves
					if (nomove) break;
				}
			}
		}
	}

gameover:
	tell_all("ENDGAME", -1);
	return rnum;
}

void sighandler(int signum)
{
	fprintf(stderr, "!!! Signal %d\n", signum);
	close_bcb_vis();
	cleanup_bots();
	exit(1);
}

int main(int argc, char** argv)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	signal(SIGPIPE, sighandler);
	signal(SIGTERM, sighandler);
	
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);

	if (argc < 5)
	{
		fprintf(stderr, "USAGE: %s <P> <T> <cow> <farmer>\n", argv[0]);
		exit(0);
	}

	setup_game(argc, argv);
	if (setup_bcb_vis(NUMAGENTS, agents, &argc, &argv))
	{
		tell_all("READY", -1);
		int rounds = play_game();
		close_bcb_vis();

		fprintf(stdout, "%d\n", rounds);
		fprintf(stderr, "Farmers caught the cow in %d rounds.\n", rounds);
	}

	cleanup_bots();
	return 0;
}

// setup an agent and get its file descriptors
void setup_agent(int bot, struct agent_t* agent, char* filename)
{
	if (!strcmp(filename, "HUMAN"))
	{
		socket_setup();
		
		socklen_t clen;
		struct sockaddr_in cli_addr;
		int nsockfd;

		agent->status = ERROR;
		clen = sizeof cli_addr;

		if (DEBUG) fprintf(stderr, "Accepting connections"
				" for bot #%d\n", bot+1);

		nsockfd = accept(sockfd, 
				(struct sockaddr *) &cli_addr, &clen);
		if (nsockfd < 0) return;

		if (DEBUG) fprintf(stderr, "...bot #%d connected"
				" successfully!\n", bot+1);

		agent->status = RUNNING;
		agent->fds[READ] = agent->fds[WRITE] = nsockfd;
		agent->timeout = TIMEOUT_MS_HMN;
		return;
	}
	else
	{
		int i, pid, c2p[2], p2c[2];
		agent->timeout = TIMEOUT_MS_BOT;

		char *p, *arglist[100];
		for (i = 0, p = strtok(filename, " "); p; 
			++i, p = strtok(NULL, " ")) arglist[i] = strdup(p);
		arglist[i] = NULL;

		// setup anonymous pipes to replace child's stdin/stdout
		if (pipe(c2p) || pipe(p2c))
		{
			// the pipes were not properly set up (perhaps no more file descriptors)
			fprintf(stderr, "Couldn't set up communication for bot%d\n", bot+1);
			exit(1);
		}

		// fork here!
		switch (pid = fork())
		{
		case -1: // error forking
			agent->status = ERROR;
			fprintf(stderr, "Could not fork process to run bot%d: '%s'\n", bot+1, filename);
			exit(1);

		case 0: // child process
			close(p2c[WRITE]); close(c2p[READ]);
			
			if (STDIN_FILENO != dup2(p2c[READ], STDIN_FILENO))
				fprintf(stderr, "Could not replace stdin on bot%d\n", bot+1);
			
			if (STDOUT_FILENO != dup2(c2p[WRITE], STDOUT_FILENO))
				fprintf(stderr, "Could not replace stdout on bot%d\n", bot+1);

			close(p2c[0]); close(c2p[1]);
			agent->status = RUNNING;
			execvp(arglist[0], arglist);
			
			agent->status = ERROR;
			fprintf(stderr, "Could not exec bot%d: [%d] %s\n", 
				bot, errno, strerror(errno));

			exit(1);
			break;

		default: // parent process
			agent->pid = pid;
			close(p2c[READ]); close(c2p[WRITE]);

			agent->fds[READ ] = c2p[READ ]; // save the file descriptors in the
			agent->fds[WRITE] = p2c[WRITE]; // returned parameter
			
			return;
		}
	}
}

// listen to a bot for a message
void listen_bot(char* msg, int bot)
{
	// read message from file descriptor for a bot
	bzero(msg, MSG_BFR_SZ);
	if (agents[bot].status != RUNNING) return;

	int br, bl; char* m = msg;
	for (bl = MSG_BFR_SZ; bl > 0; bl -= br, m += br)
		br = read(agents[bot].fds[READ], m, bl);

	// msg[strcspn(msg, "\r\n")] = 0; // clear out newlines
	if (DEBUG) fprintf(stderr, "==> RECV [%d]: (%d) %s\n", bot, br, msg);
}

// listen to a bot, with a limited amount of time to wait
void listen_bot_timeout(char* msg, int bot, int milliseconds)
{
	fd_set rfds;
	struct timeval tv;
	int retval;

	if (agents[bot].status != RUNNING) return;

	// only care about the bot's file descriptor
	FD_ZERO(&rfds);
	FD_SET(agents[bot].fds[READ], &rfds);

	// timeout in milliseconds
	tv.tv_sec = 0;
	tv.tv_usec = milliseconds * 1000u;

	// wait on this file descriptor...
	retval = select(1+agents[bot].fds[READ], 
		&rfds, NULL, NULL, &tv);

	// error, bot failed
	if (retval < 1) agents[bot].status = ERROR;

	// if we have data to read, read it
	listen_bot(msg, bot);
}

// tell a bot a message
void tell_bot(char* msg, int bot)
{
	// write message to file descriptor for a bot
	int br, bl; char* m = msg;
	for (bl = MSG_BFR_SZ; bl > 0; bl -= br, m += br)
		br = write(agents[bot].fds[WRITE], m, bl);
	
	if (DEBUG) fprintf(stderr, "<-- SEND [%d]: (%d) %s\n", bot, br, msg);
}

// tell all bots (but one, possibly) a piece of data
void tell_all(char* msg, int exclude)
{
	unsigned int i;
	for (i = 0; i < NUMAGENTS; ++i)
		if (i != exclude) tell_bot(msg, i);
}

// close all bots' file descriptors
void cleanup_bots()
{
	int i; for (i = 0; i < NUMAGENTS; ++i)
	{
		close(agents[i].fds[0]);
		kill(agents[i].pid, SIGTERM);
	}
}

