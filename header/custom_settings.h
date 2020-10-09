#ifndef CUSTOM_SETTINGS
#define CUSTOM_SETTINGS

/** \brief Allow strdup function under -std=c99, last is required for the
 * emojies */
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/** \brief Maximum maze size */
#define DEF_MAX_MAZE_SIZE 99
extern int MAX_MAZE_SIZE;

/** \brief Minimum maze size */
#define DEF_MIN_MAZE_SIZE 5
extern int MIN_MAZE_SIZE;

/** \brief Bonus value */
#define DEF_BONUS_VALUE 8
extern int BONUS_VALUE;

/** \brief Malus value */
#define DEF_MALUS_VALUE -2
extern int MALUS_VALUE;

/** \brief Movement distance max for ghost */
#define DEF_MOVE_GHOST 5
extern int MOVE_GHOST;

/** \brief Movement distance max for ogre */
#define DEF_MOVE_OGRE 3
extern int MOVE_OGRE;

/** \brief Maximum number of turns in which the player can be poisoned */
#define DEF_POISON_MAX_TURN 20
extern int POISON_MAX_TURN;

/** \brief Minimum number of turns in which the player can be poisoned */
#define DEF_POISON_MIN_TURN 5
extern int POISON_MIN_TURN;

/** \brief Config name */
#define CONFIG_NAME "config"

/** \brief Number of config elements */
#define MAXLINE 8

/**
 * \brief Change settings
 */
void edit_advanced_settings();

/**
 * \brief Set settings to default values
 */
void reset_values();

/**
 * \brief Check values to prevent invalid values if user edit the config file
 */
void check_values();

/**
 * \brief Save config values
 */
void save_config_values();

/**
 * \brief Load config values
 */
void load_config_values();

/**
 * \brief Read string config from file
 * \param file File to read
 * \param desired_name Key name
 * \return char* Key value
 */
char* read_string(FILE* file, char const* desired_name);

/**
 * \brief Read int config value from file
 * \param file File to read
 * \param desired_name Key name
 * \param red Int address, will take the value read
 * \return int boolean if read success
 */
int read_int(FILE* file, char const* desired_name, int* ret);

#endif