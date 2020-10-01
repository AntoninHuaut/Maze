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

#include "maze.h"

/**
 * \brief Monsters movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void move_monsters(maze_ maze, cell_** cells);

/**
 * \brief Ghost movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 * \return int 1 if the monster can move, else 0
 */
int move_ghost(maze_ maze, cell_** cells, struct monster* monster);

/**
 * \brief Ogre movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 * \return int 1 if the monster can move, else 0
 */
int move_ogre(maze_ maze, cell_** cells, struct monster* monster);

/**
 * \brief Initialize monster
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void init_monsters(maze_ maze, cell_** cells);

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
 * \brief Set cell symbol depend on monster type
 * \param cells cells structure array of the maze
 * \param monster monsters struct
 */
void set_symbol_monster_cell(cell_* cell, monster_* monster);

#endif