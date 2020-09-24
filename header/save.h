/**
 * \file save.h
 * \brief Management of save files
 **/
#ifndef SAVE_H
#define SAVE_H

#include <string.h>
#include <sys/stat.h>
#include "./maze.h"
#include "./player.h"

#define SAVE_FOLDER "saves/"
#define SAVE_EXT ".cfg"

char* get_file_name(maze_ maze);

void save_maze(maze_ maze, cell_** cells);

cell_** load_maze(maze_* maze);
#endif