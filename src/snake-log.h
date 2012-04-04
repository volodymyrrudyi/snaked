/*  
	Copyright (c) 2012 Volodymyr Rudyi <vladimir.rudoy@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#ifndef __SNAKE_LOG_H
#define __SNAKE_LOG_H

#include <stdio.h>

#define SNAKE_DEBUG(MESSAGE,...)   fprintf(stderr, "%s:%d\tDEBUG:   "MESSAGE"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define SNAKE_WARNING(MESSAGE,...) fprintf(stderr, "%s:%d\tWARNING: "MESSAGE"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define SNAKE_ERROR(MESSAGE,...)   fprintf(stderr, "%s:%d\tERROR:   "MESSAGE"\n",  __FILE__, __LINE__, ##__VA_ARGS__)

#endif
