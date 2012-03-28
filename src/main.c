#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include "snake-game.h"
#include "snake-log.h"

#define DEFAULT_PORT 5100
#define DEFAULT_HOST "localhost"
#define DEFAULT_NAME "snaked"


struct ProgramArgs_t {
    int port;                /* Number of port to be used   */
    const char *host_name;   /* Host name of the server     */
    const char *server_name; /* Name of the server          */
    int daemonize;           /* Run as daemon               */
} program_args;

static const char *getopt_string = "p:h:n:d";

int main(int argc, char **argv)
{
    pid_t pid, sid;
    int opt = 0;
    program_args.port = DEFAULT_PORT;
    program_args.host_name = DEFAULT_HOST;
    program_args.server_name = DEFAULT_NAME;
    program_args.daemonize = 1;

    opt = getopt( argc, argv, getopt_string);
    while( opt != -1 ) {
        switch( opt ) {
            case 'p':
                program_args.port = atoi(optarg);
                break;
            case 'h':
                program_args.host_name = optarg;
                break;
            case 'n':
                program_args.server_name = optarg;
                break;
            case 'd':
                program_args.daemonize = 1;
            default:
                break;
        }
        opt = getopt( argc, argv, getopt_string );
    }

    SNAKE_DEBUG("Using host \"%s\" port %d with server name \"%s\"",
        program_args.host_name, program_args.port, program_args.server_name);


    if (program_args.daemonize)
    {
        SNAKE_DEBUG("Running as daemon");
        pid = fork();

        if (pid < 0)
        {
            SNAKE_ERROR("Fork failed. Exiting");
            exit(EXIT_FAILURE);
        }

        if (pid > 0)
        {
            SNAKE_DEBUG("Successfully forked.");
            exit(EXIT_SUCCESS);
        }

        umask(0);
        sid = setsid();

        if (sid < 0)
        {
            SNAKE_ERROR("Failed to get new session id. Exiting");
            exit(EXIT_FAILURE);
        }

        if (chdir("/")< 0)
        {
            SNAKE_ERROR("Failed to change working directory. Exiting");
            exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
    }

    SNAKE_DEBUG("Daemon launched");
    return 0;
}
