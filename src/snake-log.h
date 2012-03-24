#ifndef __SNAKE_LOG_H
#define __SNAKE_LOG_H

#include <stdio.h>

#define SNAKE_DEBUG(MESSAGE,...)   fprintf(stderr, "DEBUG:   "MESSAGE"\n",  ##__VA_ARGS__)
#define SNAKE_WARNING(MESSAGE,...) fprintf(stderr, "WARNING: "MESSAGE"\n",  ##__VA_ARGS__)
#define SNAKE_ERROR(MESSAGE,...)   fprintf(stderr, "ERROR:   "MESSAGE"\n",  ##__VA_ARGS__)

#endif
