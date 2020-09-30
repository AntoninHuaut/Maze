/**
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.
 *
 * @author Antonin Huaut <antonin.huaut@ecole.ensicaen.fr>
 * @version 1.0.0 - 2020-09-30
 *
 * \file save.h
 * \brief Management of save files
 */
#ifndef SAVE_H
#define SAVE_H

#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include "./maze.h"
#include "./player.h"
#include "./score.h"

/** \brief Save folder */
#define SAVE_FOLDER "saves/"

/** \brief Score file ext */
#define SAVE_EXT ".cfg"

/**
 * \brief replace all char in a string by an another
 * \param str string char
 * \param find char to replace
 * \param replace new char
 * \return char* string char replaced
 */
char* replace_char(char* str, char find, char replace);

/**
 * \brief Get relative file path to the save file
 * \param maze_name maze name
 * \return char* relative file path
 */
char* get_save_file_path(char* maze_name);

/**
 * \brief Save a maze in a cfg file
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void save_maze(maze_ maze, cell_** cells);

/**
 * \brief Ask to user the save to load and call load_maze()
 * \param maze maze structure
 * \return cell_** cells structure array of the maze
 */
cell_** load_new_maze(maze_* maze);

/**
 * \brief Reload a maze from a cfg file
 * \param maze maze structure
 * \return cell_** cells structure array of the maze
 */
cell_** load_maze(maze_* maze);

/**
 * \brief Init and load score
 * \param maze maze structure
 */
void init_score(maze_* maze);

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