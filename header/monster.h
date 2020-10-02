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
 * \file monster.h
 * \brief Monsters management
 */
#ifndef MONSTER_H
#define MONSTER_H

#include <math.h>
#include "generator.h"
#include "maze.h"

#define MALUS_GHOST 3
#define MALUS_OGRE 5

#define CELL_NEIGHBOUR 4

/**
 * \brief Monsters movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void move_monsters(maze_* maze, cell_** cells);

/**
 * \brief Ghost movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 */
void move_ghost(maze_ maze, cell_** cells, struct monster* monster);

/**
 * \brief Ogre movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 */
void move_ogre(maze_ maze, cell_** cells, struct monster* monster);

/**
 * \brief Initialize monster
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void init_monsters(maze_* maze, cell_** cells);

/**
 * \brief Check if there is a monster on a case
 * \param maze maze structure
 * \param line line number
 * \param column column number
 * \return int 1 if true, else 0
 */
int has_monster_on_case(maze_ maze, int line, int column);

/**
 * \brief Set move function to monster
 * \param monster monsters struct
 */
void set_movefunction_monster(monster_* monster);

/**
 * \brief Set random position to monster
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monsters struct
 */
void set_position_monter(maze_ maze, cell_** cells, monster_* monster);

/**
 * \brief Get monster on case
 * \param maze maze structure
 * \param line line number
 * \param column column number
 * \return monster_* monster pointer on the case (can be NULL)
 */
monster_* get_monster_on_case(maze_ maze, int line, int column);

/**
 * \brief Get monster symbol
 * \param monster monsters struct
 * \return wchar_t monster symbol
 */
wchar_t get_symbol_monster_cell(monster_ monster);

/**
 * \brief Get monster malus
 * \param monster monsters struct
 * \return int malus value
 */
int get_malus_monster(monster_ monster);

#endif