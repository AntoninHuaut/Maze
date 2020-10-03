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
 * \file score.h
 * \brief Management of score system
 */
#ifndef SCORE_H
#define SCORE_H

/** \brief Score folder */
#define SCORE_FOLDER "scores/"

/** \brief Score file ext */
#define SCORE_EXT ".score"

#include "./save.h"

/**
 * \brief Get relative file path to the score file
 * \param maze_name maze name
 * \return char* relative file path
 */
char* get_score_file_path(char* maze_name);

/**
 * \brief Show best score of a maze
 * \param maze_name maze name
 */
void show_best_score(maze_* maze);

/**
 * \brief Handle new player score and check if it will be save
 * \param maze maze structure
 * \param player player structure
 */
void handle_new_score(maze_* maze, player_ player);

/**
 * \brief Delete maze score file
 * \param maze maze structure
 */
void delete_maze_score(maze_ maze);

/**
 * \brief Save best maze score in a score file
 * \param maze maze structure
 */
void save_maze_score(maze_* maze);

/**
 * \brief Load best maze score from a score file
 * \param maze maze structure
 * \param best_score best maze score
 */
void load_maze_score(maze_* maze);
#endif