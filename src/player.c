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

void tp_player_entrance(player_* player) {
  player->line = 1;
  player->column = 0;
}

int check_player_on_monster(player_* player, maze_ maze) {
  int index;
  monster_ monster;

  for (index = 0; index < maze.monster_maze; index++) {
    monster = maze.monster_list[index];

    if (player->line == monster.line && player->column == monster.column) {
      player->bonus_score -= get_malus_monster(monster);
      return 1;
    }
  }

  return 0;
}

cell_** ask_maze_options(maze_* maze) {
  cell_** cells;
  int valid_size;
  char difficulty_char;

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
    valid_size = 1;
    wprintf(L"Maze difficulty [N(ormal) - H(ard)]: ");
    difficulty_char = getchar();

    if (difficulty_char == '\n') {
      difficulty_char = getchar();
    }

    clear_buffer();

    switch (difficulty_char) {
      case 'n':
      case 'N':
        maze->difficulty = 0;
        break;
      case 'h':
      case 'H':
        maze->difficulty = 1;
        break;
      default:
        valid_size = 0;
        break;
    }

    if (!valid_size) {
      wprintf(L"%sInvalid value%s, ", RED, RESET);
    }
  } while (!valid_size);

  cells = allocte_cells_line(*maze);

  generate_maze(maze, cells);
  save_maze(*maze, cells);

  return cells;
}

void ask_maze_name(maze_* maze) {
  wprintf(L"Maze name: ");
  fgets(maze->name, NAME_MAZE_LENGTH, stdin);
  strtok(maze->name, "\n");
}

int ask_movement() {
  int valid_movement;
  wchar_t movement;

  set_input_mode();
  do {
    wprintf(L"Where you want to go?\n");
    scanf("%lc", &movement);

    /* Arrow keys fix : 27 = empty char || 91 = [ */
    if (movement == 27) {
      scanf("%lc", &movement);

      if (movement == 91) {
        scanf("%lc", &movement);
      }
    }

    valid_movement = is_valid_movement_char(movement);

    if (!valid_movement) {
      wprintf(L"%sInvalid movement%s, ", RED, RESET);
    }
  } while (!valid_movement);
  reset_input_mode();

  return movement;
}

int can_move(wchar_t movement, player_* player, maze_ maze, cell_** cells) {
  int new_line;
  int new_column;
  int direction;
  cell_* neighbour;
  cell_* new_cell;

  switch (movement) {
    case L'z':
    case L'A':
      direction = 0;
      break;
    case L'd':
    case L'C':
      direction = 1;
      break;
    case 's':
    case 'B':
      direction = 2;
      break;
    case 'q':
    case 'D':
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

  /* Delete bonus/malus*/
  if (new_cell->score_value != 0) {
    new_cell->score_value = 0;
    new_cell->symbol = EMPTY_CHAR;
  }

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

int is_valid_movement_char(wchar_t movement) {
  switch (movement) {
    case L'A':
    case L'B':
    case L'C':
    case L'D':
    case L'z':
    case L'q':
    case L's':
    case L'd':
      return 1;
    default:
      return 0;
  }
}

int get_player_score(player_ player) {
  return player.bonus_score - player.moves / 6;
}