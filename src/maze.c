#include "../header/maze.h"

void convert_location_direction(int* line, int* column, int direction) {
  switch (direction) {
    case 0:
      (*line)--;
      break;
    case 1:
      (*column)++;
      break;
    case 2:
      (*line)++;
      break;
    case 3:
      (*column)--;
      break;
  }
}

int is_init(maze_ maze) {
  return maze.height >= MIN_MAZE_SIZE && maze.width >= MIN_MAZE_SIZE;
}

int is_valid_size(int size) {
  return !(size < 5 || size > 100 || size % 2 == 0);
}

int is_finished(maze_ maze, int line, int column) {
  return line == maze.height - 2 && column == maze.width - 1;
}

void free_cells(maze_ maze, cell_** cells) {
  int index;

  if (is_init(maze) && cells != NULL) {
    for (index = 0; index < maze.height; index++) {
      free(cells[index]);
    }
    free(cells);
  }
}