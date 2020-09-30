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
 * \file generator.h
 * \brief Manages the generation of the maze
 */
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include "./maze.h"

/** Max between two values */
#define max(a, b) ((a) > (b) ? (a) : (b))

/**
 * \brief Allocate all the lines of the maze
 * \param maze maze structure
 * \return cell_** cells structure array of the maze
 */
cell_** allocte_cells_line(maze_ maze);

/**
 * \brief Allocate all the columns of a line
 * \param maze maze structure
 * \param line line number
 * \return cell_* cells structure of the maze
 */
cell_* allocate_cells_column(int line, maze_ maze);

/**
 * \brief Check is the cell is (before the maze is generating) an empty cell
 * \param line line number
 * \param column column number
 * \return int 1 if true, else 0
 */
int is_default_empty_cell(int line, int column);

/**
 * \brief Check if the maze is generated: all cells are accessibles
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \return int 1 if generated, else 0
 */
int is_generated(maze_ maze, cell_** cells);

/**
 * \brief Manage the generation of the maze
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void generate_maze(maze_ maze, cell_** cells);

/**
 * \brief Destroys a wall to generate the path
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void destroy_wall(maze_ maze, cell_** cells);

/**
 * \brief Randomly destroy a wall (hard difficulty)
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void destroy_wall_hard(maze_ maze, cell_** cells);

/**
 * \brief Randomly generate bonus and malus
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void generate_bonus_malus(maze_ maze, cell_** cells);

/**
 * \brief Check if a cell number is different from its neighbours
 * \param line line number
 * \param column column number
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \return int 1 if true, else 0
 */
int has_different_neighbour(int line, int column, maze_ maze, cell_** cells);

/**
 * \brief Replace all cells value by an another
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param old_value value of the cells who will be replaced
 * \param new_value new value for the cells
 */
void replace_cell_number(maze_ maze,
                         cell_** cells,
                         int old_value,
                         int new_value);

/**
 * \brief Get the neighbour of a cell in one direction
 * \param line line number
 * \param column column number
 * \param direction direction number (0=TOP, 1=RIGHT, 2=BOT, 3=LEFT)
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \return cell_* cell structure of the neighbour
 */
cell_* get_neighbour(int line,
                     int column,
                     int direction,
                     maze_ maze,
                     cell_** cells);

#endif