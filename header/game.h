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
 * \file game.h
 * \brief Management of the game sequence for the user
 **/
#ifndef GAME_H
#define GAME_H

#include "./display.h"
#include "./generator.h"
#include "./player.h"
#include "./save.h"

/**
 * \brief Start the game
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void start_game(maze_* maze, cell_** cells);

/**
 * \brief Play a round (= one move)
 * \param maze maze structure
 * \param player player structure address
 * \param cells cells structure array of the maze
 * \return int 1 if the player move, else 0
 */
int play_round(maze_ maze, player_* player, cell_** cells);

#endif