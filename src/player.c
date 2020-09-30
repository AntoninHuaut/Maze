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
#include "../header/player.h"

cell_** ask_maze_options(maze_* maze) {
  cell_** cells;
  int valid_size;

  wprintf(L"\n%sMaze size should be an odd number between %d and %d%s\n",
          YELLOW, MIN_MAZE_SIZE, MAX_MAZE_SIZE, RESET);

  do {
    wprintf(L"Maze height: ");
    ask_value_int(&(maze->height));
    valid_size = is_valid_size(maze->height);

    if (!valid_size) {
      wprintf(L"%sInvalid value%s, ", RED, RESET);
    }
  } while (!valid_size);

  do {
    wprintf(L"Maze width: ");
    ask_value_int(&(maze->width));
    valid_size = is_valid_size(maze->width);

    if (!valid_size) {
      wprintf(L"%sInvalid value%s, ", RED, RESET);
    }
  } while (!valid_size);

  ask_maze_name(maze);

  do {
    wprintf(L"Maze difficulty (Normal: 0 - Hard: 1): ");
    ask_value_int(&valid_size);
    maze->difficulty = valid_size;
    valid_size = maze->difficulty == 0 || maze->difficulty == 1;

    if (!valid_size) {
      wprintf(L"%sInvalid value%s, ", RED, RESET);
    }
  } while (!valid_size);

  cells = allocte_cells_line(*maze);

  generate_maze(*maze, cells);
  save_maze(*maze, cells);

  return cells;
}

void ask_maze_name(maze_* maze) {
  wprintf(L"Maze name: ");
  fgets(maze->name, NAME_MAZE_LENGTH, stdin);
  strtok(maze->name, "\n");
}

int ask_movement() {
  int movement;
  int valid_movement;

  set_input_mode();
  do {
    wprintf(L"Where you want to go?\n");
    movement = getchar();
    valid_movement = is_valid_movement_char(movement);

    if (!valid_movement) {
      wprintf(L"%sInvalid movement%s, ", RED, RESET);
    }
  } while (!valid_movement);
  reset_input_mode();

  return movement;
}

int can_move(int movement, player_* player, maze_ maze, cell_** cells) {
  int new_line;
  int new_column;
  int direction;
  cell_* neighbour;
  cell_* new_cell;

  switch (movement) {
    case 122:
    case 65:
      direction = 0;
      break;
    case 100:
    case 67:
      direction = 1;
      break;
    case 115:
    case 66:
      direction = 2;
      break;
    case 113:
    case 68:
      direction = 3;
      break;
  }

  new_line = player->line;
  new_column = player->column;
  convert_location_direction(&new_line, &new_column, direction);

  neighbour = get_empty_cell(new_line, new_column, maze, cells);

  if (neighbour == NULL || neighbour->symbol == WALL_CHAR) {
    return 0;
  }

  new_cell = &(cells[new_line][new_column]);

  if (new_cell->symbol == BONUS_CHAR || new_cell->symbol == MALUS_CHAR) {
    player->bonus_score += new_cell->score_value;
  }

  cells[player->line][player->column].symbol = EMPTY_CHAR;
  new_cell->symbol = PLAYER_CHAR;

  player->line = new_line;
  player->column = new_column;

  return 1;
}

cell_* get_empty_cell(int line, int column, maze_ maze, cell_** cells) {
  cell_* cell;

  if (line >= 0 && column >= 0 && line < maze.height && column < maze.width) {
    cell = &(cells[line][column]);

    if (cell->symbol != WALL_CHAR) {
      return cell;
    }
  }
  return NULL;
}

int is_valid_movement_char(int movement) {
  /*
  arrow up 65
  arrow down 66
  arrow right 67
  arrow left 68 */
  if (movement >= 65 && movement <= 68) {
    return 1;
  }

  switch (movement) {
    case 122: /* z */
    case 113: /* q */
    case 115: /* s */
    case 100: /* d */
      return 1;
    default:
      return 0;
  }
}

int get_player_score(player_ player) {
  return player.bonus_score - player.moves / 6;
}