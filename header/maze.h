/*
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
 * \file maze.h
 * \brief Management of structures and utility functions
 **/
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

/** \defgroup default_maze Default maze values
 * \{
 */

/** \brief Represent a wall cell */
#define WALL_CHAR '#'

/** \brief Represent an empty cell */
#define EMPTY_CHAR ' '

/** \brief Default player position on a cell */
#define PLAYER_CHAR 'o'

/** \brief Represent a bonus */
#define BONUS_CHAR '$'

/** \brief Represent a malus */
#define MALUS_CHAR '^'
/** \} */

/** \defgroup control_maze Control maze values
 * \{
 */
/** Maximum maze name length */
#define NAME_MAZE_LENGTH 32

/** \brief Minimum maze size */
#define MIN_MAZE_SIZE 5

/** \brief Maximum maze size */
#define MAX_MAZE_SIZE 99

/** \brief Bonus value */
#define BONUS_VALUE 8

/** \brief Malus value */
#define MALUS_VALUE -2

/** \brief Maximum number of record save */
#define MAX_SCORE_MAZE 10

/** \brief Maximum player name length */
#define MAX_PLAYER_NAME_LENGTH 32
/** \} */

/** \brief Player position */
typedef struct player {
  int line;        /*!< line number position */
  int column;      /*!< column number position */
  int bonus_score; /*!< player score */
  int moves;       /*!< player move count */
} player_;

/** \brief Maze difficulty */
typedef enum difficulty { NORMAL, HARD } difficulty_;

/** \brief Maze cell */
typedef struct cell {
  int number;      /*!< Cell number, used by the generator */
  char symbol;     /*!< Character representation */
  int score_value; /*!< Bonus/Malus value */
} cell_;

/** \brief Score */
typedef struct score {
  char name[MAX_PLAYER_NAME_LENGTH]; /*!< Name of the player */
  int score;                         /*!< Player score */
} score_;

/** \brief Maze */
typedef struct maze {
  char name[NAME_MAZE_LENGTH];       /*!< Name of the maze */
  int height;                        /*!< Maze height */
  int width;                         /*!< Maze width */
  score_ best_score[MAX_SCORE_MAZE]; /*!< Best score */
  difficulty_ difficulty;            /*!< Maze difficulty */
} maze_;

/**
 * \brief Convert the direction number to the new line/column
 * \param line line number address
 * \param column column number address
 * \param direction direction number (0=TOP, 1=RIGHT, 2=BOT, 3=LEFT)
 */
void convert_location_direction(int* line, int* column, int direction);

/**
 * \brief Check if the maze structure is initialize
 * \param maze maze structure
 * \return int 1 if init, else 0
 */
int is_init(maze_ maze);

/**
 * \brief Free the memory associated with the
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void free_cells(maze_ maze, cell_** cells);

/**
 * \brief Check if the size is valid
 * \param size size number
 * \return int 1 if valid, else 0
 */
int is_valid_size(int size);

/**
 * \brief Check if the player is on the exit cell
 * \param maze maze structure
 * \param line line number
 * \param column column number
 * \return int 1 if finished, else 0
 */
int is_finished(maze_ maze, int line, int column);

#endif