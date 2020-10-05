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
#include "../header/main.h"

MU_TEST(test_maze_valid_size) {
  mu_check(is_valid_size(MIN_MAZE_SIZE - 1) == 0);
  mu_check(is_valid_size(MIN_MAZE_SIZE) == 1);
  mu_check(is_valid_size(MAX_MAZE_SIZE - 1) == 0);
  mu_check(is_valid_size(MAX_MAZE_SIZE) == 1);
}

MU_TEST(test_maze_init_finish) {
  maze_ maze;

  maze.height = 0;
  maze.width = 0;
  mu_check(is_init(maze) == 0);

  maze.height = MIN_MAZE_SIZE;
  maze.width = MIN_MAZE_SIZE;
  mu_check(is_init(maze) == 1);

  mu_check(is_finished(maze, maze.height - 2, maze.width - 1) == 1);
}

MU_TEST(test_maze_locdirection) {
  int line;
  int column;

  line = 3;
  column = 3;
  convert_location_direction(&line, &column, 0);
  mu_check(line == 2 && column == 3);
  convert_location_direction(&line, &column, 1);
  mu_check(line == 2 && column == 4);
  convert_location_direction(&line, &column, 2);
  mu_check(line == 3 && column == 4);
  convert_location_direction(&line, &column, 3);
  mu_check(line == 3 && column == 3);
}

MU_TEST_SUITE(test_maze) {
  MU_RUN_TEST(test_maze_init_finish);
  MU_RUN_TEST(test_maze_valid_size);
  MU_RUN_TEST(test_maze_locdirection);
}

MU_TEST(test_player_move_cell) {
  maze_ maze;
  maze.height = MIN_MAZE_SIZE;
  maze.width = MIN_MAZE_SIZE;
  cell_** cells;
  cells = allocte_cells_line(maze);
  generate_maze(&maze, cells);
  mu_check(get_empty_cell(0, 0, maze, cells) == NULL);
  mu_check(get_empty_cell(1, 0, maze, cells) != NULL);
  free(cells);
}

MU_TEST_SUITE(test_player) {
  MU_RUN_SUITE(test_player_move_cell);
}

void run_tests() {
  MU_RUN_SUITE(test_maze);
  MU_RUN_SUITE(test_player);
  MU_REPORT();
}

int main(void) {
  srand(time(NULL));
  setlocale(LC_ALL, "");

#ifdef UNIT_TESTS
  run_tests();
  return MU_EXIT_CODE;
#else
  show_menu();
  return 0;
#endif
}