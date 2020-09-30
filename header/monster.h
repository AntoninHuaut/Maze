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

/** \brief Monster type enum */
typedef enum { GHOST, OGRE } monster_type;

typedef struct monster {
  monster_type type; /*!< Monster type */
  int line;          /*!< line number position */
  int column;        /*!< column number position */
  int (*move_monster)(maze_ maze,
                      cell_** cells,
                      struct monster* monster); /*!< Movement function */
} monster_;

/**
 * \brief Monsters movement function
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param monster_list monsters list
 * \param nb_monster number of monster in the maze
 */
void move_monsters(maze_ maze,
                   cell_** cells,
                   monster_* monster_list,
                   int nb_monster);

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
 * \param monster_list monsters list
 */
void init_monsters(maze_ maze, cell_** cells, monster_* monster_list);

#endif