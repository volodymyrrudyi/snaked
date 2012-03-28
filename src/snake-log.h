#ifndef __SNAKE_LOG_H
#define __SNAKE_LOG_H

#include <stdio.h>

#define SNAKE_DEBUG(MESSAGE,...)   fprintf(stderr, "%s:%d\tDEBUG:   "MESSAGE"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define SNAKE_WARNING(MESSAGE,...) fprintf(stderr, "%s:%d\tWARNING: "MESSAGE"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define SNAKE_ERROR(MESSAGE,...)   fprintf(stderr, "%s:%d\tERROR:   "MESSAGE"\n",  __FILE__, __LINE__, ##__VA_ARGS__)

#endif
