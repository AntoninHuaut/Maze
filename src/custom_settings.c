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
 */
#include "../header/custom_settings.h"

int MIN_MAZE_SIZE;
int MAX_MAZE_SIZE;
int BONUS_VALUE;
int MALUS_VALUE;
int MOVE_GHOST;
int MOVE_OGRE;
int POISON_MIN_TURN;
int POISON_MAX_TURN;

void edit_advanced_settings() {
  char reset_settings_char;
  int valid_char;
  int choice_settings;
  do {
    valid_char = 1;
    wprintf(L"What you want todo ? [E(edit)/R(set)/S(ee)]: ");
    reset_settings_char = getchar();

    if (reset_settings_char == '\n') {
      reset_settings_char = getchar();
    }

    clear_buffer();

    switch (reset_settings_char) {
      case 'E':
      case 'e':
        choice_settings = 1;
        break;
      case 'R':
      case 'r':
        choice_settings = 2;
        break;
      case 'S':
      case 's':
        choice_settings = 3;
        break;
      default:
        valid_char = 0;
        break;
    }

    if (!valid_char) {
      wprintf(L"%sInvalid value%s, ", RED, RESET);
    }
  } while (!valid_char);

  if (choice_settings == 3) {
    wprintf(L"\nMinimum maze size: %d\n", MIN_MAZE_SIZE);
    wprintf(L"Maximum maze size: %d\n", MAX_MAZE_SIZE);
    wprintf(L"Treasure (bonus) value: %d\n", BONUS_VALUE);
    wprintf(L"Trap (malus) value: %d\n", MALUS_VALUE);
    wprintf(L"Ghost max distance: %d\n", MOVE_GHOST);
    wprintf(L"Ogre max distance: %d\n", MOVE_OGRE);
    wprintf(L"Maximum number of turn(s) for poison: %d\n", POISON_MAX_TURN);
    wprintf(L"Minimum number of turn(s) for poison: %d\n", POISON_MIN_TURN);
  } else if (choice_settings == 2) {
    wprintf(L"Settings has been reset!\n");
    reset_values();
    save_config_values();
  } else {
    wprintf(L"\nMinimum maze size: ");
    ask_value_int(&MIN_MAZE_SIZE);
    wprintf(L"Maximum maze size: ");
    ask_value_int(&MAX_MAZE_SIZE);
    wprintf(L"Treasure (bonus) value: ");
    ask_value_int(&BONUS_VALUE);
    wprintf(L"Trap (malus) value: ");
    ask_value_int(&MALUS_VALUE);
    do {
      wprintf(L"Ghost max distance (> 0): ");
      ask_value_int(&MOVE_GHOST);
    } while (MOVE_GHOST <= 0);
    do {
      wprintf(L"Ogre max distance (> 0): ");
      ask_value_int(&MOVE_OGRE);
    } while (MOVE_OGRE <= 0);
    do {
      wprintf(L"Maximum number of turn(s) for poison (> 0): ");
      ask_value_int(&POISON_MAX_TURN);
    } while (POISON_MAX_TURN <= 0);
    do {
      wprintf(L"Minimum number of turn(s) for poison (>= 0 ; != %d): ",
              POISON_MAX_TURN);
      ask_value_int(&POISON_MIN_TURN);
    } while (POISON_MIN_TURN < 0 || POISON_MIN_TURN == POISON_MAX_TURN);
    wprintf(L"Settings has been changed!\n");

    check_values();
    save_config_values();
  }

  wait_user_interaction();
}

void reset_values() {
  MIN_MAZE_SIZE = DEF_MIN_MAZE_SIZE;
  MAX_MAZE_SIZE = DEF_MAX_MAZE_SIZE;
  BONUS_VALUE = DEF_BONUS_VALUE;
  MALUS_VALUE = DEF_MALUS_VALUE;
  MOVE_GHOST = DEF_MOVE_GHOST;
  MOVE_OGRE = DEF_MOVE_OGRE;
  POISON_MIN_TURN = DEF_POISON_MIN_TURN;
  POISON_MAX_TURN = DEF_POISON_MAX_TURN;
}

void check_values() {
  int invalid = 0;

  if (MOVE_GHOST <= 0 || MOVE_OGRE <= 0 || POISON_MAX_TURN <= 0) {
    invalid++;
  } else if (POISON_MIN_TURN < 0 || POISON_MIN_TURN == POISON_MAX_TURN) {
    invalid++;
  }

  if (invalid > 0) {
    reset_values();
    save_config_values();
    wprintf(L"%sSettings have invalid values! Reset...%s\n", RED, RESET);
    wait_user_interaction();
  }
}

void save_config_values() {
  FILE* file;
  file = fopen(CONFIG_NAME, "w");
  if (file == NULL) {
    return;
  }

  fprintf(file, "MIN_MAZE_SIZE=%d\n", MIN_MAZE_SIZE);
  fprintf(file, "MAX_MAZE_SIZE=%d\n", MAX_MAZE_SIZE);
  fprintf(file, "BONUS_VALUE=%d\n", BONUS_VALUE);
  fprintf(file, "MALUS_VALUE=%d\n", MALUS_VALUE);
  fprintf(file, "MOVE_GHOST=%d\n", MOVE_GHOST);
  fprintf(file, "MOVE_OGRE=%d\n", MOVE_OGRE);
  fprintf(file, "POISON_MIN_TURN=%d\n", POISON_MIN_TURN);
  fprintf(file, "POISON_MAX_TURN=%d\n", POISON_MAX_TURN);
  fclose(file);
}

void load_config_values() {
  reset_values();

  FILE* file;
  file = fopen(CONFIG_NAME, "r");
  if (file == NULL) {
    save_config_values();
    return;
  }
  read_int(file, "MIN_MAZE_SIZE", &MIN_MAZE_SIZE);
  read_int(file, "MAX_MAZE_SIZE", &MAX_MAZE_SIZE);
  read_int(file, "BONUS_VALUE", &BONUS_VALUE);
  read_int(file, "MALUS_VALUE", &MALUS_VALUE);
  read_int(file, "MOVE_GHOST", &MOVE_GHOST);
  read_int(file, "MOVE_OGRE", &MOVE_OGRE);
  read_int(file, "POISON_MIN_TURN", &POISON_MIN_TURN);
  read_int(file, "POISON_MAX_TURN", &POISON_MAX_TURN);

  check_values();

  fclose(file);
}

/*
 * https://codereview.stackexchange.com/questions/226293/parse-a-simple-key-value-config-file-in-c
 */
char* read_string(FILE* file, char const* desired_name) {
  char name[128];
  char val[128];

  while (fscanf(file, "%127[^=]=%127[^\n]%*c", name, val) == 2) {
    if (0 == strcmp(name, desired_name)) {
      return strdup(val);
    }
  }
  return NULL;
}

int read_int(FILE* file, char const* desired_name, int* ret) {
  fseek(file, 0, SEEK_SET);
  char* temp = read_string(file, desired_name);

  char* stop;
  *ret = strtol(temp, &stop, 10);
  int ret_val = stop == NULL || *stop != '\0';
  free(temp);
  return ret_val;
}