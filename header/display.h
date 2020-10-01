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

/** First available choice in the menu */
#define MIN_CHOICE 1
/** Last available choice in the menu */
#define MAX_CHOICE 5

/**
 * \brief Show the menu to the player
 */
void show_menu();

/**
 * \brief Show the maze to the player
 * \param maze maze structure
 * \param cells cells structure array of the maze
 */
void display(maze_ maze, cell_** cells);

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

/**
 * \brief Clear the buffer
 */
void clear_buffer();

/**
 * \brief Safe integer reading
 * \param var adress of the int to change
 */
void ask_value_int(int* var);

/**
 * \brief Wait for enter entry to continue
 */
void wait_user_interaction();

/** \defgroup text_color Text color
 * Change text color output
 * \{
 */
/** \brief Reset value */
#define RESET "\033[0m"

/** \brief Yellow color */
#define YELLOW "\033[33m"

/** \brief Red color */
#define RED "\033[31m"

/** \brief Green color */
#define GREEN "\033[32m"

/** \brief Bright black color */
#define BLACK_BRIGHT "\033[0;90m"

/** \brief Bright black background color */
#define BLACK_BRIGHT_BACKGROUND "\033[0;100m"

/** \brief Black background color */
#define BLACK_BACKGROUND "\033[40m"

/** \brief White background color */
#define WHITE_BACKGROUND "\033[47m"
/** \} */

/**
 * \brief Reset the input mode in the terminal
 */
void reset_input_mode(void);

/**
 * \brief Change the input mode in the terminal
 */
void set_input_mode(void);

#endif