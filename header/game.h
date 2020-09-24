/**
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
void start_game(maze_ maze, cell_** cells);

/**
 * \brief Play a round (= one move)
 * \param maze maze structure
 * \param player player structure
 * \param cells cells structure array of the maze
 * \return int 1 if the player move, else 0
 */
int play_round(maze_ maze, player_* player, cell_** cells);

#endif