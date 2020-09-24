/**
 * \file maze.h
 * \brief Management of structures and utility functions
 **/
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>

/** \defgroup default_maze Default maze values
 * \{
 */
/** \brief Default maze width */
#define DEFAULT_SIZE_WIDTH 15

/** \brief Default maze height */
#define DEFAULT_SIZE_HEIGHT 9

/** \brief Default maze name */
#define DEFAULT_MAZE_NAME "Default Maze"
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
/** \} */

/** \brief Player position */
typedef struct player {
  int line;   /*!< line number position */
  int column; /*!< column number position */
} player_;

/** \brief Maze difficulty */
typedef enum difficulty { NORMAL, HARD } difficulty_;

/** \brief Maze cell */
typedef struct cell {
  int number;  /*!< Cell number, used by the generator */
  char symbol; /*!< Character representation */
} cell_;

/** \brief Maze */
typedef struct maze {
  char name[NAME_MAZE_LENGTH]; /*!< Name of the maze */
  int height;                  /*!< Maze height */
  int width;                   /*!< Maze width */
  difficulty_ difficulty;      /*!< Maze difficulty */
} maze_;

/**
 * \brief Convert the direction number to the new line/column
 * \param line line number address
 * \param column column number address
 * \param direction direction number (0=TOP, 1=RIGHT, 2=BOT, 3=LEFT)
 */
void convert_location_direction(int* line, int* column, int direction);

int is_init(maze_ maze);

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