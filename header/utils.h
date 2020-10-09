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
 * \file utils.h
 * \brief Utils display functions
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/** Clear terminal without use system command */
#define CLEAR "\x1B[1;1H\x1B[2J"

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

/** \brief Purple Color */
#define PURPLE "\033[0;35m"

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