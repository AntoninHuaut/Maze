#include "../header/generator.h"
#include "../header/display.h"

cell_** allocte_cells_line(maze_ maze) {
  int line;
  cell_** array;

  array = (cell_**)malloc(maze.height * sizeof(cell_*));

  if (array == NULL) {
    perror("Malloc error maze\n");
    exit(1);
  }

  for (line = 0; line < maze.height; line++) {
    array[line] = allocate_cells_column(line, maze);
  }

  array[1][0].number = array[1][1].number;
  array[1][0].symbol = PLAYER_CHAR;

  array[maze.height - 2][maze.width - 1].number =
      array[maze.height - 2][maze.width - 2].number;
  array[maze.height - 2][maze.width - 1].symbol = EMPTY_CHAR;

  return array;
}

cell_* allocate_cells_column(int line, maze_ maze) {
  int column;
  cell_* array;

  array = (cell_*)malloc(maze.width * sizeof(cell_));

  if (array == NULL) {
    perror("Malloc error cells\n");
    exit(1);
  }

  for (column = 0; column < maze.width; column++) {
    array[column].symbol =
        is_default_empty_cell(line, column) ? EMPTY_CHAR : WALL_CHAR;

    if (array[column].symbol == WALL_CHAR) {
      array[column].number = -1;
    } else {
      array[column].number = line * maze.width + column;
    }
  }

  return array;
}

int is_default_empty_cell(int line, int column) {
  return line % 2 != 0 && column % 2 != 0;
}

int is_generated(maze_ maze, cell_** cells) {
  int line;
  int column;
  int number;
  int last_valid_number;

  last_valid_number = -1;

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      number = cells[line][column].number;

      if (number == -1) {
        continue;
      }

      if (last_valid_number == -1) {
        last_valid_number = number;
      } else if (last_valid_number != number) {
        return 0;
      }
    }
  }

  return 1;
}

void generate_maze(maze_ maze, cell_** cells) {
  while (!is_generated(maze, cells)) {
    destroy_wall(maze, cells);
  }

  generate_bonus_malus(maze, cells);
}

void destroy_wall(maze_ maze, cell_** cells) {
  int line;
  int column;
  int index;
  cell_* main_case;
  cell_* neighbour_case;

  line = (rand() % (maze.height - 2)) + 1;
  column = (rand() % (maze.width - 2)) + 1;
  main_case = &(cells[line][column]);

  if (main_case->symbol == WALL_CHAR) {
    if (!has_different_neighbour(line, column, maze, cells)) {
      return;
    }

    for (index = 0; index < 4; index++) {
      neighbour_case = get_neighbour(line, column, index, maze, cells);

      /* If the neighbour don't exist (border) or if it's a wall */
      if (neighbour_case == NULL || neighbour_case->symbol == WALL_CHAR) {
        continue;
      }

      /* If the neighbour is on the same path */
      if (neighbour_case->number == main_case->number) {
        continue;
      }

      if (main_case->number == -1) {
        main_case->symbol = EMPTY_CHAR;
        main_case->number = neighbour_case->number;
      } else {
        replace_cell_number(maze, cells, neighbour_case->number,
                            main_case->number);
      }
    }
  }
}

void generate_bonus_malus(maze_ maze, cell_** cells) {
  int max_size;
  int total_bonus_malus;

  int index;
  int line;
  int column;
  cell_* cell;

  max_size = max(maze.height, maze.width);
  total_bonus_malus = (rand() % max_size / 2) + 1;
  printf("%d\n", total_bonus_malus);

  index = 0;
  while (index < total_bonus_malus) {
    line = (rand() % (maze.height - 2)) + 1;
    column = (rand() % (maze.width - 2)) + 1;
    cell = &(cells[line][column]);

    if (cell->symbol == EMPTY_CHAR) {
      if (rand() % 2 == 0) {
        cell->symbol = BONUS_CHAR;
        cell->score_value = BONUS_VALUE;
      } else {
        cell->symbol = MALUS_CHAR;
        cell->score_value = MALUS_VALUE;
      }

      index++;
    }
  }
}

/* Check that the neighbours of the cell have a different value (-1
   excluded) */
int has_different_neighbour(int line, int column, maze_ maze, cell_** cells) {
  int index;
  int neighbour_value[4];
  cell_* neighbour_case;

  for (index = 0; index < 4; index++) {
    neighbour_case = get_neighbour(line, column, index, maze, cells);

    /* If the neighbour don't exist (border) */
    if (neighbour_case == NULL) {
      neighbour_value[index] = -1;
      continue;
    }

    neighbour_value[index] = neighbour_case->number;
  }

  for (index = 1; index < 4; index++) {
    if (neighbour_value[index] != neighbour_value[index - 1]) {
      if (neighbour_value[index] == -1 || neighbour_value[index - 1] == -1) {
        neighbour_value[index] =
            max(neighbour_value[index], neighbour_value[index - 1]);
      } else {
        return 1;
      }
    }
  }

  return 0;
}

/**
 * @direction : 0=TOP, 1=RIGHT, 2=BOT, 3=LEFT
 */
cell_* get_neighbour(int line,
                     int column,
                     int direction,
                     maze_ maze,
                     cell_** cells) {
  convert_location_direction(&line, &column, direction);

  if (line > 0 && line < maze.height - 1 && column > 0 &&
      column < maze.width - 1) {
    return &(cells[line][column]);
  }

  return NULL;
}

/**
 * Replace all cells with the value old_value with the value new_value
 */
void replace_cell_number(maze_ maze,
                         cell_** cells,
                         int old_value,
                         int new_value) {
  int line;
  int column;
  cell_* cell;

  for (line = 1; line < maze.height - 1; line++) {
    for (column = 0; column < maze.width; column++) {
      cell = &(cells[line][column]);

      if (cell->number == old_value) {
        cell->number = new_value;
      }
    }
  }
}