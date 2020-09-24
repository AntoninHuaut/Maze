/**
 * \file save.h
 * \brief Management of save files
 **/
#ifndef SAVE_H
#define SAVE_H

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "./maze.h"
#include "./player.h"

#define SAVE_FOLDER "saves/"
#define SAVE_EXT ".cfg"

char* get_file_name(char* maze_name, int set_ext);

void save_maze(maze_ maze, cell_** cells);

cell_** load_maze(maze_* maze);

int show_save_files();

int is_regular_file(const char* path);
#endif