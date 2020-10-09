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

/** Number of cell next to a cell */
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
void move_ghost(maze_ maze, struct monster* monster, cell_** cells);

/**
 * \brief Ogre movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 */
void move_ogre(maze_ maze, struct monster* monster, cell_** cells);

/**
 * \brief Generic monster movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster monster to move
 */
void move_generic(maze_ maze, struct monster* monster, cell_** cells);

/**
 * \brief Poison the player
 * \param player player structure
 * \return number of turn in which the player is poisoned
 */
int poison_player(player_* player);

/**
 * \brief Destroy all treasures pick up by the player
 * \param player player structure
 * \return number of turn in which the player is poisoned
 */
int destroy_treasure(player_* player);

/**
 * \brief Check basic condition for monster movement
 * \param maze maze structure
 * \param monster monster to move
 * \param direction movement direction (0:TOP 1:RIGHT 2:BOT 3:LEFT)
 * \param cell cell struct address (not read, only set)
 * \param cells cells structure array of the maze
 * \return int 1 if movement valid, else 0
 */
int is_valid_case(maze_ maze,
                  monster_* monster,
                  int direction,
                  cell_** cell,
                  cell_** cells);

/**
 * \brief Get new monster distance from spawn location
 * \param monster monster to move
 * \param direction movement direction (0:TOP 1:RIGHT 2:BOT 3:LEFT)
 * \return distance from spawn location
 */
int get_distance(monster_* monster, int direction);

/**
 * \brief Randomly pick a movement from an array and move the monster
 * \param nb_valid_cell number of element in the array
 * \param valid_index array of valid movement direction
 * \param monster monster to move
 */
void handle_move_monsters(int nb_valid_cell,
                          int valid_index[CELL_NEIGHBOUR],
                          monster_* monster);

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
 * \brief Set parameters to monster
 * \param monster monsters struct
 */
void set_parameters_monster(monster_* monster);

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