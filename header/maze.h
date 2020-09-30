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
 * \file maze.h
 * \brief Management of structures and utility functions
 */
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/** \defgroup default_maze Default maze values
 * \{
 */

/** \brief Represent a wall cell */
static const wchar_t WALL_CHAR = L'#';

/** \brief Represent an empty cell */
static const wchar_t EMPTY_CHAR = L' ';

/** \brief Default player position on a cell */
static const wchar_t PLAYER_CHAR = L'o';

/** \brief Represent a bonus */
static const wchar_t BONUS_CHAR = L'💰';

/** \brief Represent a malus */
static const wchar_t MALUS_CHAR = L'🩸';

/** \brief Represent a ghost */
static const wchar_t GHOST_CHAR = L'👻';

/** \brief Represent an ogre */
static const wchar_t OGRE_CHAR = L'👹';
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

/** \brief Maximum monster */
#define MAX_MONSTER_MAZE 20
/** \} */

/** \brief Maze difficulty */
typedef enum difficulty { NORMAL, HARD } difficulty_;

/** \brief Monster type enum */
typedef enum { GHOST, OGRE } monster_type;

/** \brief Player position */
typedef struct player {
  int line;        /*!< line number position */
  int column;      /*!< column number position */
  int bonus_score; /*!< player score */
  int moves;       /*!< player move count */
} player_;

/** \brief Maze cell */
typedef struct cell {
  int number;      /*!< Cell number, used by the generator */
  wchar_t symbol;  /*!< Character representation */
  int score_value; /*!< Bonus/Malus value */
} cell_;

/** \brief Score */
typedef struct score {
  char name[MAX_PLAYER_NAME_LENGTH]; /*!< Name of the player */
  int score;                         /*!< Player score */
} score_;

struct maze;
typedef struct monster {
  monster_type type; /*!< Monster type */
  int line;          /*!< line number position */
  int column;        /*!< column number position */
  int (*move_monster)(struct maze maze,
                      cell_** cells,
                      struct monster* monster); /*!< Movement function */
} monster_;

/** \brief Maze */
typedef struct maze {
  char name[NAME_MAZE_LENGTH];             /*!< Name of the maze */
  int height;                              /*!< Maze height */
  int width;                               /*!< Maze width */
  score_ best_score[MAX_SCORE_MAZE];       /*!< Best score */
  difficulty_ difficulty;                  /*!< Maze difficulty */
  monster_ monster_list[MAX_MONSTER_MAZE]; /*!< Monster list */
  int monster_maze;                        /*!< Number of monster in the maze */
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