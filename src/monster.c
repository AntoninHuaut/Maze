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

void move_monsters(maze_ maze, cell_** cells) {
  int index;
  monster_* monster;

  for (index = 0; index < maze.monster_maze; index++) {
    monster = &(maze.monster_list[index]);
    monster->move_monster(maze, cells, monster);
  }
}

int move_ghost(maze_ maze, cell_** cells, struct monster* monster) {
  monster->type++; /* TODO UNUSED */
  (&maze)->difficulty++;
  cells[0][0].number++;
  return 0;
}

int move_ogre(maze_ maze, cell_** cells, struct monster* monster) {
  monster->type++; /* TODO UNUSED */
  (&maze)->difficulty++;
  cells[0][0].number++;
  return 0;
}

void init_monsters(maze_ maze, cell_** cells) {
  int nb_monster_max;
  int nb_monster;
  int index;
  monster_* monster;

  nb_monster_max = maze.height / 10 + maze.width / 10;
  nb_monster = (rand() % (nb_monster_max - 1)) + 2;

  for (index = 0; index < nb_monster; index++) {
    monster = &(maze.monster_list[index]);
    monster->type = rand() % 2;
    set_movefunction_monster(monster);
    set_position_monter(maze, cells, monster);
  }
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
      set_symbol_monster_cell(cell, monster);
      monster->line = line;
      monster->column = column;

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

void set_symbol_monster_cell(cell_* cell, monster_* monster) {
  switch (monster->type) {
    case GHOST:
      cell->symbol = GHOST_CHAR;
      break;
    case OGRE:
      cell->symbol = OGRE_CHAR;
      break;
  }
}