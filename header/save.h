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

/**
 * \brief Get relative file path to the save file
 * \param maze_name maze name
 * \return char* relative file path
 */
char* get_file_path(char* maze_name);

/**
 * \brief Save a maze in a cfg file
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void save_maze(maze_ maze, cell_** cells);

/**
 * \brief Load a maze from a cfg file
 * \param maze maze structure
 * \return cell_** cells structure array of the maze
 */
cell_** load_maze(maze_* maze);

/**
 * \brief Show all maze save file to the user
 * \return int 1 if there is one or more save file, else 0
 */
int show_save_files();

/**
 * \brief Check if the file path is a regular file
 * \param path file path
 * \return int 1 if it's a regular file, else 0
 */
int is_regular_file(const char* path);
#endif