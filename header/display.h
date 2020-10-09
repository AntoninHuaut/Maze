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
 * \file display.h
 * \brief Management of display and generic input functions
 */
#ifndef DISPLAY_H
#define DISPLAY_H
#include <locale.h>
#include "./game.h"
#include "./maze.h"
#include "./utils.h"

/** First available choice in the menu */
#define MIN_CHOICE 1

/** Last available choice in the menu */
#define MAX_CHOICE 6

/**
 * \brief Show the menu to the player
 */
void show_menu();

/**
 * \brief Show the maze to the player
 * \param maze maze structure
 * \param cells cells structure array of the maze
 * \param player player struct
 */
void display(maze_ maze, cell_** cells, player_ player);

/**
 * \brief Print in the console the color associate to the symbol
 * \param symbol symbol of a cell
 */
void printf_symbol_color(wchar_t symbol);

/**
 * \brief Get string value by difficulty number
 * \param difficulty difficulty number
 * \return char* string value
 */
char* get_difficulty_by_num(int difficulty);
#endif