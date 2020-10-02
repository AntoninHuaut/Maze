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

void move_ghost(maze_ maze, struct monster* monster, cell_** cells) {
  int index;
  int dist;

  int valid_index[CELL_NEIGHBOUR];
  int nb_valid_cell = 0;
  int direction_selected;

  int valid_cell;
  cell_* cell;

  int line;
  int column;

  for (index = 0; index < CELL_NEIGHBOUR; index++) {
    line = monster->line;
    column = monster->column;
    convert_location_direction(&line, &column, index);

    if (!is_valid_location_with_wall(maze, line, column)) {
      continue;
    }

    cell = &(cells[line][column]);

    dist = sqrt(pow(line - monster->init_line, 2) +
                pow(column - monster->init_column, 2));

    valid_cell = cell->symbol != MALUS_CHAR; /* Ghost can hide malus */

    if (valid_cell && dist < MOVE_GHOST &&
        !has_monster_on_case(maze, line, column)) {
      valid_index[nb_valid_cell] = index;
      nb_valid_cell++;
    }
  }

  if (nb_valid_cell > 0) {
    direction_selected = (rand() % (nb_valid_cell));
    direction_selected = valid_index[direction_selected];

    line = monster->line;
    column = monster->column;
    convert_location_direction(&line, &column, direction_selected);

    monster->line = line;
    monster->column = column;
  }
}

void move_ogre(maze_ maze, struct monster* monster, cell_** cells) {
  int index;
  int dist;

  int valid_index[CELL_NEIGHBOUR];
  int nb_valid_cell = 0;
  int direction_selected;

  int valid_cell;
  int bmlus_cell;
  cell_* cell;

  int line;
  int column;

  for (index = 0; index < CELL_NEIGHBOUR; index++) {
    line = monster->line;
    column = monster->column;
    convert_location_direction(&line, &column, index);

    if (!is_valid_location_with_wall(maze, line, column)) {
      continue;
    }

    cell = &(cells[line][column]);

    dist = sqrt(pow(line - monster->init_line, 2) +
                pow(column - monster->init_column, 2));
    bmlus_cell = cell->symbol == MALUS_CHAR || cell->symbol == BONUS_CHAR;
    valid_cell = bmlus_cell || cell->symbol == EMPTY_CHAR;

    /* It's bonus/malus cell */
    if (bmlus_cell) {
      monster->init_line = line;
      monster->init_column = column;
    }

    if (valid_cell && dist < MOVE_OGRE &&
        !has_monster_on_case(maze, line, column)) {
      valid_index[nb_valid_cell] = index;
      nb_valid_cell++;
    }
  }

  if (nb_valid_cell > 0) {
    direction_selected = (rand() % (nb_valid_cell));
    direction_selected = valid_index[direction_selected];

    line = monster->line;
    column = monster->column;
    convert_location_direction(&line, &column, direction_selected);

    monster->line = line;
    monster->column = column;
  }
}

void init_monsters(maze_* maze, cell_** cells) {
  int nb_monster_max;
  int index;
  monster_* monster;

  nb_monster_max = maze->height / 10 + maze->width / 10;
  maze->monster_maze = ((rand() % (nb_monster_max - 1)) + 2);

  for (index = 0; index < maze->monster_maze; index++) {
    monster = &(maze->monster_list[index]);
    monster->type = rand() % 2;
    set_movefunction_monster(monster);
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

void set_movefunction_monster(monster_* monster) {
  switch (monster->type) {
    case GHOST:
      monster->move_monster = &move_ghost;
      break;
    case OGRE:
      monster->move_monster = &move_ogre;
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
    default:
      return 0;
  }
}