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
#include "../header/monster.h"

void move_monsters(maze_* maze, cell_** cells) {
  int index;
  monster_* monster;

  for (index = 0; index < maze->monster_maze; index++) {
    monster = &(maze->monster_list[index]);
    monster->move_monster(*maze, monster, cells);
  }
}

int poison_player(player_* player) {
  int poison_turn;

  poison_turn =
      (rand() % (POISON_MAX_TURN - POISON_MIN_TURN)) + POISON_MIN_TURN;

  if (player->poison_turn < poison_turn) {
    player->poison_turn = poison_turn;
  } else {
    player->poison_turn++;
  }

  return poison_turn;
}

int destroy_treasure(player_* player) {
  int nb_destroy;
  nb_destroy = player->nb_treasure;
  player->bonus_score -= nb_destroy * BONUS_VALUE;
  player->nb_treasure = 0;

  return nb_destroy;
}

void move_generic(maze_ maze, struct monster* monster, cell_** cells) {
  int index;

  int valid_index[CELL_NEIGHBOUR];
  int nb_valid_cell = 0;

  int valid_cell;
  cell_* cell;

  for (index = 0; index < CELL_NEIGHBOUR; index++) {
    if (!is_valid_case(maze, monster, index, &cell, cells)) {
      continue;
    }

    valid_cell = cell->symbol == MALUS_CHAR || cell->symbol == BONUS_CHAR ||
                 cell->symbol == EMPTY_CHAR;

    if (valid_cell) {
      valid_index[nb_valid_cell] = index;
      nb_valid_cell++;
    }
  }

  handle_move_monsters(nb_valid_cell, valid_index, monster);
}

void move_ghost(maze_ maze, struct monster* monster, cell_** cells) {
  int index;
  int dist;

  int valid_index[CELL_NEIGHBOUR];
  int nb_valid_cell = 0;

  int valid_cell;
  cell_* cell;

  for (index = 0; index < CELL_NEIGHBOUR; index++) {
    if (!is_valid_case(maze, monster, index, &cell, cells)) {
      continue;
    }

    valid_cell = cell->symbol != MALUS_CHAR; /* Ghost can hide malus */
    dist = get_distance(monster, index);

    if (valid_cell && dist < MOVE_GHOST) {
      valid_index[nb_valid_cell] = index;
      nb_valid_cell++;
    }
  }

  handle_move_monsters(nb_valid_cell, valid_index, monster);
}

void move_ogre(maze_ maze, struct monster* monster, cell_** cells) {
  int index;
  int dist;

  int valid_index[CELL_NEIGHBOUR];
  int nb_valid_cell = 0;

  int valid_cell;
  cell_* cell;
  int bmlus_cell;

  int line;
  int column;

  for (index = 0; index < CELL_NEIGHBOUR; index++) {
    if (!is_valid_case(maze, monster, index, &cell, cells)) {
      continue;
    }

    bmlus_cell = cell->symbol == MALUS_CHAR || cell->symbol == BONUS_CHAR;
    valid_cell = bmlus_cell || cell->symbol == EMPTY_CHAR;

    /* It's bonus/malus cell */
    if (bmlus_cell) {
      line = monster->line;
      column = monster->column;
      convert_location_direction(&line, &column, index);
      monster->init_line = line;
      monster->init_column = column;
    }

    dist = get_distance(monster, index);

    if (valid_cell && dist < MOVE_OGRE) {
      valid_index[nb_valid_cell] = index;
      nb_valid_cell++;
    }
  }

  handle_move_monsters(nb_valid_cell, valid_index, monster);
}

int is_valid_case(maze_ maze,
                  monster_* monster,
                  int direction,
                  cell_** cell,
                  cell_** cells) {
  int line;
  int column;

  line = monster->line;
  column = monster->column;
  convert_location_direction(&line, &column, direction);

  if (!is_valid_location_with_wall(maze, line, column) ||
      has_monster_on_case(maze, line, column)) {
    return 0;
  }

  *cell = &(cells[line][column]);

  return 1;
}

int get_distance(monster_* monster, int direction) {
  int line;
  int column;
  int dist;

  line = monster->line;
  column = monster->column;
  convert_location_direction(&line, &column, direction);

  dist = sqrt(pow(line - monster->init_line, 2) +
              pow(column - monster->init_column, 2));

  return dist;
}

void handle_move_monsters(int nb_valid_cell,
                          int valid_index[CELL_NEIGHBOUR],
                          monster_* monster) {
  int line;
  int column;
  int direction_selected;

  if (nb_valid_cell <= 0) {
    return;
  }

  direction_selected = (rand() % (nb_valid_cell));
  direction_selected = valid_index[direction_selected];

  line = monster->line;
  column = monster->column;
  convert_location_direction(&line, &column, direction_selected);

  monster->line = line;
  monster->column = column;
}

void init_monsters(maze_* maze, cell_** cells) {
  int nb_monster_max;
  int index;
  monster_* monster;

  nb_monster_max = maze->height / 10 + maze->width / 10;
  maze->monster_maze = ((rand() % (nb_monster_max - 1)) + 2);

  for (index = 0; index < maze->monster_maze; index++) {
    monster = &(maze->monster_list[index]);
    monster->type = rand() % 4;
    set_parameters_monster(monster);
    set_position_monter(*maze, cells, monster);
  }
}

int has_monster_on_case(maze_ maze, int line, int column) {
  int index;
  monster_ monster;

  for (index = 0; index < maze.monster_maze; index++) {
    monster = maze.monster_list[index];
    if (monster.line == line && monster.column == column) {
      return 1;
    }
  }

  return 0;
}

void set_position_monter(maze_ maze, cell_** cells, monster_* monster) {
  int generated;
  int line;
  int column;
  cell_* cell;

  generated = 0;
  while (!generated) {
    line = (rand() % (maze.height - 2)) + 1;
    column = (rand() % (maze.width - 2)) + 1;
    cell = &(cells[line][column]);

    if (cell->symbol == EMPTY_CHAR) {
      monster->line = line;
      monster->init_line = line;

      monster->column = column;
      monster->init_column = column;

      generated = 1;
    }
  }
}

void set_parameters_monster(monster_* monster) {
  switch (monster->type) {
    case GHOST:
      monster->move_monster = &move_ghost;
      monster->tp_player_eaten = 1;
      break;
    case OGRE:
      monster->move_monster = &move_ogre;
      monster->tp_player_eaten = 1;
      break;
    case SNAKE:
    case DRAGON:
      monster->move_monster = &move_generic;
      monster->tp_player_eaten = 0;
      break;
  }
}

monster_* get_monster_on_case(maze_ maze, int line, int column) {
  monster_* monster;
  int index;

  for (index = 0; index < maze.monster_maze; index++) {
    monster = &(maze.monster_list[index]);

    if (monster->line == line && monster->column == column) {
      return monster;
    }
  }

  return NULL;
}

wchar_t get_symbol_monster_cell(monster_ monster) {
  switch (monster.type) {
    case GHOST:
      return GHOST_CHAR;
    case OGRE:
      return OGRE_CHAR;
    case SNAKE:
      return SNAKE_CHAR;
    case DRAGON:
      return DRAGON_CHAR;
    default:
      return EMPTY_CHAR;
  }
}

int get_malus_monster(monster_ monster) {
  switch (monster.type) {
    case GHOST:
      return MOVE_GHOST * 1.5;
    case OGRE:
      return MOVE_OGRE * 3;
    case SNAKE:
    case DRAGON:
    default:
      return 0;
  }
}